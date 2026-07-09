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
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }
        
    eventLogger.Info("Machine", "Initializing machine....");

    bool isInitialized = true;

    isInitialized &= currentMachine->getRobot().Connect();
    isInitialized &= currentMachine->getMotion().Connect();
    isInitialized &= currentMachine->getPump().Connect();
    isInitialized &= currentMachine->getFlowController().Connect();

    isInitialized &= currentMachine->getTemperatureSensor().Connect();
    isInitialized &= currentMachine->getPressureSensor().Connect();
    isInitialized &= currentMachine->getFlowSensor().Connect();
    isInitialized &= currentMachine->getVacuumSensor().Connect();

    if (!isInitialized)
    {
        eventLogger.Error("Machine", "Initialization failed.");
        currentMachine->getStateMachine().SetError();
        return false;
    }

    eventLogger.Info("Machine", "Initialization successful.");

    return currentMachine->getStateMachine().Initialize();
}

bool MachineController::StartMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "StartMachine(): No machine selected.");
        return false;
    }

    eventLogger.Info("Machine", "Starting machine.");

    bool result = currentMachine->getStateMachine().Start();

    if (result)
        eventLogger.Info("Machine", "Machine is now RUNNING.");
    else
        eventLogger.Warning("Machine", "Start rejected by state machine.");

    return result;
}

bool MachineController::StopMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "StopMachine(): No machine selected.");
        return false;
    }

    eventLogger.Info("Machine", "Stopping machine.");

    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    bool result = currentMachine->getStateMachine().Stop();

    if (result)
        eventLogger.Info("Machine", "Machine is now STOPPED.");
    else
        eventLogger.Warning("Machine", "STOP is rejected by state machine.");

    return result;
}

bool MachineController::EmergencyStop()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "EmergencyStop(): No machine selected.");
        return false;
    }

    currentMachine->getMotion().Stop();
    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    eventLogger.Info("Machine", "EEMERGENCY STOPPING machine.");

    bool result = currentMachine->getStateMachine().EmergencyStop();

    if (result)
        eventLogger.Info("Machine", "Machine is now EMERGENCY STOPPED.");
    else
        eventLogger.Warning("Machine", "EMERGENCY STOPPED is rejected by state machine.");

    return result;
}

bool MachineController::ResetMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "ResetMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Reset();

    if (result)
        eventLogger.Info("Machine", "Machine is now RESETTED.");
    else
        eventLogger.Warning("Machine", "RESET is rejected by state machine.");

    return result;    
}

bool MachineController::PauseMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "PauseMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Pause();

    if (result)
        eventLogger.Info("Machine", "Machine is now PAUSED.");
    else
        eventLogger.Warning("Machine", "PAUSE is rejected by state machine.");

    return result;
}

bool MachineController::ResumeMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "ResumeMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Resume();

    if (result)
        eventLogger.Info("Machine", "Machine is now RESUMED.");
    else
        eventLogger.Warning("Machine", "RESUME is rejected by state machine.");

    return result;
}

bool MachineController::CompleteMachine()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "CompleteMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Complete();

    if (result)
        eventLogger.Info("Machine", "Machine is now COMPLETED.");
    else
        eventLogger.Warning("Machine", "COMPLETE is rejected by state machine.");

    return result;
}

std::string MachineController::GetMachineStateString()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "GetMachineStateString(): No machine selected.");
        return "Invalid Machine.";
    }

    return currentMachine->getStateMachine().GetStateString();
}

bool MachineController::HomeRobot()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "HomeRobot(): No machine selected.");
        return false;
    }

    eventLogger.Info("Robot", "Executing HOME command.");

    bool result = currentMachine->getRobot().Home();

    if (result)
        eventLogger.Info("Robot", "Robot homed successfully.");
    else
        eventLogger.Warning("Robot", "Robot failed at going HOME. Please check!");

    return result;
}

bool MachineController::MoveRobotToPosition(int position)
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "MoveRobotToPosition(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getRobot().MoveToPosition(position);

    if (result)
        eventLogger.Info("Robot", "Robot moved to assigned position.");
    else
        eventLogger.Warning("Robot", "Moving Robot to assigned position is failed.");

    return result;
}

int MachineController::GetRobotPosition()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getRobot().GetCurrentPosition();
}

double MachineController::GetPumpPressure()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getPump().GetPressure();
}

double MachineController::GetCurrentFlowRate()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getFlowController().GetCurrentFlowRate();
}

bool MachineController::StartPump(double targetPressure)
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

    if (!currentMachine->getPump().SetTargetPressure(targetPressure))
        return false;

    return currentMachine->getPump().Start();
}

bool MachineController::StopPump()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

    return currentMachine->getPump().Stop();
}

bool MachineController::OpenFlow(double targetFlowRate)
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

    if (!currentMachine->getFlowController().SetTargetFlowRate(targetFlowRate))
        return false;

    return currentMachine->getFlowController().Open();
}

bool MachineController::CloseFlow()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return false;
    }

    return currentMachine->getFlowController().Close();
}

double MachineController::ReadTemperature()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }
      
    return currentMachine->getTemperatureSensor().ReadValue();
}

double MachineController::ReadPressure()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getPressureSensor().ReadValue();
}

double MachineController::ReadFlow()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getFlowSensor().ReadValue();
}

double MachineController::ReadVacuum()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getVacuumSensor().ReadValue();
}

double MachineController::GetTemperature()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

	return ReadTemperature();
}

double MachineController::GetPressure()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadPressure();
}

double MachineController::GetFlow()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadFlow();
}

double MachineController::GetVacuum()
{
    if (currentMachine == nullptr)
    {
        eventLogger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadVacuum();
}

const EventLogger& MachineController::GetEventLogger() const
{
	return eventLogger;
}
