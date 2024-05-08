#include "memory.h"
void execute_jump_1(GameboyMemory *memory, GameboyRegisters *registers);
void execute_conditional_jump_1(GameboyMemory *memory, GameboyRegisters *registers);
void execute_jump(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode);