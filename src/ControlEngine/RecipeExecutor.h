#pragma once

#include "Recipe.h"
#include "RecipeExecutionStatus.h"

class IMachineController;

class RecipeExecutor
{
private:
    IMachineController* machineController;
    
    RecipeExecutionStatus status;
    std::string currentRecipeName;
    std::string currentStepDescription;

    int currentStepIndex;
    int totalSteps;

public:
    explicit RecipeExecutor(IMachineController* controller);

    bool ExecuteRecipe(const Recipe& recipe);

    RecipeExecutionStatus GetStatus() const;
    const std::string& GetCurrentRecipeName() const;
    const std::string& GetCurrentStepDescription() const;

    int GetCurrentStepIndex() const;
    int GetTotalSteps() const;
    double GetProgressPercent() const;

private:
    bool ExecuteStep(const RecipeStep& step);
};
