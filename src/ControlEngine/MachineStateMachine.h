#pragma once
#include <string>

enum class MachineState
{
    Offline = 0,
    Initializing,
    Ready,
    Running,
    Paused,
    Stopping,
    Completed,
    Error,
    EmergencyStop,
    Maintenance
};

class MachineStateMachine
{
private:
    MachineState currentState;

public:
    MachineStateMachine();

    MachineState GetCurrentState() const;
    std::string GetStateString() const;

    bool Initialize();
    bool Start();
    bool Pause();
    bool Resume();
    bool Stop();
    bool Complete();
    bool SetError();
    bool EmergencyStop();
    bool Reset();
};