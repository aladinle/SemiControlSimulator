using OperatorUI.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.PortableExecutable;
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

namespace OperatorUI.Views
{
    /// <summary>
    /// Interaction logic for MachineDetailsWindow.xaml
    /// </summary>
    public partial class MachineDetailsWindow : Window
    {
        public MachineDetailsWindow(MachineInfo machine)
        {
            InitializeComponent();

            TitleText.Text = $"Machine Details - {machine.MachineId}";

            MachineInfoText.Text =
                $"Machine ID: {machine.MachineId}\n" +
                $"Machine Type: {machine.MachineType}\n" +
                $"State: {machine.State}";
        }

        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void OpenTestSetup_Click(object sender, RoutedEventArgs e)
        {
            TestSetupWindow testSetupWindow = new TestSetupWindow();
            testSetupWindow.ShowDialog();
        }
    }
}
