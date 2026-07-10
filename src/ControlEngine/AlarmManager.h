#pragma once

#include <string>
#include <vector>
#include "../ControlEngine/EventLogger.h"
#include "../ControlEngine/MachineStateMachine.h"
#include "../ControlEngine/AlarmCode.h"

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
    bool acknowledged;
    std::string timestamp;
};

class AlarmManager
{
private:
    std::vector<Alarm> alarms;
    int nextAlarmId;
    EventLogger* logger;
    MachineStateMachine* stateMachine;

    std::string SeverityToString(AlarmSeverity severity) const;
    std::string AlarmCodeToString(AlarmCode code) const;
    std::string GetCurrentTimestamp() const;

public:
    AlarmManager(EventLogger* logger = nullptr, MachineStateMachine* stateMachine = nullptr);

    void SetStateMachine(MachineStateMachine* stateMachine);

    int RaiseAlarm(AlarmCode code,
        const std::string& component,
        const std::string& description,
        AlarmSeverity severity);

    bool ClearAlarm(int id);
    void ClearAll();

    bool HasActiveAlarms() const;
    int GetActiveAlarmCount() const;

    const std::vector<Alarm>& GetAlarms() const;

    void PrintActiveAlarms() const;

    bool AcknowledgeAlarm(int id);
    bool IsAlarmActive(int id) const;

    const Alarm* GetHighestSeverityActiveAlarm() const;
};