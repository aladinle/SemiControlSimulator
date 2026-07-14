using OperatorUI.Models;
using OperatorUI.Services;
using System;
using System.Windows;
using System.Windows.Media;
using System.Windows.Threading;

namespace OperatorUI.Views
{
    public partial class LiveMonitorWindow : Window
    {
        private readonly ControlEngineService engine;
        private readonly DispatcherTimer timer;

        private readonly MachineInfo selectedMachine;

        public LiveMonitorWindow(MachineInfo machine)
        {
            InitializeComponent();

            selectedMachine = machine;

            MessageBox.Show($"Opening {selectedMachine.MachineId}\n" + $"Index = {selectedMachine.Index}");

            engine = new ControlEngineService();
            engine.Initialize();

            // Tell the native controller which machine to monitor.
            if (!engine.SelectMachineByIndex(selectedMachine.Index))
            {
                MessageBox.Show(
                    $"Unable to select machine {selectedMachine.MachineId}.",
                    "Machine Selection Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);

                Close();
                return;
            }

            timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(100)
            };

            timer.Tick += Timer_Tick;

            MachineIdText.Text = selectedMachine.MachineId;

            RefreshDashboard();

            timer.Start();
        }

        private void Timer_Tick(
            object? sender,
            EventArgs e)
        {
            const double deltaTime = 0.1;

            engine.UpdateSimulationEngine(deltaTime);

            RefreshDashboard();
        }

        private void RefreshDashboard()
        {
            string state = engine.SelectedMachineState();

            MachineStateText.Text = state;
            MachineStateText.Foreground =
                GetStateBrush(state);

            SimulationTimeText.Text =
                $"{engine.SimulationTime():F1} s";

            PumpPressureText.Text =
                $"{engine.PumpPressure():F2} bar";

            PumpStatusText.Text =
                engine.PumpStable()
                    ? "Stable"
                    : "Ramping";

            FlowRateText.Text =
                $"{engine.FlowRate():F2} sccm";

            TemperatureText.Text =
                $"{engine.Temperature():F2} °C";

            VacuumText.Text =
                $"{engine.Vacuum():F4} Torr";
        }

        private static Brush GetStateBrush(string state)
        {
            return state switch
            {
                "Ready" => Brushes.Green,
                "Running" => Brushes.DodgerBlue,
                "Stable" => Brushes.Green,
                "Paused" => Brushes.DarkOrange,
                "Completed" => Brushes.Purple,
                "Error" => Brushes.Red,
                "Emergency Stop" => Brushes.DarkRed,
                _ => Brushes.Gray
            };
        }

        private void InitializeButton_Click(
            object sender,
            RoutedEventArgs e)
        {
            if (!engine.InitializeSelected())
            {
                MessageBox.Show(
                    "Machine initialization failed.",
                    "Initialization Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }

            RefreshDashboard();
        }

        private void StartMachineButton_Click(
            object sender,
            RoutedEventArgs e)
        {
            if (!engine.StartSelected())
            {
                MessageBox.Show(
                    "Machine could not be started.",
                    "Start Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }

            RefreshDashboard();
        }

        private void StartPumpButton_Click(
            object sender,
            RoutedEventArgs e)
        {
            engine.ResetSimulationEngine();
            engine.StartSimulationEngine();

            if (!engine.StartPump(3.2))
            {
                MessageBox.Show(
                    "Pump could not be started.",
                    "Pump Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);
            }

            RefreshDashboard();
        }

        private void StopButton_Click(
            object sender,
            RoutedEventArgs e)
        {
            timer.Stop();
            engine.StopSimulationEngine();
            engine.ResetSimulationEngine();
            Close();
        }

        protected override void OnClosed(EventArgs e)
        {
            timer.Stop();
            engine.StopSimulationEngine();

            base.OnClosed(e);
        }
    }
}
