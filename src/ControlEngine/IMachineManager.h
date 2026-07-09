#pragma once

// Forward declaration of the Machine class
// This is necessary because we are using pointers to Machine in the interface
// avoids unnecessary header dependencies.
class  Machine;

class IMachineManager
{
public:
		virtual ~IMachineManager() = default;

		virtual void Initialize() = 0;

		virtual Machine* getMachine(int index) = 0;
		
		virtual int getMachineCount() const = 0;
};