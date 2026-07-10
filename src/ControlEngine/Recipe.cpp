#include "Recipe.h"

Recipe::Recipe(const std::string& name)
    : name(name)
{
}

void Recipe::AddStep(const RecipeStep& step)
{
    steps.push_back(step);
}

const std::string& Recipe::GetName() const
{
    return name;
}

const std::vector<RecipeStep>& Recipe::GetSteps() const
{
    return steps;
}

size_t Recipe::GetStepCount() const
{
    return steps.size();
}