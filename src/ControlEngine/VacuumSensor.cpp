#include "VacuumSensor.h"

VacuumSensor::VacuumSensor(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Sensor(name, model, serialNumber, "Torr"),
    simulatedVacuum(0.001)
{
}

double VacuumSensor::ReadValue()
{
    if (!IsConnected())
        return 0.0;

    value = simulatedVacuum;
    return value;
}

void VacuumSensor::SetSimulatedVacuum(double vacuum)
{
    simulatedVacuum = vacuum;
}