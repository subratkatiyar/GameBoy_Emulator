#ifndef CPU_H
#define CPU_H

void execute_unimplemented();
void execute_instruction(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode);


#endif /* CPU_H */
