#include "PressureSensor.h"

PressureSensor::PressureSensor(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Sensor(name, model, serialNumber, "bar"),
    simulatedPressure(1.0)
{
}

double PressureSensor::ReadValue()
{
    if (!IsConnected())
        return 0.0;

    value = simulatedPressure;
    return value;
}

void PressureSensor::SetSimulatedPressure(double pressure)
{
    simulatedPressure = pressure;
}