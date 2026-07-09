**# Architecture:**





&#x20;                    OperatorUI (WPF)

&#x20;                         │

&#x20;                         ▼

&#x20;              IMachineController

&#x20;                         ▲

&#x20;                         │

&#x20;                MachineController

&#x20;                         │

&#x20;                         ▼

&#x20;               IMachineManager

&#x20;                         ▲

&#x20;                         │

&#x20;                 MachineManager

&#x20;                         │

&#x20;               ┌───────┴────────┐

&#x20;               ▼                ▼

&#x20;           Machine 0        Machine 1

&#x20;                 │

&#x20;    ┌─────────┴──────────────┐

&#x20;    ▼                              ▼

MachineStateMachine      Controllers/Sensors



**# Current Layers:**



**Layer				Responsibility**

OperatorUI			Presentation (WPF)

MachineController		Orchestrates machine operations (Facade)

MachineManager			Manages multiple machines

Machine				Represents one equipment instance

MachineStateMachine		Machine lifecycle

Controllers			Control actuators

Sensors				Read measurements

