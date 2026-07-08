#include "Machine.h"

Machine::Machine(const std::string& id, const std::string& type)
    : id(id), type(type), state(MachineState::Idle)
{
}

void Machine::start()
{
    if (state == MachineState::Idle)
    {
        state = MachineState::Running;
    }
}

void Machine::stop()
{
    if (state == MachineState::Running)
    {
        state = MachineState::Idle;
    }
}

void Machine::setError()
{
    state = MachineState::Error;
}

void Machine::reset()
{
    if (state == MachineState::Error)
    {
        state = MachineState::Idle;
    }
}

const std::string& Machine::getId() const
{
    return id;
}

const std::string& Machine::getType() const
{
    return type;
}

MachineState Machine::getState() const
{
    return state;
}