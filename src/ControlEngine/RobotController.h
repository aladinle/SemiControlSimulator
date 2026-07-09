#pragma once
#include <string>
#include "../ControlEngine/Controller.h"

enum class RobotStatus
{
    Disconnected = 0,
    Ready = 1,
    Busy = 2,
    Error = 3
};

class RobotController : public Controller
{
private:
    RobotStatus status;
    int currentPosition;

public:
    RobotController(const std::string& name, 
                    const std::string& model, 
                    const std::string& serialNumber);

    bool Connect();
    bool Disconnect();

    bool Home();
    bool MoveToPosition(int position);

    bool IsConnected() const;
    RobotStatus GetStatus() const;
    void SetStatus(RobotStatus newStatus);
    std::string GetStatusString() const;

    int GetCurrentPosition() const;
    void SetCurrentPosition(int position);

};
