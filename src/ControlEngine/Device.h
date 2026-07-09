#pragma once
#include <string>

enum class DeviceConnectionState
{
    Disconnected = 0,
    Connected = 1,
    Error = 2
};

class Device
{
protected:
    std::string name;
    std::string model;
    std::string serialNumber;
    DeviceConnectionState connectionState;

public:
    Device(const std::string& name,
        const std::string& model,
        const std::string& serialNumber);

    virtual ~Device() = default;

    virtual bool Connect();
    virtual bool Disconnect();

    bool IsConnected() const;

    const std::string& GetName() const;
    const std::string& GetModel() const;
    const std::string& GetSerialNumber() const;

    DeviceConnectionState GetConnectionState() const;
    std::string GetConnectionStateText() const;
};