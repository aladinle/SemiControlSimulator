#include "AlarmManager.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

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

std::string AlarmManager::AlarmCodeToString(AlarmCode code) const
{
	switch (code)
	{
	case AlarmCode::MachineNotSelected:
		return "SYS-0001";

	case AlarmCode::InvalidMachineIndex:
		return "SYS-0002";

	case AlarmCode::RobotHomeFailed:
		return "ROB-0001";

	case AlarmCode::RobotMoveFailed:
		return "ROB-0002";

	case AlarmCode::PumpStartFailed:
		return "PMP-0001";

	case AlarmCode::PumpPressureLow:
		return "PMP-0002";

	case AlarmCode::FlowOpenFailed:
		return "FLOW-0001";

	case AlarmCode::TemperatureHigh:
		return "TMP-0001";

	case AlarmCode::EmergencyStop:
		return "SYS-0003";

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

int AlarmManager::RaiseAlarm(AlarmCode code, const std::string& component, const std::string& description, AlarmSeverity severity)
{
	Alarm alarm;
	alarm.id = nextAlarmId++;
	alarm.code = AlarmCodeToString(code);
	alarm.component = component;
	alarm.description = description;
	alarm.severity = severity;
	alarm.active = true;
	alarm.acknowledged = false;
	alarm.timestamp = GetCurrentTimestamp();

	alarms.push_back(alarm);

	if (logger != nullptr)
	{
		logger->Error(component,
			"Alarm Raised [" + AlarmCodeToString(code) + "] " + description);
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

		std::cout
			<< "ALARM " << alarm.id
			<< " | " << alarm.timestamp
			<< " | " << alarm.code
			<< " | " << alarm.component
			<< " | " << SeverityToString(alarm.severity)
			<< " | "
			<< (alarm.acknowledged
				? "ACKNOWLEDGED"
				: "UNACKNOWLEDGED")
			<< " | " << alarm.description
			<< "\n";
	}
}

std::string AlarmManager::GetCurrentTimestamp() const
{
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime =
		std::chrono::system_clock::to_time_t(now);

	std::tm localTime{};
	localtime_s(&localTime, &currentTime);

	std::ostringstream oss;
	oss << std::put_time(
		&localTime,
		"%Y-%m-%d %H:%M:%S");

	return oss.str();
}

bool AlarmManager::AcknowledgeAlarm(int id)
{
	for (auto& alarm : alarms)
	{
		if (alarm.id == id && alarm.active)
		{
			if (alarm.acknowledged)
				return true;

			alarm.acknowledged = true;

			if (logger != nullptr)
			{
				logger->Info(
					alarm.component,
					"Alarm acknowledged [" +
					alarm.code + "] " +
					alarm.description);
			}

			return true;
		}
	}

	return false;
}

bool AlarmManager::IsAlarmActive(int id) const
{
	for (const auto& alarm : alarms)
	{
		if (alarm.id == id)
			return alarm.active;
	}

	return false;
}

const Alarm* AlarmManager::GetHighestSeverityActiveAlarm() const
{
	const Alarm* highest = nullptr;

	for (const auto& alarm : alarms)
	{
		if (!alarm.active)
			continue;

		if (highest == nullptr ||
			static_cast<int>(alarm.severity) >
			static_cast<int>(highest->severity))
		{
			highest = &alarm;
		}
	}

	return highest;
}