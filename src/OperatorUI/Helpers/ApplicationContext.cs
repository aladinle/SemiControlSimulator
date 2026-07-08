using OperatorUI.Models;

namespace OperatorUI.Helpers
{
    public static class ApplicationContext
    {
        public static User CurrentUser { get; set; }

        public static MachineInfo SelectedMachine { get; set; }
    }
}
