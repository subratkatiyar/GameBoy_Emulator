#pragma once
#include "olcPixelGameEngine.h"
#include "MemoryUnit.h"

// Override base class with your custom functionality
class DisplayUnit : public olc::PixelGameEngine
{
	private:
		void DrawTileMap();
		void DrawTile(int);
		void DrawTile(uint8_t, int, int);
		void DrawBGMap();
		void DrawOAM();
		void DrawXYAxis();
	public:
		GameboyMemory* memory;
		DisplayUnit(GameboyMemory*);
		bool OnUserCreate() override;
		bool OnUserUpdate(float fElapsedTime) override;
};

