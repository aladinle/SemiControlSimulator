#pragma once

// ControlEngine is built as a static library, so its public functions do not
// use DLL import/export decorations.
#define CONTROLENGINE_API

extern "C" {
    CONTROLENGINE_API void InitializeEngine();

    CONTROLENGINE_API int GetMachineCount();

    CONTROLENGINE_API int StartMachine(int index);

    CONTROLENGINE_API int StopMachine(int index);

    CONTROLENGINE_API int ResetMachine(int index);

    CONTROLENGINE_API int SetMachineError(int index);

    CONTROLENGINE_API int GetMachineState(int index);

	CONTROLENGINE_API int GetMachineId(int index, char* buffer, int bufferSize);

	CONTROLENGINE_API int GetMachineType(int index, char* buffer, int bufferSize);
}

