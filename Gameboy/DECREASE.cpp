#include "CPU.h"
#include <iomanip>
#include <iostream>

void CPU::execute_DEC_B() {
	MemoryUnitObj->registers.pc++;
	MemoryUnitObj->registers.b--;

	MemoryUnitObj->set_flag(FLAG_Z, MemoryUnitObj->registers.b == 0);
	MemoryUnitObj->set_flag(FLAG_N, 1);
	MemoryUnitObj->checknset_halfcarry_flag(MemoryUnitObj->registers.b);
	std::cout << "dec b\n";
}

void CPU::execute_DEC_C() {
	MemoryUnitObj->registers.pc++;
	MemoryUnitObj->registers.c--;

	MemoryUnitObj->set_flag(FLAG_Z, MemoryUnitObj->registers.c == 0);
	MemoryUnitObj->set_flag(FLAG_N, 1);
	MemoryUnitObj->checknset_halfcarry_flag(MemoryUnitObj->registers.c);
	std::cout << "dec c\n";
}