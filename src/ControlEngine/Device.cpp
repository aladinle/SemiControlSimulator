#include "Device.h"

Device::Device(const std::string& name,
    const std::string& model,
    const std::string& serialNumber)
    : name(name),
    model(model),
    serialNumber(serialNumber),
    connectionState(DeviceConnectionState::Disconnected)
{
}

bool Device::Connect()
{
    connectionState = DeviceConnectionState::Connected;
    return true;
}

bool Device::Disconnect()
{
    connectionState = DeviceConnectionState::Disconnected;
    return true;
}

bool Device::IsConnected() const
{
    return connectionState == DeviceConnectionState::Connected;
}

const std::string& Device::GetName() const
{
    return name;
}

const std::string& Device::GetModel() const
{
    return model;
}

const std::string& Device::GetSerialNumber() const
{
    return serialNumber;
}

DeviceConnectionState Device::GetConnectionState() const
{
    return connectionState;
}

std::string Device::GetConnectionStateText() const
{
    switch (connectionState)
    {
    case DeviceConnectionState::Disconnected:
        return "Disconnected";
    case DeviceConnectionState::Connected:
        return "Connected";
    case DeviceConnectionState::Error:
        return "Error";
    default:
        return "Unknown";
    }
}