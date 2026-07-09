#pragma once
#include "Sensor.h"

class PressureSensor : public Sensor
{
private:
    double simulatedPressure;

public:
    PressureSensor(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    double ReadValue() override;

    void SetSimulatedPressure(double pressure);
};