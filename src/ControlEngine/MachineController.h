#pragma once

#include "../ControlEngine/Machine.h"
#include "../ControlEngine/MachineManager.h"
#include "../ControlEngine/IMachineController.h"
#include "../ControlEngine/EventLogger.h"
#include "../ControlEngine/AlarmManager.h"

class MachineController : public IMachineController
{
private:
    IMachineManager* machineManager;
    Machine* currentMachine;

	EventLogger logger;
    AlarmManager alarmManager;

public:
    MachineController(IMachineManager* machineManager);

	bool SelectMachine(int index);

    bool InitializeMachine();
    bool StartMachine();
    bool StopMachine();
    bool EmergencyStop();
    bool ResetMachine();
    bool PauseMachine();
    bool ResumeMachine();
    bool CompleteMachine();

    std::string GetMachineStateString();

    bool HomeRobot();
    bool MoveRobotToPosition(int position);
    int GetRobotPosition();

    double GetPumpPressure();
    double GetCurrentFlowRate();
    bool StartPump(double targetPressure);
    bool StopPump();

    bool OpenFlow(double targetFlowRate);
    bool CloseFlow();

    double ReadTemperature();
    double ReadPressure();
    double ReadFlow();
    double ReadVacuum();

    double GetTemperature();
    double GetPressure();
    double GetFlow();
    double GetVacuum();

	const EventLogger& GetEventLogger() const;
    AlarmManager& GetAlarmManager();
};

