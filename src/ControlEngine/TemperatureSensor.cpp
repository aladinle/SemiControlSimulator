#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Sensor(name, model, serialNumber, "C"),
    simulatedTemperature(25.0)
{
}

double TemperatureSensor::ReadValue()
{
    if (!IsConnected())
        return 0.0;

    value = simulatedTemperature;
    return value;
}

void TemperatureSensor::SetSimulatedTemperature(double temperature)
{
    simulatedTemperature = temperature;
}