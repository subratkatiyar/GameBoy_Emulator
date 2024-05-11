#include "olcPixelGameEngine.h"
#include "MemoryUnit.h"
#include "DisplayUnit.h"
#include "DisassemblyView.h"
#include <thread>

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

void printHello() {
	/*for (uint8_t idx = 0x00;idx < 0xFF;idx++) {
		if (idx % 2 == 0) {
			MemoryUnitObj.load_oam("..\\roms\\VRAM_TEST_DATA\\OAM.dump");
		}
		else {
			MemoryUnitObj.load_oam("..\\roms\\VRAM_TEST_DATA\\OAM_1_2.dump");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}*/
	
}
int main()
{

	
	MemoryUnitObj.load_rom("..\\roms\\Tetris.gb");
	MemoryUnitObj.load_vram("..\\roms\\VRAM_TEST_DATA\\VRAM.dump");
	MemoryUnitObj.load_oam("..\\roms\\VRAM_TEST_DATA\\OAM.dump");

	DisassemblyView DisassemblyViewObj(&MemoryUnitObj.memory);

	

	
	
	std::thread t1(startDisplay);
	std::thread t2(printHello);
	// Join the thread with the main thread
	t1.join();
	t2.join();

	int test = 10;
	/*if (DisassemblyViewObj.Construct(500, 500, 2, 2))
		DisassemblyViewObj.Start();*/


	return 0;
}