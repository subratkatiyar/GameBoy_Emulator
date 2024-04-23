#include "memory.h"
#include <stdio.h>
#include <assert.h>

void execute_unimplemented() {
    // Print an error message
    printf("Error: Instruction not implemented\n");

    // Use assert to terminate the program
    assert(0); // This will cause the program to terminate with an error message
}

void get_registers_value(GameboyRegisters *registers){
    printf("AF = 0x%04X ", registers->af);
    printf("BC = 0x%04X ", registers->bc);
    printf("DE = 0x%04X ", registers->de);
    printf("HL = 0x%04X ", registers->hl);
    printf("SP = 0x%04X ", registers->sp);
    printf("PC = 0x%04X\n ", registers->pc);
    
}

void execute_no_operation(GameboyRegisters *registers){
    printf("NOP\n");
    registers->pc = registers->pc + 0x01;
}

void execute_jump(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t addressLoc = registers->pc + 0x01;
    uint16_t address = read_memory_16_le(memory, addressLoc);
    printf("JP 0x%04X\n", address); 
    registers->pc = address;
}

void execute_xor(GameboyRegisters *registers){
    printf("XOR A\n"); 
    registers->a = 0x00;
    registers->f = 1<<7;
    registers->pc += 0x01;
}

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

void execute_decrease_1(GameboyMemory *memory, GameboyRegisters *registers){
    printf("DEC B\n");
    uint8_t original_value = registers->b;
    (registers->b)--;

    if(registers->b == 0x00 ){
        registers->f |= (1 << 7);  // Set zero flag (Z = 1)
    }
    else{
        registers->f &= ~(1 << 7); // Clear zero flag (Z = 0)
    }

    // Set subtraction flag (N = 1) to indicate subtraction operation
    registers->f |= (1 << 6);  // Set subtraction flag (N = 1)

    // Set half-carry flag (H) if there was a borrow from bit 4 to bit 3
    if ((original_value & 0x0F) == 0x00) {
        registers->f |= (1 << 5);  // Set half-carry flag (H = 1)
    } else {
        registers->f &= ~(1 << 5); // Clear half-carry flag (H = 0)
    }

    registers->pc += 0x01;
}

void execute_conditional_jump_1(GameboyMemory *memory, GameboyRegisters *registers){
    uint16_t valueLoc = registers->pc + 0x01;
    uint16_t value = read_memory_16_le(memory, valueLoc);

    printf("JR NZ 0x%04X\n", value); 


    if((registers->f & (1<<7)) == 0x00){
        registers->pc = value;
    }
    else{
        registers->pc += 0x02;
    }
}

void execute_instruction(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode){
    switch(opcode){
        case 0x00:
            execute_no_operation(registers);
            break;
        case 0xC3:
            execute_jump(memory, registers);
            break;
        case 0xAF:
            execute_xor(registers);
            break;
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
        case 0x05:
            execute_decrease_1(memory, registers);
            break;
        case 0x20:
            execute_conditional_jump_1(memory, registers);
            break;
        default:
            execute_unimplemented();
            break;
    }
    get_registers_value(registers);
}