#include "CPU.h"
#include <iomanip>
#include <iostream>

void CPU::execute_LD_B_n() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	MemoryUnitObj->registers.b = n;
	MemoryUnitObj->registers.pc += 1;
	std::cout << "ld b," << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << "\n";
}


void CPU::execute_LD_C_n() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	MemoryUnitObj->registers.c = n;
	MemoryUnitObj->registers.pc += 1;
	std::cout << "ld c," << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << "\n";
}

void CPU::execute_LD_HL_dec_A() {
	MemoryUnitObj->registers.pc++;
	MemoryUnitObj->write_memory(MemoryUnitObj->registers.hl, MemoryUnitObj->registers.a);
	MemoryUnitObj->registers.hl--;
	std::cout << "ldd (hl),a\n";
}

void CPU::execute_LD_A_n() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	MemoryUnitObj->registers.a = n;
	MemoryUnitObj->registers.pc += 1;
	std::cout << "ld a," << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << "\n";
}

void CPU::execute_LD_nn_A() {
	MemoryUnitObj->registers.pc++;
	uint16_t nn = MemoryUnitObj->read_memory_16_le(MemoryUnitObj->registers.pc);
	MemoryUnitObj->write_memory(nn, MemoryUnitObj->registers.a);
	MemoryUnitObj->registers.pc++;
	std::cout << "ld (" << std::setw(4) << std::setfill('0') << std::hex << nn << "),a\n";
}

void CPU::execute_LDH_A_n() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	uint16_t address = 0xFF00 + n;
	MemoryUnitObj->registers.a = MemoryUnitObj->read_memory(address);
	MemoryUnitObj->registers.pc++;
	std::cout << "ld (ff00+" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << "),a\n";
}

void CPU::execute_LDH_n_A() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	uint16_t address = 0xFF00 + n;
	MemoryUnitObj->write_memory(address, MemoryUnitObj->registers.a);
	MemoryUnitObj->registers.pc++;
	std::cout << "ld a,(ff00+" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << ")\n";
}

void CPU::execute_LD_HL_n() {
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	MemoryUnitObj->write_memory(MemoryUnitObj->registers.hl, n);
	MemoryUnitObj->registers.pc++;
	std::cout << "ld (hl)," << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << ")\n";
}