#include "CPU.h"
#include <iomanip>
#include <iostream>

void CPU::execute_CP_n(){
	MemoryUnitObj->registers.pc++;
	uint8_t n = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
	uint8_t result = MemoryUnitObj->registers.a - n;
	
	MemoryUnitObj->set_flag(FLAG_Z, MemoryUnitObj->registers.c == 0);
	MemoryUnitObj->set_flag(FLAG_N, 1);
	MemoryUnitObj->checknset_halfcarry_flag(result);
	MemoryUnitObj->set_flag(FLAG_C, MemoryUnitObj->registers.a < n);
	MemoryUnitObj->registers.pc++;

	std::cout << "cp a," << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(n) << "\n";

}