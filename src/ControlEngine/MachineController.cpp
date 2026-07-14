#include "MachineController.h"
#include <iostream>

// ============================================================
// Construction and machine selection
// ============================================================

MachineController::MachineController(IMachineManager* machineManager)
    : machineManager(machineManager),
    currentMachine(nullptr),
    logger(),
    alarmManager(&logger),
    simulationEngine()
{
}

bool MachineController::SelectMachine(int index)
{
    if (machineManager == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "MachineManager is null.",
            AlarmSeverity::Critical);

        return false;
    }

    currentMachine = machineManager->getMachine(index);

    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::InvalidMachineIndex,
            "Machine",
            "Invalid machine index selected.",
            AlarmSeverity::Critical);

        return false;
    }

    alarmManager.SetStateMachine(&currentMachine->getStateMachine());

    simulationEngine.Reset();

    logger.Info("Machine", "Machine selected successfully.");

    return true;
}

// ============================================================
// Machine lifecycle
// ============================================================

bool MachineController::InitializeMachine()
{
    std::cout << "Current state before Initialize: "
        << currentMachine->getStateMachine().GetStateString()
        << "\n";

    if (currentMachine == nullptr)
    {
        //logger.Error("Machine", "No machine selected.");
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
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

    const bool result = currentMachine->getStateMachine().Initialize();

    if (result)
    {
        logger.Info("Machine", "Initialization successful. Machine is READY.");
    }
    else
    {
        logger.Warning("Machine", "Initialization was rejected by the state machine.");
    }

    return result;
}

bool MachineController::StartMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "StartMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    logger.Info("Machine", "Starting machine.");

    bool result = currentMachine->getStateMachine().Start();

    if (result)
    {
        logger.Info("Machine", "Machine is now RUNNING.");
    }
    else
    {
        logger.Warning("Machine", "Start rejected by state machine.");
    }

    return result;
}

bool MachineController::StopMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "StopMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    logger.Info("Machine", "Stopping machine.");

    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();
    currentMachine->getMotion().Stop();

    // Return all simulated values to their initial states.
    simulationEngine.Reset();

    const bool result = currentMachine->getStateMachine().Stop();

    if (result)
    {
        logger.Info("Machine", "Machine is now STOPPED.");
    }
    else
    {
        logger.Warning("Machine", "STOP is rejected by state machine.");
    }

    return result;
}

bool MachineController::EmergencyStop()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "EmergencyStop failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    currentMachine->getMotion().Stop();
    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();

    simulationEngine.Reset();

    const bool result = currentMachine->getStateMachine().EmergencyStop();

    if (result)
    {
        logger.Info("Machine", "Machine is now EMERGENCY STOPPED.");
    }
    else
    {
        logger.Warning("Machine", "EMERGENCY STOPPED is rejected by state machine.");
    }

    return result;
}

bool MachineController::ResetMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "ResetMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    simulationEngine.Reset();

    currentMachine->getPump().Stop();
    currentMachine->getFlowController().Close();
    currentMachine->getMotion().Stop();

    const bool result = currentMachine->getStateMachine().Reset();

    if (result)
    {
        logger.Info("Machine", "Machine is now RESETTED.");
    }
    else
    {
        logger.Warning("Machine", "RESET is rejected by state machine.");
    }

    return result;    
}

bool MachineController::PauseMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "PauseMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    const bool result = currentMachine->getStateMachine().Pause();

    if (result)
    { 
        simulationEngine.Stop();
        logger.Info("Machine", "Machine is now PAUSED.");
    }
    else
    {
        logger.Warning("Machine", "PAUSE is rejected by state machine.");
    }

    return result;
}

bool MachineController::ResumeMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "ResumeMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    const bool result = currentMachine->getStateMachine().Resume();

    if (result)
    {
        simulationEngine.Start();
        logger.Info("Machine", "Machine is now RESUMED.");
    }
    else 
    {
        logger.Warning("Machine", "RESUME is rejected by state machine.");
    }

    return result;
}

bool MachineController::CompleteMachine()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Machine",
            "CompleteMachine failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    const bool result = currentMachine->getStateMachine().Complete();

    if (result)
    {
        simulationEngine.Stop();
        logger.Info("Machine", "Machine is now COMPLETED.");
    }
    else
    {
        logger.Warning("Machine", "COMPLETE is rejected by state machine.");
    }

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

// ============================================================
// Robot control
// ============================================================

bool MachineController::HomeRobot()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Robot",
            "HomeRobot failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    logger.Info("Robot", "Executing HOME command.");

    const bool result = currentMachine->getRobot().Home();

    if (result)
    {
        logger.Info("Robot", "Robot homed successfully.");
    }
    else
    {
        //logger.Warning("Robot", "Robot failed at going HOME. Please check!");
        alarmManager.RaiseAlarm(
            AlarmCode::RobotHomeFailed,
            "Robot",
            "Robot HOME failed.",
            AlarmSeverity::Error);
    }
        
    return result;
}

