#pragma once
#include "Sensor.h"

class FlowSensor : public Sensor
{
private:
    double simulatedFlow;

public:
    FlowSensor(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    double ReadValue() override;

    void SetSimulatedFlow(double flow);
};