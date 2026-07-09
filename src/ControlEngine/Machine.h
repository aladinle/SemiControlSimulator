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
#include "MachineStateMachine.h"

class Machine
{
private:
	std::string id;
	std::string type;

	RobotController robot;
	MotionController motion;
	PumpController pump;
	FlowController flow;
	TemperatureSensor temperatureSensor;
	PressureSensor pressureSensor;
	FlowSensor flowSensor;
	VacuumSensor vacuumSensor;

	MachineStateMachine stateMachine;

public:
	Machine(const std::string& id, const std::string& type);
	
	bool start();
	bool stop();
	bool setError();
	bool reset();
	
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
	MachineStateMachine& getStateMachine();
};