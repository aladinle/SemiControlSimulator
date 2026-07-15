#pragma once

#include <string>

enum class RecipeCommand
{
    InitializeMachine,
    StartMachine,

    HomeRobot,
    MoveRobot,

    StartPump,
    StopPump,

    OpenFlow,
    CloseFlow,

    Wait,

    CompleteMachine
};

struct RecipeStep
{
    RecipeCommand command;

    double parameter = 0.0;
    
    double durationSeconds = 0.0;

    std::string description;
};