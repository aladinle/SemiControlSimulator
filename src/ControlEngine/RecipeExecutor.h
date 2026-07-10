#pragma once

#include "Recipe.h"
#include "../ControlEngine/IMachineController.h"

class RecipeExecutor
{
private:
    IMachineController* machineController;

public:
    explicit RecipeExecutor(IMachineController* controller);

    bool ExecuteRecipe(const Recipe& recipe);

private:
    bool ExecuteStep(const RecipeStep& step);
};