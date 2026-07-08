#include "MachineManager.h"

void MachineManager::Initialize() {
	machines.clear();

	machines.push_back(std::make_unique<Machine>("EQ-001", "CVD Chamber"));
	machines.push_back(std::make_unique<Machine>("EQ-002", "Robot Cell"));
	machines.push_back(std::make_unique<Machine>("EQ-003", "Pump Station"));
}

int MachineManager::getMachineCount() const {
	return static_cast<int>(machines.size());
}

Machine* MachineManager::getMachine(int index) {
	if (index < 0 || index >= static_cast<int>(machines.size())) {
		return nullptr;
	}
	return machines[index].get();
}

int MachineManager::startMachine(int index) {
	auto machine = getMachine(index);
	if (machine) {
		machine->start();
		return 0; // Success
	}
	return -1; // Machine not found
}

int MachineManager::stopMachine(int index){
	auto machine = getMachine(index);
	if (machine) {
		machine->stop();
		return 0; // Success
	}
	return -1; // Machine not found
}

int MachineManager::resetMachine(int index) {
	auto machine = getMachine(index);
	if (machine) {
		machine->reset();
		return 0; // Success
	}
	return -1; // Machine not found
}

int MachineManager::setMachineError(int index) {
	auto machine = getMachine(index);
	if (machine) {
		machine->setError();
		return 0; // Success
	}
	return -1; // Machine not found
}

int MachineManager::getMachineState(int index) {
	auto machine = getMachine(index);
	if (machine) {
		return static_cast<int>(machine->getState());
	}
	return -1; // Machine not found
}