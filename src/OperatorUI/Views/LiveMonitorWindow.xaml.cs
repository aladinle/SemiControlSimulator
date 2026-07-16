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
            MachineTypeText.Text = selectedMachine.MachineType;

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

            MachineStateText.Text = state.ToUpper();
            MachineStateText.Foreground = GetStateBrush(state);

            SimulationTimeText.Text = $"{engine.SimulationTime():F1} s";

            double pressure = engine.PumpPressure();

            PumpPressureText.Text = $"{pressure:F2} bar";

            PumpPressureBar.Value = pressure;

            if (engine.PumpStable())
            {
                PumpStatusText.Text = "🟢 Stable";
                PumpStatusText.Foreground = Brushes.Green;
            }
            else
            {
                PumpStatusText.Text = "🟠 Ramping";
                PumpStatusText.Foreground = Brushes.DarkOrange;
            }

            double pumpPercentage = pressure / 3.2 * 100.0;

            PumpPercentText.Text = $"{pumpPercentage:F0}%";

            FlowRateText.Text = $"{engine.FlowRate():F2} sccm";

            TemperatureText.Text = $"{engine.Temperature():F2} °C";

            VacuumText.Text = $"{engine.Vacuum():F4} Torr";

            EventLogText.Text = engine.EventLog();
            EventLogText.ScrollToEnd();

            // Recipe
            RecipeNameText.Text = engine.RecipeName();
            //RecipeStepText.Text = engine.CurrentRecipeStep();
            double progress = engine.RecipeProgress();
            RecipeProgressBar.Value = progress;
            RecipeProgressText.Text = $"{progress:F0}%";
            RecipeStatusText.Text = GetRecipeStatusString(engine.RecipeStatus());
            RefreshRecipePanel();
        }

        private void RefreshRecipePanel()
        {
            RecipeNameText.Text = engine.RecipeName();

            double progress = engine.RecipeProgress();

            RecipeProgressBar.Value = progress;
            RecipeProgressText.Text = $"{progress:F0}%";

            int status = engine.RecipeStatus();

            RecipeStatusText.Text = GetRecipeStatusString(status);
            RecipeStatusText.Foreground = GetRecipeStatusBrush(status);

            //----------------------------------------------------
            // Recipe Timeline
            //----------------------------------------------------

            RecipeTimelineList.Items.Clear();

            int stepCount = engine.RecipeStepCount();
            int currentStep = engine.CurrentRecipeStepIndex();

            for (int i = 0; i < stepCount; i++)
            {
                string description = engine.RecipeStepDescription(i);

                if (i < currentStep)
                {
                    RecipeTimelineList.Items.Add($"✓ {description}");
                }
                else if (i == currentStep)
                {
                    RecipeTimelineList.Items.Add($"▶ {description}");
                }
                else
                {
                    RecipeTimelineList.Items.Add($"○ {description}");
                }
            }
        }

        private Brush GetRecipeStatusBrush(int status)
        {
            switch (status)
            {
                case 0:
                    return Brushes.Gray;

                case 1:
                    return Brushes.DeepSkyBlue;

                case 2:
                    return Brushes.Green;

                case 3:
                    return Brushes.Red;

                default:
                    return Brushes.Black;
            }
        }

        private string GetRecipeStatusString(int status)
        {
            switch (status)
            {
                case 0:
                    return "⚪ Idle";

                case 1:
                    return "🟢 Running";

                case 2:
                    return "✅ Completed";

                case 3:
                    return "🔴 Failed";

                default:
                    return "Unknown";
            }
        }

        private static Brush GetStateBrush(string state)
        {
            switch (state)
            {
                case "Running":
                    return Brushes.LimeGreen;

                case "Ready":
                    return Brushes.DeepSkyBlue;

                case "Paused":
                    return Brushes.Orange;

                case "Offline":
                    return Brushes.Gray;

                case "Completed":
                    return Brushes.MediumPurple;

                case "Error":
                    return Brushes.Red;

                default:
                    return Brushes.Black;
            }
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

        private void RunRecipeButton_Click(object sender, RoutedEventArgs e)
        {
            if(!engine.RunPumpDownRecipe())
            {
                MessageBox.Show("Failed to start recipe.", "Recipe", MessageBoxButton.OK, MessageBoxImage.Warning);
            }
        }
    }
}
