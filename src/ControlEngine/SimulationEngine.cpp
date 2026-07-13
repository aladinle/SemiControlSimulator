#include "SimulationEngine.h"
#include "PumpSimulator.h"

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

// Reset engine, reset everything
void SimulationEngine::Reset()
{
	running = false;
	simulationTime = 0.0;

	pump.Reset();
	robot.Reset();
}

// Update engine, update everything
void SimulationEngine::Update(double deltaTime)
{
	if (!running)
	{
		return;
	}
	simulationTime += deltaTime;

	pump.Update(deltaTime);
	robot.Update(deltaTime);
}

bool SimulationEngine::IsRunning() const
{
	return running;
}

double SimulationEngine::GetSimulationTime() const
{
	return simulationTime;
}

PumpSimulator& SimulationEngine::GetPumpSimulator()
{
	return pump;
}

const PumpSimulator& SimulationEngine::GetPumpSimulator() const
{
	return pump;
}

RobotSimulator& SimulationEngine::GetRobotSimulator()
{
	return robot;
}

const RobotSimulator& SimulationEngine::GetRobotSimulator() const
{
	return robot;
}