bool MachineController::MoveRobotToPosition(int position)
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Robot",
            "MoveRobotToPosition failed: no machine selected.",
            AlarmSeverity::Critical);
        return false;
    }

    const bool result = currentMachine->getRobot().MoveToPosition(position);

    if (result)
    {
        logger.Info("Robot", "Robot moved to assigned position.");
    }
    else
    {
        //logger.Warning("Robot", "Moving Robot to assigned position is failed.");
        alarmManager.RaiseAlarm(
            AlarmCode::RobotMoveFailed,
            "Robot",
            "Robot move command failed.",
            AlarmSeverity::Error);
    }

    return result;
}

int MachineController::GetRobotPosition()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return -1;
    }

	return currentMachine->getRobot().GetCurrentPosition();
}

// ============================================================
// Pump control and simulation
// ============================================================

double MachineController::GetPumpPressure()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

    return simulationEngine.GetPumpSimulator().GetCurrentPressure();
}

double MachineController::GetCurrentFlowRate()
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return 0.0;
    }

	return currentMachine->getFlowController().GetCurrentFlowRate();
}

bool MachineController::StartPump(double targetPressure)
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Pump",
            "StartPump failed: no machine selected.",
            AlarmSeverity::Critical);

        return false;
    }

    if (targetPressure < 0.0)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::PumpStartFailed,
            "Pump",
            "Target pressure cannot be negative.",
            AlarmSeverity::Error);

        return false;
    }

    if (!currentMachine->getPump().SetTargetPressure(targetPressure))
    {
        alarmManager.RaiseAlarm(
            AlarmCode::PumpStartFailed,
            "Pump",
            "Failed to configure target pressure.",
            AlarmSeverity::Error);

        return false;
    }

    if (!currentMachine->getPump().Start())
    {
        alarmManager.RaiseAlarm(
            AlarmCode::PumpStartFailed,
            "Pump",
            "Pump controller failed to start.",
            AlarmSeverity::Error);

        return false;
    }

    simulationEngine.GetPumpSimulator().Start(targetPressure);

    logger.Info("Pump", "Pump simulation started toward target pressure.");

    return true;
}

bool MachineController::StopPump()
{
    if (currentMachine == nullptr)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::MachineNotSelected,
            "Pump",
            "StopPump failed: no machine selected.",
            AlarmSeverity::Critical);

        return false;
    }

    const bool result = currentMachine->getPump().Stop();

    simulationEngine.GetPumpSimulator().Stop();

    if (result)
    {
        logger.Info("Pump", "Pump stopped.");
    }
    else
    {
        logger.Warning("Pump", "Pump controller failed to stop.");
    }

    return result;
}

bool MachineController::IsPumpStable() const
{
    return simulationEngine.GetPumpSimulator().IsStable();
}

bool MachineController::OpenFlow(double targetFlowRate)
{
    if (currentMachine == nullptr)
    {
        logger.Error("Machine", "No machine selected.");
        return false;
    }

    if (!currentMachine->getFlowController().SetTargetFlowRate(targetFlowRate))
    {
        alarmManager.RaiseAlarm(
            AlarmCode::FlowOpenFailed,
            "Flow",
            "Failed to set target flow rate.",
            AlarmSeverity::Error);

        return false;
    }

    bool result = currentMachine->getFlowController().Open();

    if (!result)
    {
        alarmManager.RaiseAlarm(
            AlarmCode::FlowOpenFailed,
            "Flow",
            "Flow controller failed to open.",
            AlarmSeverity::Error);
    }

    return result;
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

const AlarmManager& MachineController::GetAlarmManager() const
{
    return alarmManager;
}

void MachineController::StartSimulation()
{
    simulationEngine.Start();
    logger.Info("Simulation", "Simulation engine started.");
}

void MachineController::StopSimulation()
{
    simulationEngine.Stop();
    logger.Info("Simulation", "Simulation engine stopped.");
}

void MachineController::ResetSimulation()
{
    simulationEngine.Reset();
    logger.Info("Simulation", "Simulation engine reset.");
}

void MachineController::UpdateSimulation(double deltaTime)
{
    simulationEngine.Update(deltaTime);
}

double MachineController::GetSimulationTime() const
{
    return simulationEngine.GetSimulationTime();
}

SimulationEngine& MachineController::GetSimulationEngine()
{
    return simulationEngine;
}

const SimulationEngine& MachineController::GetSimulationEngine() const
{
    return simulationEngine;
}

void MachineController::RunSimulationUntilIdle(double dt)
{
    StartSimulation();

    while (!IsPumpStable())
    {
        UpdateSimulation(dt);
    }

    StopSimulation();
}
