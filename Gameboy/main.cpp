#include "olcPixelGameEngine.h"
#include "MemoryUnit.h"
#include "DisplayUnit.h"
#include "DisassemblyView.h"

int main()
{

	MemoryUnit MemoryUnitObj;
	MemoryUnitObj.load_rom("..\\roms\\Tetris.gb");
	MemoryUnitObj.load_vram("..\\roms\\VRAM_TEST_DATA\\VRAM.dump");

	DisassemblyView DisassemblyViewObj(&MemoryUnitObj.memory);

	DisplayUnit DisplayUnitObj(&MemoryUnitObj.memory);

	int ScreenX = 32;
	int ScreenY = 24;
	int Multiplier = 20;
	if (DisplayUnitObj.Construct(ScreenX*Multiplier, ScreenY * Multiplier, 2, 2))
		DisplayUnitObj.Start();

	/*if (DisassemblyViewObj.Construct(500, 500, 2, 2))
		DisassemblyViewObj.Start();*/


	return 0;
}