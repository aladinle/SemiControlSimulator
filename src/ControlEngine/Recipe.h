#pragma once

#include <string>
#include <vector>

#include "RecipeStep.h"

class Recipe
{
private:
    std::string name;
    std::vector<RecipeStep> steps;

public:
    Recipe(const std::string& name);

    void AddStep(const RecipeStep& step);

    const std::string& GetName() const;

    const std::vector<RecipeStep>& GetSteps() const;

    size_t GetStepCount() const;
};