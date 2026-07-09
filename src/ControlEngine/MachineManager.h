#pragma once
#include "Machine.h"
#include <vector>
#include <memory>
#include "IMachineManager.h"

class MachineManager : public IMachineManager
{
private:
	std::vector<std::unique_ptr<Machine>> machines;

public:
	void Initialize();

	int getMachineCount() const;
	Machine* getMachine(int index);

	int startMachine(int index);
	int stopMachine(int index);
	int resetMachine(int index);
	int setMachineError(int index);
	int getMachineState(int index);
};
