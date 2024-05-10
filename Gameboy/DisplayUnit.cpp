#include "DisplayUnit.h"

void DisplayUnit::DrawTiles()
{
	uint8_t dataArray[] = {
		0x00, 0x00, 0x3c, 0x3c,
		0x66, 0x66, 0x66, 0x66,
		0x66, 0x66, 0x66, 0x66,
		0x3c, 0x3c, 0x00, 0x00
	};
	std::vector<olc::Pixel> colors = {
		olc::WHITE, olc::GREY, olc::DARK_GREY, olc::BLACK
	};

	// Clear the screen
	Clear(olc::BLACK);

	std::pair<int32_t, int32_t> startPoint = { 0, 0 };
	std::pair<int32_t, int32_t> RectangleDimensions = { ScreenWidth(), ScreenHeight()};

	/*DrawRect(startPoint.first, startPoint.second, RectangleDimensions.first, RectangleDimensions.second, olc::WHITE);

	for (int x = startPoint.first; x < startPoint.first + RectangleDimensions.first; x += RectangleDimensions.first / 32) {
		for (int y = startPoint.second; y < startPoint.second + RectangleDimensions.second; y += RectangleDimensions.second/ 24) {
			DrawRect(x, y, RectangleDimensions.first / 16, RectangleDimensions.second / 24, olc::RED);
		}
	}*/
	std::pair<int32_t, int32_t> pixelSize = { RectangleDimensions.first / 256, RectangleDimensions.second / 192 };
	
	// Render the graphics map
	int countX = 1;
	int countY = 1;

	for (int tile_idx = 0; tile_idx < 384; tile_idx++) {

		int tile_xPos = tile_idx%16;
		int tile_yPos = tile_idx/16;

		int memoryStart = (256 * tile_yPos) + (tile_xPos * 16);
		int memoryEnd = memoryStart + 16;

		//std::cout << tile_idx << "->" << memoryStart << " " << memoryEnd << "\n";
		for (uint32_t addr = memoryStart; addr < memoryEnd; addr += 0x02) {
			for (uint8_t bit = 0x00; bit < 0x08; bit++) {
				bool bit1 = memory->vram[addr] & (1 << bit);
				bool bit2 = memory->vram[addr + 1] & (1 << bit);

				uint8_t temp = (bit2 << 0x01) | (bit1 < 0x00);

				int posY = ((addr / 2) * pixelSize.first) - (pixelSize.first * 8 * (tile_idx - tile_yPos));
				int posX = ((8 * (tile_xPos + 1)) - bit) * pixelSize.second;
		
				// Draw the tile using a rectangle shape
				FillRect(posX, posY, pixelSize.first, pixelSize.second, colors[temp]);
			}
		}
		//DrawRect((tile_xPos + 1) * pixelSize.first * 8, (tile_yPos + 1) * pixelSize.second * 8, pixelSize.first * 8, pixelSize.second * 8, olc::BLUE);
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
	//DrawXYAxis();
	DrawTiles();
	
	return true;
}
