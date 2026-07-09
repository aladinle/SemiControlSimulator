#pragma once
#include <string>
#include "../ControlEngine/Controller.h"

enum class MotionStatus
{
    Disabled = 0,
    Ready = 1,
    Moving = 2,
    Error = 3
};

class MotionController : public Controller
{
private:
    MotionStatus status;
    double currentPosition;
    double currentVelocity;
    bool enabled;

public:
    MotionController(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    bool Connect() override;
    bool Disconnect() override;

    bool Enable();
    bool Disable();

    bool Home();
    bool MoveAbsolute(double position);
    bool MoveRelative(double distance);
    bool Stop();

    bool IsEnabled() const;
    bool IsMoving() const;

    double GetCurrentPosition() const;
    double GetCurrentVelocity() const;

    MotionStatus GetStatus() const;
    std::string GetStatusString() const;
};