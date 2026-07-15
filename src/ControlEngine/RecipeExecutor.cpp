#include "RecipeExecutor.h"
#include "IMachineController.h"

RecipeExecutor::RecipeExecutor(IMachineController* controller)
    :   machineController(controller),
        status (RecipeExecutionStatus::Idle),
        currentRecipeName(),
        currentStepDescription(),
        currentStepIndex(0),
        totalSteps(0)
{
}

bool RecipeExecutor::ExecuteRecipe(const Recipe& recipe)
{
    if (machineController == nullptr)
    {
        status = RecipeExecutionStatus::Failed;
        return false;
    }

    currentRecipeName = recipe.GetName();
    currentStepDescription.clear();
    currentStepIndex = 0;
    totalSteps = static_cast<int>(recipe.GetStepCount());
    status = RecipeExecutionStatus::Running;

    const auto& steps = recipe.GetSteps();

    for (int index = 0; index < totalSteps; ++index)
    {
        currentStepIndex = index;
        currentStepDescription = steps[index].description;

        if (!ExecuteStep(steps[index]))
        {
            status = RecipeExecutionStatus::Failed; 
            return false;
        }
    }

    currentStepIndex = totalSteps;
    currentStepDescription = "Recipe completed!";
    status = RecipeExecutionStatus::Completed;

    return true;
}

RecipeExecutionStatus RecipeExecutor::GetStatus() const
{
    return status;
}

const std::string& RecipeExecutor::GetCurrentRecipeName() const
{
    return currentRecipeName;
}

const std::string& RecipeExecutor::GetCurrentStepDescription() const
{
    return currentStepDescription;
}

int RecipeExecutor::GetCurrentStepIndex() const
{
    return currentStepIndex;
}

int RecipeExecutor::GetTotalSteps() const
{
    return totalSteps;
}

double RecipeExecutor::GetProgressPercent() const
{
    if (totalSteps <= 0)
    {
        return 0.0;
    }

    return static_cast<double>(currentStepIndex) / static_cast<double>(totalSteps) * 100.0;
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
