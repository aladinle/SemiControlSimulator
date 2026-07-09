#include "ControlEngineAPI.h"
#include "MachineManager.h"
#include <cstring>

static MachineManager machineManager;

void InitializeEngine() {
	machineManager.Initialize();
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