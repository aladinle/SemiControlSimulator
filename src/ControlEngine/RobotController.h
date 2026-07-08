#pragma once
#include <string>

enum class RobotStatus 
{
    Disconnected = 0,
    Ready = 1,
    Busy = 2,
    Error = 3
};

class RobotController
{
private:
    std::string name;
    std::string model;
    std::string serialNumber;

    RobotStatus status;
    int currentPosition;

public:
    RobotController(const std::string& name, const std::string& model, const std::string& serialNumber);

    bool connect();
    bool disconnect();
    bool home();
    bool moveToPosition(int position);

    const std::string& GetName() const;
    const std::string& GetModel() const;
    const std::string& GetSerialNumber() const;

    bool isConnected() const;
    RobotStatus getStatus() const;
    std::string getStatusString() const;

    void setStatus(RobotStatus newStatus);
    int getCurrentPosition() const;
    void setCurrentPosition(int position);

};
