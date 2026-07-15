#pragma once

#include <string>

class Recipe;
class RecipeExecutor;

class IMachineController
{
public:
    virtual ~IMachineController() = default;

    virtual bool SelectMachine(int index) = 0;

    virtual bool InitializeMachine() = 0;
    virtual bool StartMachine() = 0;
    virtual bool PauseMachine() = 0;
    virtual bool ResumeMachine() = 0;
    virtual bool CompleteMachine() = 0;
    virtual bool StopMachine() = 0;
    virtual bool EmergencyStop() = 0;
    virtual bool ResetMachine() = 0;

    virtual bool HomeRobot() = 0;
    virtual bool MoveRobotToPosition(int position) = 0;

    virtual bool IsPumpStable() const = 0;
    virtual bool StartPump(double pressure) = 0;
    virtual bool StopPump() = 0;

    virtual bool OpenFlow(double flowRate) = 0;
    virtual bool CloseFlow() = 0;

    virtual std::string GetMachineStateString() = 0;

    virtual int GetRobotPosition() = 0;

    virtual double GetPumpPressure() = 0;
    virtual double GetCurrentFlowRate() = 0;

    virtual double GetTemperature() = 0;
    virtual double GetPressure() = 0;
    virtual double GetFlow() = 0;
    virtual double GetVacuum() = 0;

    virtual void StartSimulation() = 0;
    virtual void StopSimulation() = 0;
    virtual void ResetSimulation() = 0;
    virtual void UpdateSimulation(double deltaTime) = 0;

    virtual double GetSimulationTime() const = 0;    

    virtual bool ExecuteRecipe(const Recipe& recipe) = 0;
    virtual RecipeExecutor& GetRecipeExecutor() = 0;
};
