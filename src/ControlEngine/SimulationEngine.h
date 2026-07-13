#pragma once
#include "RobotSimulator.h"
#include "PumpSimulator.h"

class SimulationEngine
{
private:
	bool running = false;
	double simulationTime = 0.0;

	PumpSimulator pump;
	RobotSimulator robot;

public:
	SimulationEngine();

	void Start();
	void Stop();
	void Reset();

	void Update(double deltaTime);

	bool IsRunning() const;

	double GetSimulationTime() const;

	PumpSimulator& GetPumpSimulator();
	const PumpSimulator& GetPumpSimulator() const;

	RobotSimulator& GetRobotSimulator();
	const RobotSimulator& GetRobotSimulator() const;
};
