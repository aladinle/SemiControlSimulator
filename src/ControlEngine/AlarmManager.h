#pragma once

#include <string>
#include <vector>
#include "../ControlEngine/EventLogger.h"
#include "../ControlEngine/MachineStateMachine.h"

enum class AlarmSeverity
{
    Info = 0,
    Warning = 1,
    Error = 2,
    Critical = 3
};

struct Alarm
{
    int id;
    std::string code;
    std::string component;
    std::string description;
    AlarmSeverity severity;
    bool active;
};

class AlarmManager
{
private:
    std::vector<Alarm> alarms;
    int nextAlarmId;
    EventLogger* logger;
    MachineStateMachine* stateMachine;

    std::string SeverityToString(AlarmSeverity severity) const;

public:
    AlarmManager(EventLogger* logger = nullptr, MachineStateMachine* stateMachine = nullptr);

    void SetStateMachine(MachineStateMachine* stateMachine);

    int RaiseAlarm(const std::string& code,
        const std::string& component,
        const std::string& description,
        AlarmSeverity severity);

    bool ClearAlarm(int id);
    void ClearAll();

    bool HasActiveAlarms() const;
    int GetActiveAlarmCount() const;

    const std::vector<Alarm>& GetAlarms() const;

    void PrintActiveAlarms() const;
};