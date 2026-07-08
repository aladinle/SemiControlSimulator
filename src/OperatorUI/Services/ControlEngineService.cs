using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace OperatorUI.Services
{
    public class ControlEngineService
    {
        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void InitializeEngine();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetMachineCount();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int StartMachine(int index);

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int StopMachine(int index);

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int GetMachineState(int index);

        [DllImport("ControlEngine.dll",
    EntryPoint = "GetMachineId",
    CallingConvention = CallingConvention.Cdecl,
    CharSet = CharSet.Ansi)]
        private static extern int NativeGetMachineId(
    int index,
    StringBuilder buffer,
    int bufferSize);

        [DllImport("ControlEngine.dll",
            EntryPoint = "GetMachineType",
            CallingConvention = CallingConvention.Cdecl,
            CharSet = CharSet.Ansi)]
        private static extern int NativeGetMachineType(
            int index,
            StringBuilder buffer,
            int bufferSize);

        public void Initialize()
        {
            InitializeEngine();
        }

        public int MachineCount()
        {
            return GetMachineCount();
        }

        public int Start(int index)
        {
            return StartMachine(index);
        }

        public int Stop(int index)
        {
            return StopMachine(index);
        }

        public int State(int index)
        {
            return GetMachineState(index);
        }

        public string MachineId(int index)
        {
            StringBuilder buffer = new StringBuilder(256);
            int result = NativeGetMachineId(index, buffer, buffer.Capacity);
            return result == 0 ? buffer.ToString() : "N/A";
        }

        public string MachineType(int index)
        {
            StringBuilder buffer = new StringBuilder(256);
            int result = NativeGetMachineType(index, buffer, buffer.Capacity);
            return result == 0 ? buffer.ToString() : "N/A";
        }
    }
}
