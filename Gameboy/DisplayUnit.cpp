#include "DisplayUnit.h"

void DisplayUnit::DrawTileMap()
{

	std::pair<int32_t, int32_t> startPoint = { 0, 0 };
	

	// Render the graphics map
	int countX = 1;
	int countY = 1;

	for (int tile_idx = 0; tile_idx < 384; tile_idx++) {

		DrawTile(tile_idx);
		//DrawRect((tile_xPos + 1) * pixelSize.first * 8, (tile_yPos + 1) * pixelSize.second * 8, pixelSize.first * 8, pixelSize.second * 8, olc::BLUE);
	}
}

void DisplayUnit::DrawTile(int tile_idx) // Function used for TileMap Only.
{
	std::vector<olc::Pixel> colors = {
		olc::WHITE, olc::GREY, olc::DARK_GREY, olc::BLACK
	};

	std::pair<int32_t, int32_t> RectangleDimensions = { ScreenWidth(), ScreenHeight() };
	std::pair<int32_t, int32_t> pixelSize = { RectangleDimensions.first / 256, RectangleDimensions.second / 192 };

	int tile_xPos = tile_idx % 16;
	int tile_yPos = tile_idx / 16;

	uint32_t memoryStart = (256 * tile_yPos) + (tile_xPos * 16);
	uint32_t memoryEnd = memoryStart + 16;

	//std::cout << tile_idx << "->" << memoryStart << " " << memoryEnd << "\n";
	for (uint32_t addr = memoryStart; addr < memoryEnd; addr += 0x02) {
		for (uint8_t bit = 0x00; bit < 0x08; bit++) {
			bool bit1 = memory->vram[addr] & (1 << bit);
			bool bit2 = memory->vram[addr + 1] & (1 << bit);


			uint8_t temp = 0x00;
			if (bit1 && bit2)
				temp = 0x03;
			else if (bit2)
				temp = 0x02;
			else if (bit1)
				temp = 0x01;
			else
				temp = 0x00;

			int posY = ((addr / 2) * pixelSize.first) - (pixelSize.first * 8 * (tile_idx - tile_yPos));
			int posX = ((8 * (tile_xPos + 1)) - bit) * pixelSize.second;

			// Draw the tile using a rectangle shape
			FillRect(350+posX, posY, pixelSize.first, pixelSize.second, colors[temp]);
		}
	}
}

void DisplayUnit::DrawTile(uint8_t tile_idx, int tile_xPos, int tile_yPos)
{
	std::vector<olc::Pixel> colors = {
		olc::WHITE, olc::GREY, olc::DARK_GREY, olc::BLACK
	};

	std::pair<int32_t, int32_t> RectangleDimensions = { ScreenWidth(), ScreenHeight() };
	std::pair<int32_t, int32_t> pixelSize = { RectangleDimensions.first / 256, RectangleDimensions.second / 192 };

	uint32_t memoryStart = (256 * (tile_idx / 16)) + ((tile_idx % 16) * 16);
	uint32_t memoryEnd = memoryStart + 16;

	//std::cout << tile_idx << "->" << memoryStart << " " << memoryEnd << "\n";
	for (uint32_t addr = memoryStart; addr < memoryEnd; addr += 0x02) {
		for (uint8_t bit = 0x00; bit < 0x08; bit++) {
			bool bit1 = memory->vram[addr] & (1 << bit);
			bool bit2 = memory->vram[addr + 1] & (1 << bit);


			uint8_t temp = 0x00;
			if (bit1 && bit2)
				temp = 0x03;
			else if (bit2)
				temp = 0x02;
			else if (bit1)
				temp = 0x01;
			else
				temp = 0x00;

			int posY = ((addr / 2) * pixelSize.first) - (pixelSize.first * 8 * (tile_idx - tile_yPos));
			int posX = ((8 * (tile_xPos + 1)) - bit) * pixelSize.second;

			// Draw the tile using a rectangle shape
			FillRect(posX, posY, pixelSize.first, pixelSize.second, colors[temp]);
		}
	}
}



void DisplayUnit::DrawBGMap()
{
	// Clear the screen
	//Clear(olc::WHITE);
	for (uint8_t tile_x = 0x00; tile_x < 0x12; tile_x++) {
		for (uint8_t tile_y = 0x00; tile_y < 0x14; tile_y++) {
			
			// 20x + y + const
			uint16_t tile_addr = (0x20 * tile_x) + tile_y + 0x1800;
			DrawTile(memory->vram[tile_addr], tile_y, tile_x);
			/*std::cout << std::hex << (tile_addr + 0x8000) << " ";*/
		}
		//std::cout << "\n";
	}
}

void DisplayUnit::DrawOAM()
{
	for (uint8_t addr = 0x00; addr < OAM_SIZE;addr += 4) {
		int xPos = memory->oam[addr+0x01];
		int yPos = memory->oam[addr];
		int tile = memory->oam[addr + 0x02];
		int attribute = memory->oam[addr + 0x03];

		DrawTile(tile, xPos/8 - 1, yPos/8 -2);
		//std::cout << std::hex << xPos << " " << yPos << " " << tile << " " << attribute << "\n";
	}
}

void DisplayUnit::DrawXYAxis()
{
	// Clear the screen
	Clear(olc::WHITE);

	// Draw X axis
	DrawLine(0, ScreenHeight() / 2, ScreenWidth(), ScreenHeight() / 2, olc::WHITE);
	DrawString(ScreenWidth() - 20, ScreenHeight() / 2 + 10, "X", olc::WHITE);

	// Draw Y axis
	DrawLine(ScreenWidth() / 2, 0, ScreenWidth() / 2, ScreenHeight(), olc::WHITE);
	DrawString(ScreenWidth() / 2 + 10, 10, "Y", olc::WHITE);

}

DisplayUnit::DisplayUnit(GameboyMemory* memoryPointer)
{
	// Name your application
	sAppName = "Disassembly View";
	memory = memoryPointer;
}

bool DisplayUnit::OnUserCreate()
{
	// Called once at the start, so create things here
	return true;
}

bool DisplayUnit::OnUserUpdate(float fElapsedTime)
{
	// Clear the screen
	Clear(olc::GREY);
	//DrawXYAxis();
	DrawTileMap();
	DrawBGMap();
	DrawOAM();
	
	return true;
}
