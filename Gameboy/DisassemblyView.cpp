#pragma once
#include "DisassemblyView.h"
#include "MemoryUnit.h"
#include <cstdint>
#include <iomanip>
#include <sstream>

std::string DisassemblyView::ByteToHexString(uint8_t byte)
{
    std::stringstream stream;
    stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    return stream.str();
}

DisassemblyView::DisassemblyView(MemoryUnit *memoryPointer)
{
	// Name your application
	sAppName = "Disassembly View";
    memory = &memoryPointer->memory;
}

void DisassemblyView::DrawMemory()
{

    Clear(olc::BLACK);

    int y = 10 - yOffset;

    for (int i = 0; i < sizeof(GameboyMemory); i += bytesPerLine)
    {
        int yPos = y + lineHeight * (i / bytesPerLine);
        if (yPos < 0 || yPos >= ScreenHeight()) continue;

        // Draw memory address
        std::stringstream addressStream;
        addressStream << std::hex << std::setw(4) << std::setfill('0') << startAddress + i;
        DrawString(10, yPos, addressStream.str(), olc::WHITE);

        for (int j = 0; j < bytesPerLine; ++j)
        {
            if (i + j >= sizeof(GameboyMemory)) break;

            // Draw byte value
            std::string byteStr = ByteToHexString(*((uint8_t*)&memory + i + j));
            DrawString(50 + j * 3 * 5 + j * 3, yPos, byteStr, olc::WHITE);
            DrawString(50 + j * 3 * 5 + j * 3 + 10, yPos, " ", olc::WHITE);

        }
    }
}


bool DisassemblyView::OnUserCreate()
{
	// Called once at the start, so create things here
	return true;
}

bool DisassemblyView::OnUserUpdate(float fElapsedTime)
{

	// Called once per frame, draws random coloured pixels
    if (GetKey(olc::Key::UP).bHeld) 
        if(yOffset>0)
            yOffset -= 1;
        
    if (GetKey(olc::Key::DOWN).bHeld)
        yOffset += 1;

    DrawMemory();
	return true;
}
