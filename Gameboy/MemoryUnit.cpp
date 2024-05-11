#include "MemoryUnit.h"
#include <fstream>
#include <iostream>
		
bool MemoryUnit::read_binary(uint8_t *startAddr, uint16_t addrRange, const char* filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	file.read(reinterpret_cast<char*>(startAddr), addrRange);

	// Output the number of bytes read
	std::cout << "Read " << file.gcount() << " bytes from " << filename << std::endl;

	// Close the file
	file.close();

	return true;
}

bool MemoryUnit::load_rom(const char* filename) {
	return read_binary(memory.rom, ROM_SIZE, filename);
}

bool MemoryUnit::load_vram(const char* filename) {
	return read_binary(memory.vram, VRAM_SIZE, filename);
}

bool MemoryUnit::load_oam(const char* filename)
{
	return read_binary(memory.oam, OAM_SIZE, filename);
}
