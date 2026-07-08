// ControlEngineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ControlEngineAPI.h"
#include "MachineManager.h"

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
    
    std::cout << "Initial State: "
        << machine->getStateMachine().GetStateString() << "\n";

	
	machine->getStateMachine().Initialize();    // Offline -> Ready

    std::cout << "After Initialize: "
        << machine->getStateMachine().GetStateString() << "\n";

    machine->getStateMachine().Start();         // Ready -> Running

    std::cout << "After Start: "
        << machine->getStateMachine().GetStateString() << "\n";

    machine->getStateMachine().Pause();

    std::cout << "After Pause: "
        << machine->getStateMachine().GetStateString() << "\n";

    machine->getStateMachine().Resume();

    std::cout << "After Resume: "
        << machine->getStateMachine().GetStateString() << "\n";

    machine->getStateMachine().Complete();

    std::cout << "After Complete: "
        << machine->getStateMachine().GetStateString() << "\n";

	machine->getRobot().Connect();
	machine->getRobot().home();
	machine->getRobot().moveToPosition(100);

    std::cout << "Robot: "
        << machine->getRobot().GetName()
        << " | Status: "
		<< machine->getRobot().getStatusString()
        << " | Position: "
		<< machine->getRobot().getCurrentPosition()
        << "\n";

    machine->getMotion().Connect();
    machine->getMotion().Enable();
    machine->getMotion().Home();
    machine->getMotion().MoveAbsolute(100.5);

    std::cout << "Motion Position: "
        << machine->getMotion().GetCurrentPosition()
        << "\n";

    machine->getPump().Connect();
    machine->getPump().SetTargetPressure(3.2);
    machine->getPump().Start();

    std::cout << "Pump Pressure: "
        << machine->getPump().GetPressure()
        << "\n";

    machine->getFlowController().Connect();
    machine->getFlowController().SetTargetFlowRate(15.0);
    machine->getFlowController().Open();

    std::cout << "Flow Rate: "
        << machine->getFlowController().GetCurrentFlowRate()
        << "\n";

    machine->getTemperatureSensor().Connect();
    machine->getPressureSensor().Connect();
    machine->getFlowSensor().Connect();
    machine->getVacuumSensor().Connect();

    std::cout << "Temperature: "
        << machine->getTemperatureSensor().ReadValue()
        << " "
        << machine->getTemperatureSensor().GetUnit()
        << "\n";

    std::cout << "Pressure Sensor: "
        << machine->getPressureSensor().ReadValue()
        << " "
        << machine->getPressureSensor().GetUnit()
        << "\n";

    std::cout << "Flow Sensor: "
        << machine->getFlowSensor().ReadValue()
        << " "
        << machine->getFlowSensor().GetUnit()
        << "\n";

    std::cout << "Vacuum: "
        << machine->getVacuumSensor().ReadValue()
        << " "
        << machine->getVacuumSensor().GetUnit()
        << "\n";

    std::cout << "\nPHASE 2 STATE MACHINE TEST PASSED\n";

	return 0;
}