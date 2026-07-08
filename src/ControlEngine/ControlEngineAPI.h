#pragma once

#ifdef CONTROLENGINE_EXPORTS
#define CONTROLENGINE_API __declspec(dllexport)
#else
#define CONTROLENGINE_API __declspec(dllimport)
#endif // CONTROLENGINE_EXPORTS

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

