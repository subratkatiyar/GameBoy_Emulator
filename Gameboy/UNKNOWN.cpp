#include "CPU.h"
#include <iomanip>
#include <iostream>

void CPU::execute_DI() {
	MemoryUnitObj->registers.pc++;
}