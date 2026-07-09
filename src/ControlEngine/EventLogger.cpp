#include "EventLogger.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

std::string EventLogger::GetCurrentTimestamp() const
{
	auto now = std::chrono::system_clock::now();
	auto currentTime = std::chrono::system_clock::to_time_t(now);

	std::tm localTime{};
	localtime_s(&localTime, &currentTime);

	std::ostringstream oss;
	oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}

std::string EventLogger::LogLevelToString(LogLevel level) const
{
	switch (level)
	{
	case LogLevel::INFO:
		return "INFO";
	case LogLevel::WARNING:
		return "WARNING";
	case LogLevel::ERROR:
		return "ERROR";
	case LogLevel::CRITICAL:
		return "CRITICAL";
	default:
		return "UNKNOWN";
	}
}

void EventLogger::LogEvent(LogLevel level, const std::string& component, const std::string& message)
{
	EventLogEntry entry;
	entry.eventId = nextEventId++;
	entry.timestamp = GetCurrentTimestamp();
	entry.level = level;
	entry.component = component;
	entry.message = message;

	logs.push_back(entry);
}

void EventLogger::Info(const std::string& component, const std::string& message)
{
	LogEvent(LogLevel::INFO, component, message);
}

void EventLogger::Warning(const std::string& component, const std::string& message)
{
	LogEvent(LogLevel::WARNING, component, message);
}

void EventLogger::Error(const std::string& component, const std::string& message)
{
	LogEvent(LogLevel::ERROR, component, message);
}

void EventLogger::Critical(const std::string& component, const std::string& message)
{
	LogEvent(LogLevel::CRITICAL, component, message);
}

const std::vector<EventLogEntry>& EventLogger::GetLogs() const
{
	return logs;
}

void EventLogger::ClearLogs()
{
	logs.clear();
}

void EventLogger::PrintLogs() const
{
	for (const auto& entry : logs)
	{
		std::cout << "["
			<< entry.eventId
			<< "] "
			<< "["
			<< entry.timestamp
			<< "] "
			<< LogLevelToString(entry.level)
			<< " | "
			<< entry.component
			<< " | "
			<< entry.message
			<< '\n';
	}
}

