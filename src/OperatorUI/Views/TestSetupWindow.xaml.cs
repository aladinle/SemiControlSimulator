using OperatorUI.Helpers;
using System.Windows;

namespace OperatorUI.Views
{
    /// <summary>
    /// Interaction logic for TestSetupWindow.xaml
    /// </summary>
    public partial class TestSetupWindow : Window
    {
        public TestSetupWindow()
        {
            InitializeComponent();

            var machine = ApplicationContext.SelectedMachine;

            TitleText.Text = $"Test Setup for Machine {machine.MachineId} (Type: {machine.MachineType})";

            MachineInfoText.Text = $"Machine Index: {machine.Index}\n" +
                                   $"Machine Type: {machine.MachineType}\n" +
                                   $"State: {machine.State}";
        }

        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }
    }
}
