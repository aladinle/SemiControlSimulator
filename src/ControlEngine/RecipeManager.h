#pragma once
#pragma once

#include <vector>

#include "Recipe.h"

class RecipeManager
{
private:
    std::vector<Recipe> recipes;

public:
    void AddRecipe(const Recipe& recipe);

    Recipe* FindRecipe(const std::string& name);

    const std::vector<Recipe>& GetRecipes() const;

    void PrintRecipes() const;
};