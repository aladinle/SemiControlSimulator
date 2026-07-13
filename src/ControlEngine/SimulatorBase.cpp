#include "SimulatorBase.h"

SimulatorBase::SimulatorBase()
    : running(false)
{
}

void SimulatorBase::Start()
{
    running = true;
}

void SimulatorBase::Stop()
{
    running = false;
}

bool SimulatorBase::IsRunning() const
{
    return running;
}