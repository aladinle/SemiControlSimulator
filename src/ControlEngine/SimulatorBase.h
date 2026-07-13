#pragma once

class SimulatorBase
{
protected:
    bool running;

public:
    SimulatorBase();
    virtual ~SimulatorBase() = default;

    virtual void Start();
    virtual void Stop();
    virtual void Update(double deltaTime) = 0;
    virtual void Reset() = 0;

    bool IsRunning() const;
};