#include <stdio.h>
#include "INS_load.h"

void execute_load_1(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint16_t value = read_memory_16_le(memory, valueLoc);
    printf("LOAD HL 0x%04X\n", value); 
    registers->hl = value;
    registers->pc += 0x03;
}

void execute_load_2(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint16_t value = read_memory(memory, valueLoc);
    printf("LOAD C 0x%02X\n", value); 
    registers->c = value;
    registers->pc += 0x02;
}

void execute_load_3(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint16_t value = read_memory(memory, valueLoc);
    printf("LOAD B 0x%02X\n", value); 
    registers->b = value;
    registers->pc += 0x02;
}

void execute_load_4(GameboyMemory *memory, GameboyRegisters *registers){
    uint8_t value = registers->a;
    printf("LOAD *HL A\n"); 
    write_memory(memory, registers->hl, value);
    registers->hl -= 0x01;
    registers->pc += 0x01;
}

void execute_load_5(GameboyMemory *memory, GameboyRegisters *registers){
    printf("LOAD L C\n"); 
    registers->l = registers->c;
    registers->pc += 0x01;
}

void execute_load_6(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint8_t value = read_memory(memory, valueLoc);
    printf("LOAD A 0x%02X\n", value);
    registers->a = value; 
    registers->pc += 0x02;
}

void execute_load_7(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint8_t value = read_memory(memory, valueLoc);
    printf("LOAD FF00+ 0x%02X, A\n", value); 

    uint16_t address = 0xFF00 + value;
    write_memory(memory, address, registers->a);
    
    registers->pc += 0x02;
}

void execute_load_8(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint8_t value = read_memory(memory, valueLoc);
    uint16_t address = 0xFF00 + value;
    printf("LOAD A, FF00+ 0x%02X, A\n", value); 
    value = read_memory(memory, address);
    registers->a = value;
    registers->pc += 0x02;
}

void execute_load(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode){
    switch(opcode){
        case 0x21:
            execute_load_1(memory, registers);
            break;
        case 0x0E:
            execute_load_2(memory, registers);
            break;
        case 0x06:
            execute_load_3(memory, registers);
            break;
        case 0x32:
            execute_load_4(memory, registers);
            break;
        case 0x3E:
            execute_load_6(memory, registers);
            break;
        case 0xE0:
            execute_load_7(memory, registers);
            break;
        case 0xF0:
            execute_load_8(memory, registers);
            break;
    }
}