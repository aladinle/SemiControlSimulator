#include "AlarmManager.h"
#include <iostream>

std::string AlarmManager::SeverityToString(AlarmSeverity severity) const
{
	switch (severity)
	{
		case AlarmSeverity::Info:
			return "INFO";
		case AlarmSeverity::Warning:
			return "WARNING";
		case AlarmSeverity::Error:
			return "ERROR";
		case AlarmSeverity::Critical:
			return "CRITICAL";
		default:
			return "UNKNOWN";
	}
}

AlarmManager::AlarmManager(EventLogger* logger, MachineStateMachine* stateMachine): nextAlarmId(1), logger(logger)
{
}

void AlarmManager::SetStateMachine(MachineStateMachine* stateMachine)
{
	this->stateMachine = stateMachine;
}

int AlarmManager::RaiseAlarm(const std::string& code, const std::string& component, const std::string& description, AlarmSeverity severity)
{
	Alarm alarm;
	alarm.id = nextAlarmId++;
	alarm.code = code;
	alarm.component = component;
	alarm.description = description;
	alarm.severity = severity;
	alarm.active = true;

	alarms.push_back(alarm);

	if (logger != nullptr)
	{
		logger->Error(component,
			"Alarm Raised [" + code + "] " + description);
	}

	if (severity == AlarmSeverity::Error ||
		severity == AlarmSeverity::Critical)
	{
		if (stateMachine != nullptr)
		{
			stateMachine->SetError();
		}
	}

	return alarm.id;
}

bool AlarmManager::ClearAlarm(int id)
{
	for (auto& alarm : alarms)
	{
		if (alarm.id == id && alarm.active)
		{
			alarm.active = false;

			if (logger != nullptr)
			{
				logger->Info(alarm.component,
					"Alarm Cleared [" + alarm.code + "] " + alarm.description);
			}

			return true;
		}
	}

	return false;
}

void AlarmManager::ClearAll()
{
	for (auto& alarm : alarms)
	{
		alarm.active = false;
	}

	if (logger != nullptr)
	{
		logger->Info("AlarmManager", "All alarms cleared.");
	}
}

bool AlarmManager::HasActiveAlarms() const
{
	for (const auto& alarm : alarms)
	{
		if (alarm.active)
			return true;
	}

	return false;
}

int AlarmManager::GetActiveAlarmCount() const
{
	int count = 0;

	for (const auto& alarm : alarms)
	{
		if (alarm.active)
			count++;
	}

	return count;
}

const std::vector<Alarm>& AlarmManager::GetAlarms() const
{
	return alarms;
}

void AlarmManager::PrintActiveAlarms() const
{
	for (const auto& alarm : alarms)
	{
		if (!alarm.active)
			continue;

		std::cout << "ALARM "
			<< alarm.id
			<< " | "
			<< alarm.code
			<< " | "
			<< alarm.component
			<< " | "
			<< SeverityToString(alarm.severity)
			<< " | "
			<< alarm.description
			<< "\n";
	}
}
