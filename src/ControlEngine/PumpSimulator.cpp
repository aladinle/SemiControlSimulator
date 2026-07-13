#include "PumpSimulator.h"

PumpSimulator::PumpSimulator()
    : RampSimulator(0.0,    // initial pressure
                    0.8,    // bar per second
                    0.0001)
{
}

void PumpSimulator::Start(double targetPressure)
{
    if (targetPressure < 0.0)
    {
        return;
    }

    RampSimulator::Start(targetPressure);
}

double PumpSimulator::GetCurrentPressure() const
{
    return GetCurrentValue();
}

double PumpSimulator::GetTargetPressure() const
{
    return GetTargetValue();
}