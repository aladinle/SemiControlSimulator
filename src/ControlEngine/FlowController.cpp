#include "FlowController.h"

FlowController::FlowController(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : Controller(name, model, serialNumber),
    status(FlowStatus::Closed),
    currentFlowRate(0.0),
    targetFlowRate(0.0)
{
}

bool FlowController::Connect()
{
    Device::Connect();
	Enable();
    status = FlowStatus::Closed;
    return true;
}

bool FlowController::Disconnect()
{
	Disable();
    Device::Disconnect();
    status = FlowStatus::Closed;
    currentFlowRate = 0.0;
    return true;
}

bool FlowController::Open()
{
    if (!IsConnected())
        return false;

    status = FlowStatus::Open;
    currentFlowRate = targetFlowRate;
    return true;
}

bool FlowController::Close()
{
    status = FlowStatus::Closed;
    currentFlowRate = 0.0;
    return true;
}

bool FlowController::SetTargetFlowRate(double flowRate)
{
    if (flowRate < 0.0)
        return false;

    targetFlowRate = flowRate;
    return true;
}

double FlowController::GetCurrentFlowRate() const
{
    return currentFlowRate;
}

double FlowController::GetTargetFlowRate() const
{
    return targetFlowRate;
}

FlowStatus FlowController::GetStatus() const
{
    return status;
}

std::string FlowController::GetStatusString() const
{
    switch (status)
    {
    case FlowStatus::Closed:
        return "Closed";
    case FlowStatus::Open:
        return "Open";
    case FlowStatus::Error:
        return "Error";
    default:
        return "Unknown";
    }
}