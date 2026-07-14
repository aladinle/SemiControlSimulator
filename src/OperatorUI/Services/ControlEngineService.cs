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
        // Machine
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

        [DllImport("ControlEngine.dll", EntryPoint = "GetMachineId", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern int NativeGetMachineId(int index, StringBuilder buffer, int bufferSize);

        [DllImport("ControlEngine.dll", EntryPoint = "GetMachineType", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern int NativeGetMachineType(int index, StringBuilder buffer, int bufferSize);

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int InitializeSelectedMachine();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int StartSelectedMachine();

        // Simulation
        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void StartSimulation();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void StopSimulation();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResetSimulation();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void UpdateSimulation(double deltaTime);

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetSimulationTime();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetPumpPressure();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int IsPumpStable();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int StartPumpSimulation(double targetPressure);

        [DllImport("ControlEngine.dll", EntryPoint = "GetSelectedMachineState", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern int NativeGetSelectedMachineState( StringBuilder buffer, int bufferSize);

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetCurrentFlowRate();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetTemperature();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern double GetVacuum();

        [DllImport("ControlEngine.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int SelectMachine(int index);

        public void Initialize()
        {
            InitializeEngine();
        }

        // Machine
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

        public bool InitializeSelected()
        {
            return InitializeSelectedMachine() != 0;
        }

        public bool StartSelected()
        {
            return StartSelectedMachine() != 0;
        }

        // Simulation
        public void StartSimulationEngine()
        {
            StartSimulation();
        }

        public void StopSimulationEngine()
        {
            StopSimulation();
        }

        public void ResetSimulationEngine()
        {
            ResetSimulation();
        }

        public void UpdateSimulationEngine(double deltaTime)
        {
            UpdateSimulation(deltaTime);
        }

        public double SimulationTime()
        {
            return GetSimulationTime();
        }

        public double PumpPressure()
        {
            return GetPumpPressure();
        }

        public bool PumpStable()
        {
            return IsPumpStable() != 0;
        }

        public bool StartPump(double targetPressure)
        {
            return StartPumpSimulation(targetPressure) != 0;
        }

        public string SelectedMachineState()
        {
            StringBuilder buffer = new StringBuilder(64);

            int result = NativeGetSelectedMachineState(buffer, buffer.Capacity);

            return result == 0 ? buffer.ToString() : "Unknown";
        }

        public double FlowRate()
        {
            return GetCurrentFlowRate();
        }

        public double Temperature()
        {
            return GetTemperature();
        }

        public double Vacuum()
        {
            return GetVacuum();
        }

        public bool SelectMachineByIndex(int index)
        {
            return SelectMachine(index) != 0;
        }
    }
}
