#pragma once

#include "RampSimulator.h"

class PumpSimulator : public RampSimulator
{
public:
    PumpSimulator();

    void Start(double targetPressure);

    double GetCurrentPressure() const;
    double GetTargetPressure() const;
};