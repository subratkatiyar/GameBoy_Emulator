#include "memory.h"
#include <stdio.h>
#include <assert.h>

void dump_memory_to_file(const char* filename, const GameboyMemory* memory) {
    // Open the file in binary write mode
    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }
    
    // Write each memory section to the file
    size_t total_bytes_written = 0;
    // total_bytes_written += fwrite(memory->rom, 1, ROM_SIZE, file);
    total_bytes_written += fwrite(memory->vram, 1, VRAM_SIZE, file);
    // total_bytes_written += fwrite(memory->eram, 1, ERAM_SIZE, file);
    // total_bytes_written += fwrite(memory->wram, 1, WRAM_SIZE, file);
    // total_bytes_written += fwrite(memory->oam, 1, OAM_SIZE, file);
    // total_bytes_written += fwrite(memory->io, 1, IO_SIZE, file);
    // total_bytes_written += fwrite(memory->hram, 1, HRAM_SIZE, file);
    // total_bytes_written += fwrite(&(memory->ie), 1, sizeof(uint8_t), file);
    
    // Check if all bytes were written
    if (total_bytes_written != ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE + IO_SIZE + HRAM_SIZE + sizeof(uint8_t)) {
        fprintf(stderr, "Error writing memory to file\n");
    } else {
        printf("Memory dumped successfully to %s\n", filename);
    }
    
    // Close the file
    fclose(file);
}


void execute_unimplemented(GameboyMemory *memory) {
    // Print an error message
    printf("Error: Instruction not implemented\n");
    // dump_memory_to_file("E:\\GitWorkDir\\GameBoy_Emulator\\roms\\gameboy_memory_dump.dump", memory);
    fflush(stdout);
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
    printf("LOAD L C\n"); 
    registers->l = registers->c;
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

void execute_return(GameboyMemory *memory, GameboyRegisters *registers){
    printf("RETURN \n"); 
    uint16_t value = read_memory_16_le(memory, registers->sp);
    registers->sp += 0x02;
    registers->pc = value;
}

void execute_disable_interrupts(GameboyRegisters *registers){
    printf("DI \n"); 
    registers->pc += 0x01;
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
        case 0x0D:
            execute_decrease_2(memory, registers);
            break;
        case 0x3E:
            execute_load_6(memory, registers);
            break;
        case 0xF3:
            execute_disable_interrupts(registers);
            break;
        case 0xE0:
            execute_load_7(memory, registers);
            break;

        // case 0x69:
        //     execute_load_5(memory, registers);
        //     break;
        // case 0xC8:
        //     execute_return(memory, registers);
        //     break;
        default:
            execute_unimplemented(memory);
            break;
    }
    get_registers_value(registers);
}