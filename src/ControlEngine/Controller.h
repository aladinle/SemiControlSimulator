#pragma once
#include <string>
#include "../ControlEngine/Device.h"

enum class ControllerState
{
    Disabled = 0,
    Enabled = 1,
    Faulted = 2,
    EmergencyStopped = 3
};

class Controller : public Device
{
protected:
    ControllerState controllerState;

public:
    Controller(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    virtual bool Enable();
    virtual bool Disable();
    virtual bool Reset();
    virtual bool EmergencyStop();

    bool IsEnabled() const;

    ControllerState GetControllerState() const;
    std::string GetControllerStateText() const;
};