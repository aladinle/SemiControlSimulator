#pragma once
#include "Sensor.h"

class TemperatureSensor : public Sensor
{
private:
    double simulatedTemperature;

public:
    TemperatureSensor(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    double ReadValue() override;

    void SetSimulatedTemperature(double temperature);
};