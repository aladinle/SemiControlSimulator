                           OperatorUI (WPF)
                                  │
                                  ▼
                       IMachineController
                                  ▲
                                  │
                         MachineController
                ┌─────────────────┼─────────────────┐
                ▼                 ▼                 ▼
         EventLogger        AlarmManager      IMachineManager
                │                 │                 │
                │                 │                 ▼
                │                 │          MachineManager
                │                 │                 │
                │                 ▼                 ▼
                │         MachineStateMachine    Machine
                │                                   │
                ▼                                   ▼
         Controllers                        Sensors