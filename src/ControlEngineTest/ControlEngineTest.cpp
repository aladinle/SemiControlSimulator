// ControlEngineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ControlEngineAPI.h"
#include "MachineManager.h"
#include "MachineController.h"

int main()
{
	MachineManager machineManager;
	machineManager.Initialize();

	Machine* machine = machineManager.getMachine(0);

	if(machine == nullptr)
	{
		std::cerr << "Machine not found!\n";
		return -1;
	}

    std::cout << "Machine ID: " << machine->getId() << "\n";
    std::cout << "Machine Type: " << machine->getType() << "\n";
	
    MachineController machineController(machine);

    std::cout << "Initial State: " << machineController.GetMachineStateString() << "\n";

    if (!machineController.InitializeMachine())     // Offline -> Ready
    {
        std::cerr << "FAIL: InitializeMachine failed\n";
        return -1;
    }

    std::cout << "After Initialize: " << machineController.GetMachineStateString() << "\n";

    if (!machineController.StartMachine())         // Ready -> Running
    {
        std::cerr << "FAIL: StartMachine failed\n";
        return -1;
    }

    std::cout << "After Start: " << machineController.GetMachineStateString() << "\n";

	machineController.HomeRobot();
	machineController.MoveRobotToPosition(100);

	machineController.StartPump(3.2);
	machineController.OpenFlow(15.0);

    std::cout << "Robot Position: " << machineController.GetRobotPosition() << "\n";

    std::cout << "Pump Pressure: " << machineController.GetPumpPressure() << "\n";

    std::cout << "Flow Rate: " << machineController.GetCurrentFlowRate() << "\n";

    std::cout << "Temperature: " << machineController.GetTemperature() << "\n";
    std::cout << "Pressure: " << machineController.GetPressure() << "\n";

    std::cout << "Vacuum: " << machineController.GetVacuum() << "\n";

    if (!machineController.StopMachine())     // Running -> Ready
    {
        std::cerr << "FAIL: StopMachine failed\n";
        return -1;
    }

    std::cout << "After Stop: " << machineController.GetMachineStateString() << "\n";

    std::cout << "\nMACHINE CONTROLLER TEST PASSED\n";

	return 0;
}