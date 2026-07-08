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

    bool connect();
    bool disconnect();

    bool home();
    bool moveToPosition(int position);

    bool isConnected() const;
    RobotStatus getStatus() const;
    void setStatus(RobotStatus newStatus);
    std::string getStatusString() const;

    int getCurrentPosition() const;
    void setCurrentPosition(int position);

};
