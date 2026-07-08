#pragma once
#include <string>
#include "RobotController.h"
#include "MotionController.h"
#include "PumpController.h"
#include "FlowController.h"
#include "TemperatureSensor.h"
#include "PressureSensor.h"
#include "FlowSensor.h"
#include "VacuumSensor.h"

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
	PumpController pump;
	FlowController flow;
	TemperatureSensor temperatureSensor;
	PressureSensor pressureSensor;
	FlowSensor flowSensor;
	VacuumSensor vacuumSensor;

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
	PumpController& getPump();
	FlowController& getFlowController();
	TemperatureSensor& getTemperatureSensor();
	PressureSensor& getPressureSensor();
	FlowSensor& getFlowSensor();
	VacuumSensor& getVacuumSensor();
};