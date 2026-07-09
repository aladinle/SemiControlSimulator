#pragma once

#include "../ControlEngine/Device.h"

class Sensor : public Device
{
protected:
    double value;
    std::string unit;

public:
    Sensor(const std::string& name,
        const std::string& model,
        const std::string& serialNumber,
        const std::string& unit);

    virtual double ReadValue() = 0;

    double GetValue() const;
    const std::string& GetUnit() const;
};