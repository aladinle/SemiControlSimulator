#pragma once

enum class AlarmCode
{
    // System
    MachineNotSelected,
    InvalidMachineIndex,

    // Robot
    RobotHomeFailed,
    RobotMoveFailed,

    // Pump
    PumpStartFailed,
    PumpPressureLow,

    // Flow
    FlowOpenFailed,

    // Temperature
    TemperatureHigh,

    // Emergency
    EmergencyStop
};