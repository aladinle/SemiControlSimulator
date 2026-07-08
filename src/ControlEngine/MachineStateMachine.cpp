#include "MachineStateMachine.h"

MachineStateMachine::MachineStateMachine()
    : currentState(MachineState::Offline)
{
}

MachineState MachineStateMachine::GetCurrentState() const
{
    return currentState;
}

std::string MachineStateMachine::GetStateString() const
{
    switch (currentState)
    {
    case MachineState::Offline:         return "Offline";
    case MachineState::Initializing:    return "Initializing";
    case MachineState::Ready:           return "Ready";
    case MachineState::Running:         return "Running";
    case MachineState::Paused:          return "Paused";
    case MachineState::Stopping:        return "Stopping";
    case MachineState::Completed:       return "Completed";
    case MachineState::Error:           return "Error";
    case MachineState::EmergencyStop:   return "Emergency Stop";
    case MachineState::Maintenance:     return "Maintenance";
    default:                            return "Unknown";
    }
}

bool MachineStateMachine::Initialize()
{
    if (currentState != MachineState::Offline)
        return false;

    currentState = MachineState::Initializing;
    currentState = MachineState::Ready;
    return true;
}

bool MachineStateMachine::Start()
{
    if (currentState != MachineState::Ready)
        return false;

    currentState = MachineState::Running;
    return true;
}

bool MachineStateMachine::Pause()
{
    if (currentState != MachineState::Running)
        return false;

    currentState = MachineState::Paused;
    return true;
}

bool MachineStateMachine::Resume()
{
    if (currentState != MachineState::Paused)
        return false;

    currentState = MachineState::Running;
    return true;
}

bool MachineStateMachine::Stop()
{
    if (currentState != MachineState::Running &&
        currentState != MachineState::Paused)
        return false;

    currentState = MachineState::Stopping;
    currentState = MachineState::Completed;
    return true;
}

bool MachineStateMachine::Complete()
{
    if (currentState != MachineState::Running)
        return false;

    currentState = MachineState::Completed;
    return true;
}

bool MachineStateMachine::SetError()
{
    currentState = MachineState::Error;
    return true;
}

bool MachineStateMachine::EmergencyStop()
{
    currentState = MachineState::EmergencyStop;
    return true;
}

bool MachineStateMachine::Reset()
{
    currentState = MachineState::Offline;
    return true;
}