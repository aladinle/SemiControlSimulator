#include "RobotController.h"

RobotController::RobotController(const std::string& name,
	const std::string& model,
	const std::string& serialNumber)
	: Controller(name, model, serialNumber),
	status(RobotStatus::Disconnected),
	currentPosition(0)
{
}

bool RobotController::connect() 
{
	// Simulate connection logic
	Device::Connect();
	Enable();
	status = RobotStatus::Ready;
	return true;
}

bool RobotController::disconnect() 
{
	// Simulate disconnection logic
	Disable();
	Device::Disconnect();
	status = RobotStatus::Disconnected;
	return true;
}

bool RobotController::home() 
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

bool RobotController::moveToPosition(int position) 
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

bool RobotController::isConnected() const 
{
	return status != RobotStatus::Disconnected;
}

RobotStatus RobotController::getStatus() const 
{
	return status;
}

std::string RobotController::getStatusString() const 
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

void RobotController::setStatus(RobotStatus newStatus) 
{
	status = newStatus;
}

int RobotController::getCurrentPosition() const 
{
	return currentPosition;
}

void RobotController::setCurrentPosition(int position) 
{
	currentPosition = position;
}