#include "RobotSimulator.h"

RobotSimulator::RobotSimulator()
    : RampSimulator(
        0.0,      // Home position
        200.0)    // mm/sec
{
}

void RobotSimulator::MoveTo(double position)
{
    if (position < 0.0)
    {
        position = 0.0;
    }

    Start(position);
}

double RobotSimulator::GetPosition() const
{
    return GetCurrentValue();
}