#include "MachineController.h"

MachineController::MachineController(IMachineManager* machineManager)
    : machineManager(machineManager), currentMachine(nullptr), logger(), alarmManager(&logger)
{
}

bool MachineController::SelectMachine(int index)
{
    if (machineManager == nullptr)
    {
        alarmManager.RaiseAlarm(
            "ALM-0001",
            "Machine",
            "MachineManager is null.",
            AlarmSeverity::Critical);

        return false;
    }

    currentMachine = machineManager->getMachine(index);

    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            "ALM-0002",
            "Machine",
            "Invalid machine index selected.",
            AlarmSeverity::Critical);

        return false;
    }

    logger.Info("Machine", "Machine selected successfully.");

    alarmManager.SetStateMachine(&currentMachine->getStateMachine());

    return true;
}

bool MachineController::InitializeMachine()
{
    if (currentMachine == nullptr)
    {
        //logger.Error("Machine", "No machine selected.");
        alarmManager.RaiseAlarm(
            "ALM-0003",
            "Machine",
            "InitializeMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }
        
    logger.Info("Machine", "Initializing machine....");

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
        logger.Error("Machine", "Initialization failed.");
        currentMachine->getStateMachine().SetError();
        return false;
    }

    logger.Info("Machine", "Initialization successful.");

    return currentMachine->getStateMachine().Initialize();
}

bool MachineController::StartMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "StartMachine(): No machine selected.");
        return false;
    }

    logger.Info("Machine", "Starting machine.");

    bool result = currentMachine->getStateMachine().Start();

    if (result)
        logger.Info("Machine", "Machine is now RUNNING.");
    else
        logger.Warning("Machine", "Start rejected by state machine.");

    return result;
}

bool MachineController::StopMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "StopMachine(): No machine selected.");
        return false;
    }

    logger.Info("Machine", "Stopping machine.");

    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    bool result = currentMachine->getStateMachine().Stop();

    if (result)
        logger.Info("Machine", "Machine is now STOPPED.");
    else
        logger.Warning("Machine", "STOP is rejected by state machine.");

    return result;
}

bool MachineController::EmergencyStop()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "EmergencyStop(): No machine selected.");
        return false;
    }

    currentMachine->getMotion().Stop();
    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    logger.Info("Machine", "EEMERGENCY STOPPING machine.");

    bool result = currentMachine->getStateMachine().EmergencyStop();

    if (result)
        logger.Info("Machine", "Machine is now EMERGENCY STOPPED.");
    else
        logger.Warning("Machine", "EMERGENCY STOPPED is rejected by state machine.");

    return result;
}

bool MachineController::ResetMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "ResetMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Reset();

    if (result)
        logger.Info("Machine", "Machine is now RESETTED.");
    else
        logger.Warning("Machine", "RESET is rejected by state machine.");

    return result;    
}

bool MachineController::PauseMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "PauseMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Pause();

    if (result)
        logger.Info("Machine", "Machine is now PAUSED.");
    else
        logger.Warning("Machine", "PAUSE is rejected by state machine.");

    return result;
}

bool MachineController::ResumeMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "ResumeMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Resume();

    if (result)
        logger.Info("Machine", "Machine is now RESUMED.");
    else
        logger.Warning("Machine", "RESUME is rejected by state machine.");

    return result;
}

bool MachineController::CompleteMachine()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "CompleteMachine(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getStateMachine().Complete();

    if (result)
        logger.Info("Machine", "Machine is now COMPLETED.");
    else
        logger.Warning("Machine", "COMPLETE is rejected by state machine.");

    return result;
}

std::string MachineController::GetMachineStateString()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "GetMachineStateString(): No machine selected.");
        return "Invalid Machine.";
    }

    return currentMachine->getStateMachine().GetStateString();
}

bool MachineController::HomeRobot()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "HomeRobot(): No machine selected.");
        return false;
    }

    logger.Info("Robot", "Executing HOME command.");

    bool result = currentMachine->getRobot().Home();

    if (result)
        logger.Info("Robot", "Robot homed successfully.");
    else
    {
        //logger.Warning("Robot", "Robot failed at going HOME. Please check!");
        alarmManager.RaiseAlarm(
            "ROB-0001",
            "Robot",
            "Robot HOME failed.",
            AlarmSeverity::Error);

        currentMachine->getStateMachine().SetError();
    }
        
    return result;
}

bool MachineController::MoveRobotToPosition(int position)
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "MoveRobotToPosition(): No machine selected.");
        return false;
    }

    bool result = currentMachine->getRobot().MoveToPosition(position);

    if (result)
        logger.Info("Robot", "Robot moved to assigned position.");
    else
    {
        //logger.Warning("Robot", "Moving Robot to assigned position is failed.");
        alarmManager.RaiseAlarm(
            "ROB-0002",
            "Robot",
            "Robot move command failed.",
            AlarmSeverity::Error);

        currentMachine->getStateMachine().SetError();
    }

    return result;
}

int MachineController::GetRobotPosition()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getRobot().GetCurrentPosition();
}

double MachineController::GetPumpPressure()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getPump().GetPressure();
}

double MachineController::GetCurrentFlowRate()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return false;
    }

	return currentMachine->getFlowController().GetCurrentFlowRate();
}

bool MachineController::StartPump(double targetPressure)
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
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
        logger.Error("Machine", "No machine selected.");
        return false;
    }

    return currentMachine->getPump().Stop();
}

bool MachineController::OpenFlow(double targetFlowRate)
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
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
        logger.Error("Machine", "No machine selected.");
        return false;
    }

    return currentMachine->getFlowController().Close();
}

double MachineController::ReadTemperature()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }
      
    return currentMachine->getTemperatureSensor().ReadValue();
}

double MachineController::ReadPressure()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getPressureSensor().ReadValue();
}

double MachineController::ReadFlow()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getFlowSensor().ReadValue();
}

double MachineController::ReadVacuum()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return currentMachine->getVacuumSensor().ReadValue();
}

double MachineController::GetTemperature()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

	return ReadTemperature();
}

double MachineController::GetPressure()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadPressure();
}

double MachineController::GetFlow()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadFlow();
}

double MachineController::GetVacuum()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return ReadVacuum();
}

const EventLogger& MachineController::GetEventLogger() const
{
	return logger;
}

AlarmManager& MachineController::GetAlarmManager()
{
    return alarmManager;
}
