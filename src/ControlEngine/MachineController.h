#pragma once

#include "../ControlEngine/Machine.h"
#include "../ControlEngine/MachineManager.h"
#include "../ControlEngine/IMachineController.h"
#include "../ControlEngine/EventLogger.h"
#include "../ControlEngine/AlarmManager.h"
#include "../ControlEngine/AlarmCode.h"
#include "SimulationEngine.h"
#include "RecipeExecutor.h"
#include "Recipe.h"
#include "RecipeStep.h"

class MachineController : public IMachineController
{
private:
    IMachineManager* machineManager;
    Machine* currentMachine;

    EventLogger logger;
    AlarmManager alarmManager;
    SimulationEngine simulationEngine;
    
    RecipeExecutor recipeExecutor;

public:
    explicit MachineController(IMachineManager* machineManager);

    bool SelectMachine(int index) override;

    bool InitializeMachine() override;
    bool StartMachine() override;
    bool StopMachine() override;
    bool EmergencyStop() override;
    bool ResetMachine() override;
    bool PauseMachine() override;
    bool ResumeMachine() override;
    bool CompleteMachine() override;

    std::string GetMachineStateString() override;

    bool HomeRobot() override;
    bool MoveRobotToPosition(int position) override;
    int GetRobotPosition() override;

    bool StartPump(double targetPressure) override;
    bool StopPump() override;
    double GetPumpPressure() override;
    bool IsPumpStable() const override;

    bool OpenFlow(double targetFlowRate) override;
    bool CloseFlow() override;
    double GetCurrentFlowRate() override;

    double ReadTemperature();
    double ReadPressure();
    double ReadFlow();
    double ReadVacuum();

    double GetTemperature() override;
    double GetPressure() override;
    double GetFlow() override;
    double GetVacuum() override;

    const EventLogger& GetEventLogger() const;

    AlarmManager& GetAlarmManager();
    const AlarmManager& GetAlarmManager() const;

    void StartSimulation() override;
    void StopSimulation() override;
    void ResetSimulation() override;
    void UpdateSimulation(double deltaTime) override;

    double GetSimulationTime() const override;

    SimulationEngine& GetSimulationEngine();
    const SimulationEngine& GetSimulationEngine() const;

    void RunSimulationUntilIdle(double dt);

    bool ExecuteRecipe(const Recipe& recipe) override;

    RecipeExecutor& GetRecipeExecutor() override;

    bool StartPumpDownRecipe();
    double GetRecipeProgress() const;
    std::string GetRecipeName() const;
    std::string GetRecipeCurrentStep() const;
    RecipeExecutionStatus GetRecipeStatus() const;

    bool StartRecipe(const Recipe& recipe);
    void UpdateRecipe(double deltaTime);
    bool IsRecipeRunning() const;

    // Recipe Timeline
    int GetRecipeStepCount() const;
    int GetRecipeCurrentStepIndex() const;
    std::string GetRecipeStepDescription(int index) const;
};