#include "RecipeExecutor.h"

RecipeExecutor::RecipeExecutor(IMachineController* controller)
	: machineController(controller),
	status(RecipeExecutionStatus::Idle),
	currentRecipeName(),
	currentStepDescription("Idle"),
	activeSteps(),
	currentStepIndex(0),
	totalSteps(0),
	currentStepElapsed(0.0),
	currentStepStarted(false)
{
}

bool RecipeExecutor::StartRecipe(const Recipe& recipe)
{
	if (machineController == nullptr)
	{
		status = RecipeExecutionStatus::Failed;
		currentStepDescription = "No machine controller";
		return false;
	}

	if (status == RecipeExecutionStatus::Running)
	{
		return false;
	}

	currentRecipeName = recipe.GetName();
	activeSteps = recipe.GetSteps();

	currentStepIndex = 0;
	totalSteps = static_cast<int>(activeSteps.size());

	currentStepElapsed = 0.0;
	currentStepStarted = false;

	if (totalSteps == 0)
	{
		status = RecipeExecutionStatus::Failed;
		currentStepDescription = "Recipe contains no steps";
		return false;
	}

	currentStepDescription = activeSteps.front().description;
	status = RecipeExecutionStatus::Running;

	return true;
}

void RecipeExecutor::Update(double deltaTime)
{
	if (status != RecipeExecutionStatus::Running || deltaTime <= 0.0)
	{
		return;
	}

	if (currentStepIndex >= totalSteps)
	{
		status = RecipeExecutionStatus::Completed;
		currentStepDescription = "Recipe completed";
		return;
	}

	const RecipeStep& step = activeSteps[currentStepIndex];

	currentStepDescription = step.description;

	if (!currentStepStarted)
	{
		if (!ExecuteStep(step))
		{
			status = RecipeExecutionStatus::Failed;
			currentStepDescription = "Failed: " + step.description;
			return;
		}

		currentStepStarted = true;
		currentStepElapsed = 0.0;
	}

	currentStepElapsed += deltaTime;

	if (currentStepElapsed < step.durationSeconds)
	{
		return;
	}

	++currentStepIndex;

	currentStepElapsed = 0.0;
	currentStepStarted = false;

	if (currentStepIndex >= totalSteps)
	{
		status = RecipeExecutionStatus::Completed;
		currentStepDescription = "Recipe completed";
	}
	else
	{
		currentStepDescription = activeSteps[currentStepIndex].description;
	}
}

void RecipeExecutor::Reset()
{
	status = RecipeExecutionStatus::Idle;

	currentRecipeName.clear();
	currentStepDescription = "Idle";

	activeSteps.clear();

	currentStepIndex = 0;
	totalSteps = 0;

	currentStepElapsed = 0.0;
	currentStepStarted = false;
}

bool RecipeExecutor::IsRunning() const
{
	return status == RecipeExecutionStatus::Running;
}

bool RecipeExecutor::ExecuteRecipe(const Recipe& recipe)
{
	if (!StartRecipe(recipe))
	{
		return false;
	}

	constexpr double deltaTime = 0.1;
	constexpr int maxUpdates = 100000;

	int updateCount = 0;

	while (IsRunning() && updateCount < maxUpdates)
	{
		Update(deltaTime);
		++updateCount;
	}

	if (IsRunning())
	{
		status = RecipeExecutionStatus::Failed;
		currentStepDescription = "Recipe execution timed out";
		return false;
	}

	return status == RecipeExecutionStatus::Completed;
}

RecipeExecutionStatus RecipeExecutor::GetStatus() const
{
	return status;
}

const std::string&RecipeExecutor::GetCurrentRecipeName() const
{
	return currentRecipeName;
}

const std::string&RecipeExecutor::GetCurrentStepDescription() const
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

int RecipeExecutor::GetStepCount() const
{
	return static_cast<int>(activeSteps.size());
}

std::string RecipeExecutor::GetStepDescription(int index) const
{
	if (index < 0 || index >= static_cast<int>(activeSteps.size()))
	{
		return "";
	}

	return activeSteps[index].description;
}

const std::vector<RecipeStep>&RecipeExecutor::GetSteps() const
{
	return activeSteps;
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
		return machineController->StartPump(
			step.parameter);

	case RecipeCommand::StopPump:
		return machineController->StopPump();

	case RecipeCommand::OpenFlow:
		return machineController->OpenFlow(
			step.parameter);

	case RecipeCommand::CloseFlow:
		return machineController->CloseFlow();

	case RecipeCommand::Wait:
		// Duration handling already occurs in Update().
		return true;

	case RecipeCommand::CompleteMachine:
		return machineController->CompleteMachine();

	default:
		return false;
	}
}