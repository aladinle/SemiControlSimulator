#pragma once

// ControlEngine is built as a DLL, so exported functions use import/export
// decorations.
#ifdef CONTROLENGINE_EXPORTS
#define CONTROLENGINE_API __declspec(dllexport)
#else
#define CONTROLENGINE_API __declspec(dllimport)
#endif


extern "C" 
{
    CONTROLENGINE_API void InitializeEngine();

    // Machine
    CONTROLENGINE_API int GetMachineCount();
    CONTROLENGINE_API int StartMachine(int index);
    CONTROLENGINE_API int StopMachine(int index);
    CONTROLENGINE_API int ResetMachine(int index);
    CONTROLENGINE_API int SetMachineError(int index);
    CONTROLENGINE_API int GetMachineState(int index);
	CONTROLENGINE_API int GetMachineId(int index, char* buffer, int bufferSize);
	CONTROLENGINE_API int GetMachineType(int index, char* buffer, int bufferSize);
    CONTROLENGINE_API int InitializeSelectedMachine();
    CONTROLENGINE_API int StartSelectedMachine();
    CONTROLENGINE_API int GetSelectedMachineState(char* buffer, int bufferSize);
    CONTROLENGINE_API int SelectMachine(int index);

    // Simulation
    CONTROLENGINE_API void StartSimulation();
    CONTROLENGINE_API void StopSimulation();
    CONTROLENGINE_API void ResetSimulation();
    CONTROLENGINE_API void UpdateSimulation(double deltaTime);

    CONTROLENGINE_API double GetSimulationTime();
    CONTROLENGINE_API double GetPumpPressure();
    CONTROLENGINE_API int IsPumpStable();
    CONTROLENGINE_API int StartPumpSimulation(double targetPressure);

    CONTROLENGINE_API double GetCurrentFlowRate();
    CONTROLENGINE_API double GetTemperature();
    CONTROLENGINE_API double GetVacuum();

    // Event Logger
    CONTROLENGINE_API int GetEventLog(char* buffer, int bufferSize);
}

