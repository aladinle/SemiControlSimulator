#pragma once

#include "RampSimulator.h"

class RobotSimulator : public RampSimulator
{
public:
    RobotSimulator();

    void MoveTo(double position);

    double GetPosition() const;
};