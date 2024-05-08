#include "memory.h"

void execute_decrease_1(GameboyMemory *memory, GameboyRegisters *registers);
void execute_decrease_2(GameboyMemory *memory, GameboyRegisters *registers);
void execute_decrease(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode);