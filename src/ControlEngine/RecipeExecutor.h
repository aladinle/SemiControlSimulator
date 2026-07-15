#pragma once

#include "Recipe.h"
#include "RecipeExecutionStatus.h"
#include "IMachineController.h"

class RecipeExecutor
{
private:
    IMachineController* machineController;
    
    RecipeExecutionStatus status;
    std::string currentRecipeName;
    std::string currentStepDescription;

    std::vector<RecipeStep> activeSteps;

    int currentStepIndex;
    int totalSteps;
    double currentStepElapsed;
    bool currentStepStarted;

public:
    explicit RecipeExecutor(IMachineController* controller);

    bool StartRecipe(const Recipe& recipe);
    void Update(double deltaTime);
    void Reset();
    bool IsRunning() const;

    bool ExecuteRecipe(const Recipe& recipe);

    RecipeExecutionStatus GetStatus() const;
    const std::string& GetCurrentRecipeName() const;
    const std::string& GetCurrentStepDescription() const;

    int GetCurrentStepIndex() const;
    int GetTotalSteps() const;
    double GetProgressPercent() const;
    const std::vector<RecipeStep>& GetSteps() const;

private:
    bool ExecuteStep(const RecipeStep& step);
};
