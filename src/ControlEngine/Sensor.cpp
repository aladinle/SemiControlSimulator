#include "Sensor.h"

Sensor::Sensor(const std::string& name,
    const std::string& model,
    const std::string& serialNumber,
    const std::string& unit)
    : Device(name, model, serialNumber),
    value(0.0),
    unit(unit)
{
}

double Sensor::GetValue() const
{
    return value;
}

const std::string& Sensor::GetUnit() const
{
    return unit;
}