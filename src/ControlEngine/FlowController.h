#pragma once
#include <string>
#include "../ControlEngine/Controller.h"

enum class FlowStatus
{
    Closed = 0,
    Open = 1,
    Error = 2
};

class FlowController : public Controller
{
private:
    FlowStatus status;
    double currentFlowRate;
    double targetFlowRate;

public:
    FlowController(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    bool Connect() override;
    bool Disconnect() override;

    bool Open();
    bool Close();
    bool SetTargetFlowRate(double flowRate);

    double GetCurrentFlowRate() const;
    double GetTargetFlowRate() const;

    FlowStatus GetStatus() const;
    std::string GetStatusString() const;
};