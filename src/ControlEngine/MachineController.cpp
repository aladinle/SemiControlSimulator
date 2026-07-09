#include "MachineController.h"

MachineController::MachineController(IMachineManager* machineManager)
    : machineManager(machineManager), currentMachine(nullptr)
{
}

bool MachineController::SelectMachine(int index)
{
    if (machineManager == nullptr)
        return false;
    currentMachine = machineManager->getMachine(index);
    return currentMachine != nullptr;
}

bool MachineController::InitializeMachine()
{
    if (currentMachine == nullptr)
        return false;

    bool ok = true;

    ok &= currentMachine->getRobot().Connect();
    ok &= currentMachine->getMotion().Connect();
    ok &= currentMachine->getPump().Connect();
    ok &= currentMachine->getFlowController().Connect();

    ok &= currentMachine->getTemperatureSensor().Connect();
    ok &= currentMachine->getPressureSensor().Connect();
    ok &= currentMachine->getFlowSensor().Connect();
    ok &= currentMachine->getVacuumSensor().Connect();

    if (!ok)
    {
        currentMachine->getStateMachine().SetError();
        return false;
    }

    return currentMachine->getStateMachine().Initialize();
}

bool MachineController::StartMachine()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getStateMachine().Start();
}

bool MachineController::StopMachine()
{
    if (currentMachine == nullptr)
        return false;

    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();
    return currentMachine->getStateMachine().Stop();
}

bool MachineController::EmergencyStop()
{
    if (currentMachine == nullptr)
        return false;

    currentMachine->getMotion().Stop();
    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    return currentMachine->getStateMachine().EmergencyStop();
}

bool MachineController::ResetMachine()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getStateMachine().Reset();
}

bool MachineController::PauseMachine()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getStateMachine().Pause();
}

bool MachineController::ResumeMachine()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getStateMachine().Resume();
}

bool MachineController::CompleteMachine()
{
    if (currentMachine == nullptr)
        return false;

	return currentMachine->getStateMachine().Complete();
}

std::string MachineController::GetMachineStateString()
{
    if (currentMachine == nullptr)
        return "Invalid Machine";

    return currentMachine->getStateMachine().GetStateString();
}

bool MachineController::HomeRobot()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getRobot().Home();
}

bool MachineController::MoveRobotToPosition(int position)
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getRobot().MoveToPosition(position);
}

int MachineController::GetRobotPosition()
{
    if (currentMachine == nullptr)
        return false;

	return currentMachine->getRobot().getCurrentPosition();
}

double MachineController::GetPumpPressure()
{
    if (currentMachine == nullptr)
        return false;

	return currentMachine->getPump().GetPressure();
}

double MachineController::GetCurrentFlowRate()
{
    if (currentMachine == nullptr)
        return false;

	return currentMachine->getFlowController().GetCurrentFlowRate();
}

bool MachineController::StartPump(double targetPressure)
{
    if (currentMachine == nullptr)
        return false;

    if (!currentMachine->getPump().SetTargetPressure(targetPressure))
        return false;

    return currentMachine->getPump().Start();
}

bool MachineController::StopPump()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getPump().Stop();
}

bool MachineController::OpenFlow(double targetFlowRate)
{
    if (currentMachine == nullptr)
        return false;

    if (!currentMachine->getFlowController().SetTargetFlowRate(targetFlowRate))
        return false;

    return currentMachine->getFlowController().Open();
}

bool MachineController::CloseFlow()
{
    if (currentMachine == nullptr)
        return false;

    return currentMachine->getFlowController().Close();
}

double MachineController::ReadTemperature()
{
    if (currentMachine == nullptr)
        return 0.0;

    return currentMachine->getTemperatureSensor().ReadValue();
}

double MachineController::ReadPressure()
{
    if (currentMachine == nullptr)
        return 0.0;

    return currentMachine->getPressureSensor().ReadValue();
}

double MachineController::ReadFlow()
{
    if (currentMachine == nullptr)
        return 0.0;

    return currentMachine->getFlowSensor().ReadValue();
}

double MachineController::ReadVacuum()
{
    if (currentMachine == nullptr)
        return 0.0;

    return currentMachine->getVacuumSensor().ReadValue();
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
