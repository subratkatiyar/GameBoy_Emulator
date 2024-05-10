#include "memory.h"
// #include "stdio.h"

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

void execute_decrease_2(GameboyMemory *memory, GameboyRegisters *registers){
    printf("DEC C\n");
    uint8_t original_value = registers->c;
    (registers->c)--;

    if(registers->c == 0x00 ){
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

void execute_decrease(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode){
    switch(opcode){
        case 0x05:
            execute_decrease_1(memory, registers);
            break;
        case 0x0D:
            execute_decrease_2(memory, registers);
            break;
    }
}