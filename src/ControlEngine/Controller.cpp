#include "Controller.h"

Controller::Controller(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Device(name, model, serialNumber),
    controllerState(ControllerState::Disabled)
{
}

bool Controller::Enable()
{
    if (!IsConnected())
        return false;

    controllerState = ControllerState::Enabled;
    return true;
}

bool Controller::Disable()
{
    controllerState = ControllerState::Disabled;
    return true;
}

bool Controller::Reset()
{
    controllerState = ControllerState::Disabled;
    return true;
}

bool Controller::EmergencyStop()
{
    controllerState = ControllerState::EmergencyStopped;
    return true;
}

bool Controller::IsEnabled() const
{
    return controllerState == ControllerState::Enabled;
}

ControllerState Controller::GetControllerState() const
{
    return controllerState;
}

std::string Controller::GetControllerStateText() const
{
    switch (controllerState)
    {
    case ControllerState::Disabled:
        return "Disabled";
    case ControllerState::Enabled:
        return "Enabled";
    case ControllerState::Faulted:
        return "Faulted";
    case ControllerState::EmergencyStopped:
        return "Emergency Stopped";
    default:
        return "Unknown";
    }
}