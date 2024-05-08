#include <stdio.h>
#include "INS_jump.h"

void execute_jump_1(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t addressLoc = registers->pc + 0x01;
    uint16_t address = read_memory_16_le(memory, addressLoc);
    printf("JP 0x%04X\n", address); 
    registers->pc = address;
}

void execute_conditional_jump_1(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    registers->pc += 0x01;
    int8_t value = (int8_t)read_memory(memory, valueLoc); // Unsigned to signed 
    registers->pc += 0x01;
    printf("JR NZ 0x%02X\n", (registers->pc+(int8_t)value)); 


    if((registers->f & (1<<7)) == 0x00){
        registers->pc +=  value;
    }
}

void execute_jump(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode){
    switch(opcode){
        case 0xC3:
            execute_jump_1(memory, registers);
            break;
        case 0x20:
            execute_conditional_jump_1(memory, registers);
            break;
    }
}