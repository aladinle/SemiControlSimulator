#include "MotionController.h"

MotionController::MotionController(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Controller(name, model, serialNumber),
    status(MotionStatus::Disabled),
    currentPosition(0.0),
    currentVelocity(0.0),
    enabled(false)
{
}

bool MotionController::Connect()
{
    Device::Connect();
    status = MotionStatus::Disabled;
    return true;
}

bool MotionController::Disconnect()
{
    Device::Disconnect();
    enabled = false;
    status = MotionStatus::Disabled;
    return true;
}

bool MotionController::Enable()
{
    if (!IsConnected())
        return false;

    enabled = true;
    status = MotionStatus::Ready;
    return true;
}

bool MotionController::Disable()
{
    enabled = false;
    currentVelocity = 0.0;
    status = MotionStatus::Disabled;
    return true;
}

bool MotionController::Home()
{
    if (!enabled || status != MotionStatus::Ready)
        return false;

    status = MotionStatus::Moving;
    currentVelocity = 10.0;

    currentPosition = 0.0;

    currentVelocity = 0.0;
    status = MotionStatus::Ready;

    return true;
}

bool MotionController::MoveAbsolute(double position)
{
    if (!enabled || status != MotionStatus::Ready)
        return false;

    status = MotionStatus::Moving;
    currentVelocity = 25.0;

    currentPosition = position;

    currentVelocity = 0.0;
    status = MotionStatus::Ready;

    return true;
}

bool MotionController::MoveRelative(double distance)
{
    return MoveAbsolute(currentPosition + distance);
}

bool MotionController::Stop()
{
    currentVelocity = 0.0;

    if (enabled)
        status = MotionStatus::Ready;
    else
        status = MotionStatus::Disabled;

    return true;
}

bool MotionController::IsEnabled() const
{
    return enabled;
}

bool MotionController::IsMoving() const
{
    return status == MotionStatus::Moving;
}

double MotionController::GetCurrentPosition() const
{
    return currentPosition;
}

double MotionController::GetCurrentVelocity() const
{
    return currentVelocity;
}

MotionStatus MotionController::GetStatus() const
{
    return status;
}

std::string MotionController::GetStatusString() const
{
    switch (status)
    {
    case MotionStatus::Disabled:
        return "Disabled";
    case MotionStatus::Ready:
        return "Ready";
    case MotionStatus::Moving:
        return "Moving";
    case MotionStatus::Error:
        return "Error";
    default:
        return "Unknown";
    }
}