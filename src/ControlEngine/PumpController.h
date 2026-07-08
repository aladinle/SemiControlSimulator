#pragma once
#include <string>
#include "../ControlEngine/Controller.h"

enum class PumpStatus
{
    Off = 0,
    Running = 1,
    Error = 2
};

class PumpController : public Controller
{
private:
    PumpStatus status;
    double pressure;
    double targetPressure;

public:
    PumpController(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    bool Connect() override;
    bool Disconnect() override;

    bool Start();
    bool Stop();
    bool SetTargetPressure(double pressure);

    double GetPressure() const;
    double GetTargetPressure() const;

    PumpStatus GetStatus() const;
    std::string GetStatusString() const;
};