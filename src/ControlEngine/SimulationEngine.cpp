#include "SimulationEngine.h"

SimulationEngine::SimulationEngine(): running(false), simulationTime(0.0)
{
}

void SimulationEngine::Start()
{
	running = true;
}

void SimulationEngine::Stop()
{
	running = false;
}

void SimulationEngine::Reset()
{
	running = false;
	simulationTime = 0.0;
}

void SimulationEngine::Update(double deltaTime)
{
	if (!running)
	{
		return;
	}
	simulationTime += deltaTime;
}

bool SimulationEngine::IsRunning() const
{
	return running;
}

double SimulationEngine::GetSimulationTime() const
{
	return simulationTime;
}



