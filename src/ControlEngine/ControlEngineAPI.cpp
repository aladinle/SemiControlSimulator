#include "ControlEngineAPI.h"
#include "MachineManager.h"
#include "MachineController.h"
#include <cstring>
#include <iostream>

static MachineManager machineManager;
static MachineController machineController(&machineManager);
static bool isEngineInitialized = false;

void InitializeEngine() {
	// avoid calling InitializeEngine() duplicated
	if (isEngineInitialized)
	{
		return;
	}

	machineManager.Initialize();

	if (!machineController.SelectMachine(0))
	{
		return;
	}
	// initialize engine
	isEngineInitialized = true;
}

int GetMachineCount() {
	return machineManager.getMachineCount();
}

int StartMachine(int index) {
	return machineManager.startMachine(index);
}

int StopMachine(int index) {
	return machineManager.stopMachine(index);
}

int ResetMachine(int index) {
	return machineManager.resetMachine(index);
}

int SetMachineError(int index) {
	return machineManager.setMachineError(index);
}

int GetMachineState(int index) {
	return machineManager.getMachineState(index);
}

int GetMachineId(int index, char* buffer, int bufferSize) {
	Machine* machine = machineManager.getMachine(index);
	if (!machine || buffer == nullptr || bufferSize <= 0)
		return -1;

	strncpy_s(buffer, bufferSize, machine->getId().c_str(), _TRUNCATE);
	return 0;
}
		
int GetMachineType(int index, char* buffer, int bufferSize)
{
	Machine* machine = machineManager.getMachine(index);
	if (!machine || buffer == nullptr || bufferSize <= 0)
		return -1;

	strncpy_s(buffer, bufferSize, machine->getType().c_str(), _TRUNCATE);
	return 0;
}

int InitializeSelectedMachine()
{
	std::cout << "InitializeSelectedMachine() called\n";

	if (!isEngineInitialized)
	{
		InitializeEngine();
	}

	// double check after re_initialized
	if (!isEngineInitialized)
	{
		return 0;
	}

	const std::string state = machineController.GetMachineStateString();
	if (state == "Ready" || state == "Running" || state == "Paused")
	{
		return 1;
	}
	
	return machineController.InitializeMachine() ? 1 : 0;
}

int StartSelectedMachine()
{
	std::cout << "StartSelectedMachine() called\n";

	if (!isEngineInitialized)
	{
		InitializeEngine();
	}

	// double check after re_initialized
	if (!isEngineInitialized)
	{
		return 0;
	}

	if (machineController.GetMachineStateString() == "Running")
	{
		return 1;
	}

	if (machineController.GetMachineStateString() == "Offline")
	{
		if (!machineController.InitializeMachine())
		{
			return 0;
		}
	}

	return machineController.StartMachine() ? 1 : 0;
}

CONTROLENGINE_API int GetSelectedMachineState(char* buffer, int bufferSize)
{
	if (!isEngineInitialized || buffer == nullptr || bufferSize <= 0)
	{
		return -1;
	}

	const std::string state = machineController.GetMachineStateString();

	strncpy_s(buffer, static_cast<size_t>(bufferSize), state.c_str(), _TRUNCATE);

	return 0;
}

int SelectMachine(int index)
{
	if (!isEngineInitialized)
	{
		InitializeEngine();
	}

	if (!isEngineInitialized)
	{
		return 0;
	}

	return machineController.SelectMachine(index) ? 1 : 0;
}

// Simulation
void StartSimulation()
{
	machineController.StartSimulation();
}

void StopSimulation()
{
	machineController.StopSimulation();
}

void ResetSimulation()
{
	machineController.ResetSimulation();
}

void UpdateSimulation(double deltaTime)
{
	machineController.UpdateSimulation(deltaTime);
}

double GetSimulationTime()
{
	return machineController.GetSimulationTime();
}

double GetPumpPressure()
{
	return machineController.GetPumpPressure();
}

int IsPumpStable()
{
	return machineController.IsPumpStable() ? 1 : 0;
}

int StartPumpSimulation(double targetPressure)
{
	std::cout << "StartPumpSimulation() called\n";

	if (!isEngineInitialized)
	{
		InitializeEngine();
	}

	if (machineController.GetMachineStateString() == "Offline")
	{
		if (!machineController.InitializeMachine())
		{
			return 0;
		}

		if (!machineController.StartMachine())
		{
			return 0;
		}
	}
	else if (machineController.GetMachineStateString() == "Ready")
	{
		if (!machineController.StartMachine())
		{
			return 0;
		}
	}

	machineController.StartSimulation();

	return machineController.StartPump(targetPressure) ? 1 : 0;
}

double GetCurrentFlowRate()
{
	if (!isEngineInitialized)
	{
		return 0.0;
	}

	return machineController.GetCurrentFlowRate();
}

double GetTemperature()
{
	if (!isEngineInitialized)
	{
		return 0.0;
	}

	return machineController.GetTemperature();
}

double GetVacuum()
{
	if (!isEngineInitialized)
	{
		return 0.0;
	}

	return machineController.GetVacuum();
}

CONTROLENGINE_API int GetEventLog(char* buffer, int bufferSize)
{
	if (!isEngineInitialized || buffer == nullptr || bufferSize < 0)
	{
		return -1;
	}

	std::string eventText = machineController.GetEventLogger().ToString();
	strncpy_s(buffer, bufferSize, eventText.c_str(), _TRUNCATE);
	return 0;
}

CONTROLENGINE_API int StartPumpDownRecipe()
{
	return machineController.StartPumpDownRecipe() ? 1 : 0;
}

double GetRecipeProgress()
{
	return machineController.GetRecipeProgress();
}

CONTROLENGINE_API int GetRecipeStatus()
{
	return static_cast<int>(machineController.GetRecipeStatus());
}

CONTROLENGINE_API int GetRecipeName(char* buffer, int bufferSize)
{
	if (buffer == nullptr || bufferSize <= 0)
	{
		return -1;
	}

	std::string name = machineController.GetRecipeName();

	strncpy_s(buffer, bufferSize, name.c_str(), _TRUNCATE);

	return 0;
}

CONTROLENGINE_API int GetRecipeCurrentStep(char* buffer, int bufferSize)
{
	if (buffer == nullptr || bufferSize <= 0)
	{
		return -1;
	}

	std::string name = machineController.GetRecipeCurrentStep();

	strncpy_s(buffer, bufferSize, name.c_str(), _TRUNCATE);

	return 0;
}
