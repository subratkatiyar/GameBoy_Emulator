#include "CPU.h"
#include <iomanip>
#include <iostream>

void CPU::execute_JP_nn() {
	MemoryUnitObj->registers.pc++;
	uint16_t nn = MemoryUnitObj->read_memory_16_le(MemoryUnitObj->registers.pc);
	MemoryUnitObj->registers.pc = nn;
	std::cout << "jp " << std::setw(4) << std::setfill('0') << std::hex << nn << "\n";
}

void CPU::execute_JR_NZ_n() {
	MemoryUnitObj->registers.pc++;
	int8_t n = (int8_t)MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc); // Unsigned to signed 
	MemoryUnitObj->registers.pc++;
	if (!MemoryUnitObj->get_flag(FLAG_Z)) {
		MemoryUnitObj->registers.pc += n;
	}

	std::cout<<"jr nz," << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.pc << "\n";
}