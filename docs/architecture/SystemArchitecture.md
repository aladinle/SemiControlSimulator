SemiControlSimulator/

│

├── .github/

│   └── workflows/

│       └── build.yml                # GitHub Actions (later)

│

├── docs/

│   ├── architecture/

│   │   ├── SystemArchitecture.md

│   │   ├── ControlEngine.md

│   │   ├── MachineStateDiagram.md

│   │   └── DatabaseDesign.md

│   │

│   ├── api/

│   │   ├── ControlEngineAPI.md

│   │   └── RestAPI.md               # Phase 3

│   │

│   ├── ui/

│   │   ├── Dashboard.png

│   │   ├── TestSetup.png

│   │   ├── Login.png

│   │   └── UserManagement.png

│   │

│   ├── testplans/

│   │   ├── RobotTests.md

│   │   ├── MotionTests.md

│   │   └── PumpTests.md

│   │

│   └── screenshots/

│

├── src/

│   │

│   ├── ControlEngine/               # C++ DLL

│   │   ├── Machine/

│   │   ├── Robot/

│   │   ├── Motion/

│   │   ├── Pump/

│   │   ├── Sensor/

│   │   ├── Alarm/

│   │   ├── Logging/

│   │   ├── Testing/

│   │   ├── ControlEngineAPI.cpp

│   │   └── ControlEngineAPI.h

│   │

│   ├── OperatorUI/                  # C# WPF

│   │   ├── Views/

│   │   ├── ViewModels/

│   │   ├── Models/

│   │   ├── Services/

│   │   ├── Controls/

│   │   └── Resources/

│   │

│   ├── ControlEngineTest/           # Console test

│   │

│   └── Shared/

│       ├── Common/

│       ├── Constants/

│       └── Utilities/

│

├── test/

│   ├── UnitTests/

│   ├── IntegrationTests/

│   └── SimulationTests/

│

├── scripts/

│   ├── build.ps1

│   ├── clean.ps1

│   └── run.ps1

│

├── assets/

│   ├── icons/

│   ├── images/

│   └── logos/

│

├── .gitignore

├── LICENSE

├── README.md

├── CHANGELOG.md

└── SemiControlSimulator.sln

