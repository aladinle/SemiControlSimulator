#pragma once
#include <string>
#include "RobotController.h"
#include "MotionController.h"

enum class MachineState
{
	Idle = 0,
	Running = 1,
	Error = 2,
	Maintenance = 3
};

class Machine
{
private:
	std::string id;
	std::string type;
	MachineState state;

	RobotController robot;
	MotionController motion;

public:
	Machine(const std::string& id, const std::string& type);
	
	void start();
	void stop();
	void setError();
	void reset();
	
	const std::string& getId() const;
	const std::string& getType() const;
	MachineState getState() const;

	RobotController& getRobot();
	MotionController& getMotion();
};