#include "olcPixelGameEngine.h"
#include "MemoryUnit.h"
#include "DisplayUnit.h"
#include "DisassemblyView.h"
#include <thread>
#include "CPU.h"

MemoryUnit MemoryUnitObj;

void startDisplay() {
	DisplayUnit DisplayUnitObj(&MemoryUnitObj.memory);
	int ScreenX = 32;
	int ScreenY = 24;
	int Multiplier = 20;
	if (DisplayUnitObj.Construct(ScreenX * Multiplier, ScreenY * Multiplier, 2, 2)) {
		DisplayUnitObj.Start();
	}
}

int main()
{
	DisassemblyView DisassemblyViewObj(&MemoryUnitObj);
	CPU cpu(&MemoryUnitObj);
	
	std::thread t1(startDisplay);
	std::thread t2(&CPU::start_execution, cpu);
	// Join the thread with the main thread
	t1.join();
	t2.join();

	/*if (DisassemblyViewObj.Construct(500, 500, 2, 2))
		DisassemblyViewObj.Start();*/
	


	return 0;
}