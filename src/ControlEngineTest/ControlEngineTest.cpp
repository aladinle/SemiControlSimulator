// ControlEngineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ControlEngineAPI.h"

int main()
{
	InitializeEngine();

	std::cout << "Machine Control Engine initialized successfully." << std::endl;

	std::cout << "Machine Count: " << GetMachineCount() << std::endl;

	StartMachine(0);
	std::cout << "Machine 0 State: " << GetMachineState(0) << std::endl;

	StopMachine(0);
	std::cout << "Machine 0 State after stopping: " << GetMachineState(0) << std::endl;

	return 0;
}