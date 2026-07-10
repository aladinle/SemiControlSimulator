#include "RecipeManager.h"

#include <iostream>

void RecipeManager::AddRecipe(const Recipe& recipe)
{
    recipes.push_back(recipe);
}

Recipe* RecipeManager::FindRecipe(const std::string& name)
{
    for (auto& recipe : recipes)
    {
        if (recipe.GetName() == name)
            return &recipe;
    }

    return nullptr;
}

const std::vector<Recipe>& RecipeManager::GetRecipes() const
{
    return recipes;
}

void RecipeManager::PrintRecipes() const
{
    std::cout << "\nRecipes\n";
    std::cout << "---------------------------\n";

    for (const auto& recipe : recipes)
    {
        std::cout
            << recipe.GetName()
            << " ("
            << recipe.GetStepCount()
            << " steps)\n";
    }
}