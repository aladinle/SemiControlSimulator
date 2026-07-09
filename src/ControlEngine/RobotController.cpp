#include "RobotController.h"

RobotController::RobotController(const std::string& name,
	const std::string& model,
	const std::string& serialNumber)
	: Controller(name, model, serialNumber),
	status(RobotStatus::Disconnected),
	currentPosition(0)
{
}

bool RobotController::Connect() 
{
	// Simulate connection logic
	Device::Connect();
	Enable();
	status = RobotStatus::Ready;
	return true;
}

bool RobotController::Disconnect() 
{
	// Simulate disconnection logic
	Disable();
	Device::Disconnect();
	status = RobotStatus::Disconnected;
	return true;
}

bool RobotController::Home() 
{
	if (status != RobotStatus::Ready) 
	{
		return false;		
	}
	
	status = RobotStatus::Busy;
	currentPosition = 0;
	status = RobotStatus::Ready;
	return true;
}

bool RobotController::MoveToPosition(int position) 
{
	if (status != RobotStatus::Ready) 
	{
		return false;		
	}
	
	status = RobotStatus::Busy;
	currentPosition = position;
	status = RobotStatus::Ready;
	return true;
}

bool RobotController::IsConnected() const 
{
	return status != RobotStatus::Disconnected;
}

RobotStatus RobotController::GetStatus() const 
{
	return status;
}

std::string RobotController::GetStatusString() const 
{
	switch (status) 
	{
		case RobotStatus::Disconnected:
			return "Disconnected";
		case RobotStatus::Ready:
			return "Ready";
		case RobotStatus::Busy:
			return "Busy";
		case RobotStatus::Error:
			return "Error";
		default:
			return "Unknown Status";
	}
}

void RobotController::SetStatus(RobotStatus newStatus) 
{
	status = newStatus;
}

int RobotController::GetCurrentPosition() const 
{
	return currentPosition;
}

void RobotController::SetCurrentPosition(int position) 
{
	currentPosition = position;
}