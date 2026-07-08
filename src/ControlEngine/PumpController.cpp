#include "PumpController.h"

PumpController::PumpController(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Controller(name, model, serialNumber),
    status(PumpStatus::Off),
    pressure(0.0),
    targetPressure(0.0)
{
}

bool PumpController::Connect()
{
    Device::Connect();
	Enable();
    status = PumpStatus::Off;
    return true;
}

bool PumpController::Disconnect()
{
	Disable();
    Device::Disconnect();
    status = PumpStatus::Off;
    pressure = 0.0;
    return true;
}

bool PumpController::Start()
{
    if (!IsConnected())
        return false;

    status = PumpStatus::Running;
    pressure = targetPressure;
    return true;
}

bool PumpController::Stop()
{
    status = PumpStatus::Off;
    pressure = 0.0;
    return true;
}

bool PumpController::SetTargetPressure(double pressureValue)
{
    if (pressureValue < 0)
        return false;

    targetPressure = pressureValue;
    return true;
}

double PumpController::GetPressure() const
{
    return pressure;
}

double PumpController::GetTargetPressure() const
{
    return targetPressure;
}

PumpStatus PumpController::GetStatus() const
{
    return status;
}

std::string PumpController::GetStatusString() const
{
    switch (status)
    {
    case PumpStatus::Off:
        return "Off";
    case PumpStatus::Running:
        return "Running";
    case PumpStatus::Error:
        return "Error";
    default:
        return "Unknown";
    }
}