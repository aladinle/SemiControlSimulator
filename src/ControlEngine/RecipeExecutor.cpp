#include "RecipeExecutor.h"

RecipeExecutor::RecipeExecutor(IMachineController* controller)
    : machineController(controller)
{
}

bool RecipeExecutor::ExecuteRecipe(const Recipe& recipe)
{
    for (const auto& step : recipe.GetSteps())
    {
        if (!ExecuteStep(step))
        {
            return false;
        }
    }

    return true;
}

bool RecipeExecutor::ExecuteStep(const RecipeStep& step)
{
    switch (step.command)
    {
        case RecipeCommand::InitializeMachine:
            return machineController->InitializeMachine();

        case RecipeCommand::StartMachine:
            return machineController->StartMachine();

        case RecipeCommand::HomeRobot:
            return machineController->HomeRobot();

        case RecipeCommand::MoveRobot:
            return machineController->MoveRobotToPosition(
                static_cast<int>(step.parameter));

        case RecipeCommand::StartPump:
            return machineController->StartPump(step.parameter);

        case RecipeCommand::StopPump:
            return machineController->StopPump();

        case RecipeCommand::OpenFlow:
            return machineController->OpenFlow(step.parameter);

        case RecipeCommand::CloseFlow:
            return machineController->CloseFlow();

        case RecipeCommand::CompleteMachine:
            return machineController->CompleteMachine();

        default:
            return false;
    }
}