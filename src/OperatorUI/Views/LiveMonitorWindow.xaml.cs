using System;
using System.Windows;
using System.Windows.Threading;
using OperatorUI.Services;

namespace OperatorUI.Views
{
    public partial class LiveMonitorWindow : Window
    {
        private readonly ControlEngineService engine;
        private readonly DispatcherTimer timer;

        public LiveMonitorWindow()
        {
            InitializeComponent();

            engine = new ControlEngineService();
            // Make sure engine is initialized before using simulation
            engine.Initialize();

            if (!engine.InitializeSelected())
            {
                MessageBox.Show(
                    "Machine initialization failed.",
                    "Initialization Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);

                return;
            }

            if (!engine.InitializeSelected())
            {
                MessageBox.Show(
                    "Machine initialization failed.",
                    "Initialization Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);

                return;
            }

            engine.ResetSimulationEngine();
            engine.StartSimulationEngine();

            timer = new DispatcherTimer
            {
                Interval = TimeSpan.FromMilliseconds(100)
            };

            timer.Tick += Timer_Tick;

            engine.ResetSimulationEngine();
            engine.StartSimulationEngine();

            timer.Start();
        }

        private void Timer_Tick(object? sender, EventArgs e)
        {
            const double deltaTime = 0.1;

            engine.UpdateSimulationEngine(deltaTime);

            SimulationTimeText.Text = $"{engine.SimulationTime():F1} s";

            PumpPressureText.Text = $"{engine.PumpPressure():F2} bar";

            PumpStatusText.Text = engine.PumpStable() ? "Stable" : "Ramping";
        }

        private void StartPumpButton_Click(object sender, RoutedEventArgs e)
        {
            engine.ResetSimulationEngine();
            engine.StartSimulationEngine();

            bool started = engine.StartPump(3.2);

            if (!started)
            {
                MessageBox.Show(
                    "Pump could not be started.",
                    "Pump Error",
                    MessageBoxButton.OK,
                    MessageBoxImage.Error);

                return;
            }

            PumpStatusText.Text = "Ramping";
        }

        private void StopButton_Click(object sender, RoutedEventArgs e)
        {
            timer.Stop();
            engine.StopSimulationEngine();
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