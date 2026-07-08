#pragma once

#include "../ControlEngine/Machine.h"

class MachineController
{
private:
    Machine* machine;

public:
    MachineController(Machine* machine);

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
};

