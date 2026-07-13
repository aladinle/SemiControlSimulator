// ControlEngineTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

#include "MachineManager.h"
#include "MachineController.h"
#include <Recipe.h>
#include <RecipeExecutor.h>
#include <SimulationEngine.h>

namespace
{
    bool Check(bool condition, const std::string& testName)
    {
        if (condition)
        {
            std::cout << "[PASS] " << testName << "\n";
            return true;
        }

        std::cerr << "[FAIL] " << testName << "\n";
        return false;
    }

    bool TestMachineLifecycle(MachineController& controller)
    {
        std::cout << "\n========== MACHINE LIFECYCLE TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.GetMachineStateString() == "Offline",
            "Initial state is Offline");

        allPassed &= Check(
            controller.InitializeMachine(),
            "Initialize machine");

        allPassed &= Check(
            controller.GetMachineStateString() == "Ready",
            "State becomes Ready");

        allPassed &= Check(
            controller.StartMachine(),
            "Start machine");

        allPassed &= Check(
            controller.GetMachineStateString() == "Running",
            "State becomes Running");

        allPassed &= Check(
            controller.PauseMachine(),
            "Pause machine");

        allPassed &= Check(
            controller.GetMachineStateString() == "Paused",
            "State becomes Paused");

        allPassed &= Check(
            controller.ResumeMachine(),
            "Resume machine");

        allPassed &= Check(
            controller.GetMachineStateString() == "Running",
            "State returns to Running");

        return allPassed;
    }

    bool TestRobotController(MachineController& controller)
    {
        std::cout << "\n========== ROBOT CONTROLLER TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.HomeRobot(),
            "Home robot");

        allPassed &= Check(
            controller.GetRobotPosition() == 0,
            "Robot home position is 0");

        allPassed &= Check(
            controller.MoveRobotToPosition(100),
            "Move robot to position 100");

        allPassed &= Check(
            controller.GetRobotPosition() == 100,
            "Robot position is 100");

        return allPassed;
    }

    bool TestPumpController(MachineController& controller)
    {
        std::cout << "\n========== PUMP CONTROLLER TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.StartPump(3.2),
            "Start pump with target pressure 3.2");

        allPassed &= Check(
            controller.GetPumpPressure() == 3.2,
            "Pump pressure reaches 3.2");

        allPassed &= Check(
            controller.StopPump(),
            "Stop pump");

        allPassed &= Check(
            controller.GetPumpPressure() == 0.0,
            "Pump pressure returns to 0");

        return allPassed;
    }

    bool TestFlowController(MachineController& controller)
    {
        std::cout << "\n========== FLOW CONTROLLER TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.OpenFlow(15.0),
            "Open flow controller at 15.0 sccm");

        allPassed &= Check(
            controller.GetCurrentFlowRate() == 15.0,
            "Flow rate reaches 15.0 sccm");

        allPassed &= Check(
            controller.CloseFlow(),
            "Close flow controller");

        allPassed &= Check(
            controller.GetCurrentFlowRate() == 0.0,
            "Flow rate returns to 0");

        return allPassed;
    }

    bool TestSensors(MachineController& controller)
    {
        std::cout << "\n========== SENSOR TEST ==========\n";

        bool allPassed = true;

        const double temperature = controller.GetTemperature();
        const double pressure = controller.GetPressure();
        const double flow = controller.GetFlow();
        const double vacuum = controller.GetVacuum();

        std::cout << "Temperature: " << temperature << "\n";
        std::cout << "Pressure:    " << pressure << "\n";
        std::cout << "Flow:        " << flow << "\n";
        std::cout << "Vacuum:      " << vacuum << "\n";

        allPassed &= Check(
            temperature > 0.0,
            "Temperature sensor returns a value");

        allPassed &= Check(
            pressure >= 0.0,
            "Pressure sensor returns a valid value");

        allPassed &= Check(
            flow >= 0.0,
            "Flow sensor returns a valid value");

        allPassed &= Check(
            vacuum >= 0.0,
            "Vacuum sensor returns a valid value");

        return allPassed;
    }

    bool TestStopMachine(MachineController& controller)
    {
        std::cout << "\n========== MACHINE STOP TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.StopMachine(),
            "Stop machine");

        allPassed &= Check(
            controller.GetMachineStateString() == "Completed",
            "State becomes Completed");

        return allPassed;
    }

    bool TestAlarmManager(MachineController& controller)
    {
        std::cout << "\n========== ALARM MANAGER TEST ==========\n";

        bool allPassed = true;

        AlarmManager& alarmManager = controller.GetAlarmManager();

        const int alarmId = alarmManager.RaiseAlarm(
            AlarmCode::PumpPressureLow,
            "Pump",
            "Pump pressure is below target.",
            AlarmSeverity::Critical);

        allPassed &= Check(
            alarmId > 0,
            "Raise critical alarm");

        allPassed &= Check(
            alarmManager.HasActiveAlarms(),
            "AlarmManager reports active alarms");

        allPassed &= Check(
            alarmManager.GetActiveAlarmCount() == 1,
            "Active alarm count is 1");

        allPassed &= Check(
            controller.GetMachineStateString() == "Error",
            "Critical alarm changes machine state to Error");

        allPassed &= Check(
            alarmManager.IsAlarmActive(alarmId),
            "Raised alarm is active");

        allPassed &= Check(
            alarmManager.AcknowledgeAlarm(alarmId),
            "Acknowledge alarm");

        const Alarm* highestAlarm =
            alarmManager.GetHighestSeverityActiveAlarm();

        allPassed &= Check(
            highestAlarm != nullptr,
            "Highest-severity active alarm exists");

        if (highestAlarm != nullptr)
        {
            std::cout << "Highest Alarm: "
                << highestAlarm->code
                << " | "
                << highestAlarm->description
                << "\n";

            allPassed &= Check(
                highestAlarm->severity == AlarmSeverity::Critical,
                "Highest alarm severity is Critical");

            allPassed &= Check(
                highestAlarm->acknowledged,
                "Highest alarm is acknowledged");
        }

        std::cout << "\nActive alarms:\n";
        alarmManager.PrintActiveAlarms();

        allPassed &= Check(
            alarmManager.ClearAlarm(alarmId),
            "Clear alarm");

        allPassed &= Check(
            !alarmManager.IsAlarmActive(alarmId),
            "Cleared alarm is inactive");

        allPassed &= Check(
            !alarmManager.HasActiveAlarms(),
            "No active alarms remain");

        return allPassed;
    }

    void PrintEventLog(const MachineController& controller)
    {
        std::cout
            << "\n================ EVENT LOG ================\n";

        controller.GetEventLogger().PrintLogs();

        std::cout
            << "===========================================\n";
    }

    bool TestRecipeExecution(IMachineController& controller)
    {
        std::cout << "\n========== RECIPE EXECUTION TEST ==========\n";

        bool allPassed = true;

        allPassed &= Check(
            controller.ResetMachine(),
            "Reset machine before recipe");

        allPassed &= Check(
            controller.GetMachineStateString() == "Offline",
            "Machine state is Offline before recipe");

        Recipe pumpDown("PumpDown");

        pumpDown.AddStep({
            RecipeCommand::InitializeMachine,
            0.0,
            "Initialize Machine"
            });

        pumpDown.AddStep({
            RecipeCommand::StartMachine,
            0.0,
            "Start Machine"
            });

        pumpDown.AddStep({
            RecipeCommand::HomeRobot,
            0.0,
            "Home Robot"
            });

        pumpDown.AddStep({
            RecipeCommand::StartPump,
            3.2,
            "Start Pump"
            });

        pumpDown.AddStep({
            RecipeCommand::OpenFlow,
            15.0,
            "Open Flow"
            });

        RecipeExecutor executor(&controller);

        allPassed &= Check(
            executor.ExecuteRecipe(pumpDown),
            "Execute PumpDown recipe");

        allPassed &= Check(
            controller.GetMachineStateString() == "Running",
            "Machine remains Running after recipe");

        allPassed &= Check(
            controller.GetRobotPosition() == 0,
            "Robot is at home position");

        allPassed &= Check(
            controller.GetPumpPressure() == 3.2,
            "Pump pressure is 3.2");

        allPassed &= Check(
            controller.GetCurrentFlowRate() == 15.0,
            "Flow rate is 15.0");

        return allPassed;
    }

    bool TestSimulationEngine()
    {
        std::cout << "\n========== SIMULATION ENGINE TEST ==========\n";

        bool allPassed = true;

        SimulationEngine simulation;

        allPassed &= Check(simulation.GetSimulationTime() == 0.0, "Initial simulation time is zero");
        allPassed &= Check(!simulation.IsRunning(), "Simulation is initially stopped");
        simulation.Start();
        allPassed &= Check(simulation.IsRunning(), "Simulation started");
        simulation.Update(0.5);
        simulation.Update(0.5);
        simulation.Update(1.0);
        allPassed &= Check(simulation.GetSimulationTime() == 2.0, "Simulation time is 2.0 seconds");
        simulation.Stop();
        allPassed &= Check(!simulation.IsRunning(), "Simulation stopped");
        simulation.Reset();
        allPassed &= Check(simulation.GetSimulationTime() == 0.0, "Simulation reset");
        allPassed &= Check(!simulation.IsRunning(), "Simulation remains stopped after reset");

        return allPassed;
    }
}

