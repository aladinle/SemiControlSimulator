#include "MachineController.h"

MachineController::MachineController(Machine* machine)
    : machine(machine)
{
}

bool MachineController::InitializeMachine()
{
    if (machine == nullptr)
        return false;

    bool ok = true;

    ok &= machine->getRobot().Connect();
    ok &= machine->getMotion().Connect();
    ok &= machine->getPump().Connect();
    ok &= machine->getFlowController().Connect();

    ok &= machine->getTemperatureSensor().Connect();
    ok &= machine->getPressureSensor().Connect();
    ok &= machine->getFlowSensor().Connect();
    ok &= machine->getVacuumSensor().Connect();

    if (!ok)
    {
        machine->getStateMachine().SetError();
        return false;
    }

    return machine->getStateMachine().Initialize();
}

bool MachineController::StartMachine()
{
    if (machine == nullptr)
        return false;

    return machine->getStateMachine().Start();
}

bool MachineController::StopMachine()
{
    if (machine == nullptr)
        return false;

    machine->getPump().Stop();
    machine->getFlowController().Close();

    return machine->getStateMachine().Stop();
}

bool MachineController::EmergencyStop()
{
    if (machine == nullptr)
        return false;

    machine->getMotion().Stop();
    machine->getPump().Stop();
    machine->getFlowController().Close();

    return machine->getStateMachine().EmergencyStop();
}

bool MachineController::ResetMachine()
{
    if (machine == nullptr)
        return false;

    return machine->getStateMachine().Reset();
}

bool MachineController::PauseMachine()
{
    if (machine == nullptr)
        return false;

    return machine->getStateMachine().Pause();
}

bool MachineController::ResumeMachine()
{
    if (machine == nullptr)
        return false;

    return machine->getStateMachine().Resume();
}

bool MachineController::CompleteMachine()
{
    if (machine == nullptr)
        return false;

	return machine->getStateMachine().Complete();
}

std::string MachineController::GetMachineStateString()
{
    if (machine == nullptr)
        return "Invalid Machine";

    return machine->getStateMachine().GetStateString();
}

bool MachineController::HomeRobot()
{
    if (machine == nullptr)
        return false;

    return machine->getRobot().Home();
}

bool MachineController::MoveRobotToPosition(int position)
{
    if (machine == nullptr)
        return false;

    return machine->getRobot().MoveToPosition(position);
}

int MachineController::GetRobotPosition()
{
    if (machine == nullptr)
        return false;

	return machine->getRobot().getCurrentPosition();
}

double MachineController::GetPumpPressure()
{
    if (machine == nullptr)
        return false;

	return machine->getPump().GetPressure();
}

double MachineController::GetCurrentFlowRate()
{
    if (machine == nullptr)
        return false;

	return machine->getFlowController().GetCurrentFlowRate();
}

bool MachineController::StartPump(double targetPressure)
{
    if (machine == nullptr)
        return false;

    if (!machine->getPump().SetTargetPressure(targetPressure))
        return false;

    return machine->getPump().Start();
}

bool MachineController::StopPump()
{
    if (machine == nullptr)
        return false;

    return machine->getPump().Stop();
}

bool MachineController::OpenFlow(double targetFlowRate)
{
    if (machine == nullptr)
        return false;

    if (!machine->getFlowController().SetTargetFlowRate(targetFlowRate))
        return false;

    return machine->getFlowController().Open();
}

bool MachineController::CloseFlow()
{
    if (machine == nullptr)
        return false;

    return machine->getFlowController().Close();
}

double MachineController::ReadTemperature()
{
    if (machine == nullptr)
        return 0.0;

    return machine->getTemperatureSensor().ReadValue();
}

double MachineController::ReadPressure()
{
    if (machine == nullptr)
        return 0.0;

    return machine->getPressureSensor().ReadValue();
}

double MachineController::ReadFlow()
{
    if (machine == nullptr)
        return 0.0;

    return machine->getFlowSensor().ReadValue();
}

double MachineController::ReadVacuum()
{
    if (machine == nullptr)
        return 0.0;

    return machine->getVacuumSensor().ReadValue();
}

double MachineController::GetTemperature()
{
	return ReadTemperature();
}

double MachineController::GetPressure()
{
    return ReadPressure();
}

double MachineController::GetFlow()
{
    return ReadFlow();
}

double MachineController::GetVacuum()
{
    return ReadVacuum();
}
