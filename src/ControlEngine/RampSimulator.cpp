#include "RampSimulator.h"

#include <algorithm>
#include <cmath>

void RampSimulator::SetCurrentValue(double value)
{
    currentValue = value;
}

RampSimulator::RampSimulator(double initialValue,
                             double initialRampRate,
                             double tolerance)
    : initialValue(initialValue),
    currentValue(initialValue),
    targetValue(initialValue),
    rampRate(initialRampRate),
    tolerance(tolerance)
{
}

void RampSimulator::Start(double target)
{
    targetValue = target;
    SimulatorBase::Start();
}

void RampSimulator::Stop()
{
    SimulatorBase::Stop();
}

void RampSimulator::Update(double deltaTime)
{
    if (!running || deltaTime <= 0.0)
    {
        return;
    }

    const double step = rampRate * deltaTime;

    if (currentValue < targetValue)
    {
        currentValue = std::min(currentValue + step, targetValue);
    }
    else if (currentValue > targetValue)
    {
        currentValue = std::max(currentValue - step, targetValue);
    }

    if (IsStable())
    {
        currentValue = targetValue;
    }
}

void RampSimulator::Reset()
{
    running = false;
    currentValue = initialValue;
    targetValue = initialValue;
}

double RampSimulator::GetCurrentValue() const
{
    return currentValue;
}

double RampSimulator::GetTargetValue() const
{
    return targetValue;
}

double RampSimulator::GetRampRate() const
{
    return rampRate;
}

bool RampSimulator::IsStable() const
{
    return std::abs(currentValue - targetValue) <= tolerance;
}

void RampSimulator::SetRampRate(double newRampRate)
{
    if (newRampRate > 0.0)
    {
        rampRate = newRampRate;
    }
}