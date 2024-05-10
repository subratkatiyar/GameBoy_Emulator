#pragma once

#include "olcPixelGameEngine.h"
#include "MemoryUnit.h"

// Override base class with your custom functionality
class DisassemblyView : public olc::PixelGameEngine
{
	private:
		int yOffset = 0;
		int lineHeight = 10;
		int bytesPerLine = 16;
		uint32_t startAddress = 0;
		void DrawMemory();
		std::string ByteToHexString(uint8_t);
	public:
		GameboyMemory* memory;
		DisassemblyView(GameboyMemory*);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;
};
