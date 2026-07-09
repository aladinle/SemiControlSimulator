#include "FlowSensor.h"

FlowSensor::FlowSensor(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Sensor(name, model, serialNumber, "sccm"),
    simulatedFlow(15.0)
{
}

double FlowSensor::ReadValue()
{
    if (!IsConnected())
        return 0.0;

    value = simulatedFlow;
    return value;
}

void FlowSensor::SetSimulatedFlow(double flow)
{
    simulatedFlow = flow;
}