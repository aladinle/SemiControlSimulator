using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using OperatorUI.Models;
using OperatorUI.Services;
using OperatorUI.Views;
using OperatorUI.Helpers;

namespace OperatorUI
{
    /// <summary>
    /// Interaction logic for DashboardWindow.xaml
    /// </summary>
    public partial class DashboardWindow : Window
    {
        private readonly ControlEngineService controlEngineService = new ControlEngineService();
        public DashboardWindow(User user)
        {
            InitializeComponent();

            UserInfoText.Text = $"Logged in as: {user.Username} ({user.Role})";

            controlEngineService.Initialize();

            int count = controlEngineService.MachineCount();

            LoadMachines();
        }

        private void LoadMachines()
        {
            List<MachineInfo> machines = new List<MachineInfo>();

            int count = controlEngineService.MachineCount();

            for (int i = 0; i < count; i++)
            {
                machines.Add(new MachineInfo
                {
                    Index = i,
                    MachineId = controlEngineService.MachineId(i),
                    MachineType = controlEngineService.MachineType(i),
                    State = ConvertState(controlEngineService.State(i))
                });
            }

            MachineGrid.ItemsSource = machines;
        }

        private string ConvertState(int state)
        {
            return state switch
            {
                0 => "Idle",
                1 => "Running",
                2 => "Error",
                3 => "Maintenance",
                _ => "Unknown"
            };
        }

        private void OpenDetailsButton_Click(object sender, RoutedEventArgs e)
        {
            MachineInfo selectedMachine = MachineGrid.SelectedItem as MachineInfo;

            if (selectedMachine == null)
            {
                MessageBox.Show("Please select a machine first.");
                return;
            }

            ApplicationContext.SelectedMachine = selectedMachine;

            MachineDetailsWindow detailsWindow = new MachineDetailsWindow(selectedMachine);
            detailsWindow.ShowDialog();
        }
    }
}