int main()
{
	MachineManager machineManager;
	machineManager.Initialize();

	MachineController machineController(&machineManager);

    int machineIndex = 0; // Select the first machine for testing

    if (!machineController.SelectMachine(machineIndex))
    {
        std::cerr << "Unable to select machine.\n";
        return 1;
    }

    Machine* machine = machineManager.getMachine(machineIndex);

    if (machine == nullptr)
    {
        std::cerr << "Machine not found.\n";
        return 1;
    }

    std::cout << "Machine ID: " << machine->getId() << "\n";
    std::cout << "Machine Type: " << machine->getType() << "\n";
	
    bool allTestsPassed = true;

    allTestsPassed &= TestMachineLifecycle(machineController);
    allTestsPassed &= TestRobotController(machineController);
    allTestsPassed &= TestPumpController(machineController);
    allTestsPassed &= TestFlowController(machineController);
    allTestsPassed &= TestSensors(machineController);
    allTestsPassed &= TestStopMachine(machineController);
    allTestsPassed &= TestRecipeExecution(machineController);
    // Alarm test intentionally moves machine into Error.
    allTestsPassed &= TestAlarmManager(machineController);
    
    PrintEventLog(machineController);

    allTestsPassed &= TestSimulationEngine();

    std::cout << "\n===========================================\n";    

    if (allTestsPassed)
    {
        std::cout << "ALL SUBSYSTEM TESTS PASSED\n";
        return 0;
    }

    std::cerr << "ONE OR MORE SUBSYSTEM TESTS FAILED\n";

    return 1;
}