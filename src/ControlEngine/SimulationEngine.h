#pragma once

class SimulationEngine
{
private:
	bool running = false;
	double simulationTime = 0.0;

public:
	SimulationEngine();

	void Start();
	void Stop();
	void Reset();

	void Update(double deltaTime);

	bool IsRunning() const;

	double GetSimulationTime() const;
};
