#pragma once

#include "SimulatorBase.h"

class RampSimulator : public SimulatorBase
{
protected:
    double initialValue;
    double currentValue;
    double targetValue;

    double rampRate;
    double tolerance;

public:
    RampSimulator(double initialValue, double initialRampRate, double tolerance = 0.0001);
    virtual ~RampSimulator() = default;

    virtual void Start(double target);
    virtual void Stop() override;

    virtual void Update(double deltaTime) override;
    virtual void Reset() override;

    double GetCurrentValue() const;
    double GetTargetValue() const;
    double GetRampRate() const;

    bool IsStable() const;

    void SetRampRate(double newRampRate);
};
