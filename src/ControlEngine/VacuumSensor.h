#pragma once
#include "Sensor.h"

class VacuumSensor : public Sensor
{
private:
    double simulatedVacuum;

public:
    VacuumSensor(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    double ReadValue() override;

    void SetSimulatedVacuum(double vacuum);
};