#include "Machine.h"

Machine::Machine(const std::string& id, const std::string& type)
    : id(id),
    type(type),
    robot("Wafer Transfer Robot", "SIM-1000", "RB-001"),
    motion("Linear Motion Controller", "LMC-2000", "MC-001"),
    pump("Vacuum Pump", "VP-3000", "PMP-001"),
    flow("Flow Controller", "FC-4000", "FC-001"),
    temperatureSensor("Temperature Sensor", "TS-5000", "TS-001"),
    pressureSensor("Pressure Sensor", "PS-6000", "PS-001"),
    flowSensor("Flow Sensor", "FS-7000", "FS-001"),
    vacuumSensor("Vacuum Sensor", "VS-8000", "VS-001")
{
}

bool Machine::start()
{
	return stateMachine.Start();
}

bool Machine::stop()
{
    return stateMachine.Stop();
}   
    
bool Machine::setError()
{
	return stateMachine.SetError();
}

bool Machine::reset()
{
	return stateMachine.Reset();
}

const std::string& Machine::getId() const
{
    return id;
}

const std::string& Machine::getType() const
{
    return type;
}

MachineState Machine::getState() const
{
    return stateMachine.GetCurrentState();
}

RobotController& Machine::getRobot()
{
    return robot;
}

MotionController& Machine::getMotion()
{
    return motion;
}

PumpController& Machine::getPump()
{
    return pump;
}

FlowController& Machine::getFlowController()
{
    return flow;
}

TemperatureSensor& Machine::getTemperatureSensor()
{
    return temperatureSensor;
}

PressureSensor& Machine::getPressureSensor()
{
    return pressureSensor;
}

FlowSensor& Machine::getFlowSensor()
{
    return flowSensor;
}

VacuumSensor& Machine::getVacuumSensor()
{
    return vacuumSensor;
}

MachineStateMachine& Machine::getStateMachine()
{
    return stateMachine;
}