#include "memory.h"

void execute_load_1(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_2(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_3(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_4(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_5(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_6(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_7(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load_8(GameboyMemory *memory, GameboyRegisters *registers);
void execute_load(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode);