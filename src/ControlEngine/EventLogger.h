#pragma once

#include <string>
#include <vector>

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR,
	CRITICAL
};

struct EventLogEntry
{
	LogLevel level;
	int eventId;
	std::string timestamp;
	std::string component;
	std::string message;
};

class EventLogger
{
private:
	std::vector<EventLogEntry> logs;
	int nextEventId = 1;

	std::string GetCurrentTimestamp() const;
	std::string LogLevelToString(LogLevel level) const;

public:
	void LogEvent(LogLevel level, const std::string& component, const std::string& message);

	void Info(const std::string& component, const std::string& message);
	void Warning(const std::string& component, const std::string& message);
	void Error(const std::string& component, const std::string& message);
	void Critical(const std::string& component, const std::string& message);

	const std::vector<EventLogEntry>& GetLogs() const;
	void ClearLogs();

	void PrintLogs() const;
	std::string ToString() const;
};
