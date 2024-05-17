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

void MemoryUnit::reset_eram()
{
	for (uint16_t idx = 0x00; idx < ERAM_SIZE; idx++) {
		memory.eram[idx] = 0xFF;
	}
}

void MemoryUnit::reset_ieregister()
{
	memory.ie = 0x00;
}

void MemoryUnit::reset_notusuable()
{
	for (uint16_t idx = 0x00; idx < NOT_USABLE; idx++) {
		memory.notuse[idx] = 0x00;
	}
}

bool MemoryUnit::load_ioregisters(const char* filename)
{
	return read_binary(memory.io, IO_SIZE, filename);
}

// Getter function for FLAG
bool MemoryUnit::get_flag(uint16_t flag)
{
	return (registers.f & flag) != 0;
}

// Setter function for FLAG
void MemoryUnit::set_flag(uint16_t flag, bool value) {
	if (value) {
		registers.f |= flag;
	}
	else {
		registers.f &= ~flag;
	}
}

void MemoryUnit::checknset_halfcarry_flag(uint16_t value) {
	set_flag(FLAG_H, (value & 0x0F) == 0x0F);
}

// Function to read from memory
uint8_t MemoryUnit::read_memory(uint16_t address) {
	if (address < ROM_SIZE) {
		return memory.rom[address];
	}
	else if (address < ROM_SIZE + VRAM_SIZE) {
		return memory.vram[address - ROM_SIZE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
		return memory.eram[address - ROM_SIZE - VRAM_SIZE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
		return memory.wram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM) {
		return memory.echoram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE) {
		return memory.oam[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE) {
		return memory.notuse[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE) {
		return memory.io[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE];
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE + HRAM_SIZE) {
		return memory.hram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE - IO_SIZE];
	}
	else {
		return memory.ie;
	}
}

uint16_t MemoryUnit::read_memory_16_le(uint16_t pc) {
	uint8_t low_byte  = read_memory(pc);       // Read lower byte (least significant byte)
	uint8_t high_byte = read_memory(pc + 1);  // Read higher byte (most significant byte)

	// Combine the bytes to form a 16-bit instruction in little-endian order
	return (high_byte << 8) | low_byte;
}

// Function to write to memory
void MemoryUnit::write_memory(uint16_t address, uint8_t value) {
	if (address < ROM_SIZE) {
		memory.rom[address] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE) {
		memory.vram[address - ROM_SIZE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
		memory.eram[address - ROM_SIZE - VRAM_SIZE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
		memory.wram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM) {
		memory.echoram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE) {
		memory.oam[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE) {
		memory.notuse[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE) {
		memory.io[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE] = value;
	}
	else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE + HRAM_SIZE) {
		memory.hram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE - IO_SIZE] = value;
	}
	else {
		memory.ie = value;
	}
}

