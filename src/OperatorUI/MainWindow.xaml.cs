using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using OperatorUI.Models;
using OperatorUI.Services;
using OperatorUI.Helpers;

namespace OperatorUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly AuthenticationService authService = new AuthenticationService();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void LoginButton_Click(object sender, RoutedEventArgs e)
        {
            string username = UsernameTextBox.Text;
            string password = PasswordBox.Password;

            var user = authService.login(username, password);
            if (user == null)
            {
                ErrorTextBlock.Text = "Invalid username or password.";
                return;
            }

            // Store the authenticated user in the application context for later use
            ApplicationContext.CurrentUser = user;

            // Navigate to the appropriate view based on the user's role
            DashboardWindow dashboardWindow = new DashboardWindow(user);
            dashboardWindow.Show();

            this.Close();
        }
    }
}