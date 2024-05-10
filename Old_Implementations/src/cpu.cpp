#include "memory.h"
// #include "INS_load.h"
// #include "INS_jump.h"
// #include "INS_decrease.h"
#include <assert.h>

// void dump_memory_to_file(const char* filename, const GameboyMemory* memory) {
//     // Open the file in binary write mode
//     FILE* file = fopen(filename, "wb");
//     if (file == NULL) {
//         fprintf(stderr, "Error opening file %s\n", filename);
//         return;
//     }
    
//     // Write each memory section to the file
//     size_t total_bytes_written = 0;
//     // total_bytes_written += fwrite(memory->rom, 1, ROM_SIZE, file);
//     total_bytes_written += fwrite(memory->vram, 1, VRAM_SIZE, file);
//     // total_bytes_written += fwrite(memory->eram, 1, ERAM_SIZE, file);
//     // total_bytes_written += fwrite(memory->wram, 1, WRAM_SIZE, file);
//     // total_bytes_written += fwrite(memory->oam, 1, OAM_SIZE, file);
//     // total_bytes_written += fwrite(memory->io, 1, IO_SIZE, file);
//     // total_bytes_written += fwrite(memory->hram, 1, HRAM_SIZE, file);
//     // total_bytes_written += fwrite(&(memory->ie), 1, sizeof(uint8_t), file);
    
//     // Check if all bytes were written
//     if (total_bytes_written != ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE + IO_SIZE + HRAM_SIZE + sizeof(uint8_t)) {
//         fprintf(stderr, "Error writing memory to file\n");
//     } else {
//         printf("Memory dumped successfully to %s\n", filename);
//     }
    
//     // Close the file
//     fclose(file);
// }


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

void execute_xor(GameboyRegisters *registers){
    printf("XOR A\n"); 
    registers->a = 0x00;
    registers->f = 1<<7;
    registers->pc += 0x01;
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

void execute_compare_1(GameboyMemory *memory, GameboyRegisters *registers){
    // registers->pc += 0x01;
    // int8_t n = (int8_t)read_memory(memory, registers->pc);
    // registers->pc += 0x01;

    // printf("CP A 0x%02X\n", n); 
    // if(registers->a == n)
    //     registers->f = 1;
    // else
    //     registers->z = 0;

}

void execute_instruction(GameboyMemory *memory, GameboyRegisters *registers, uint8_t opcode){
    switch(opcode){
        case 0x00:
            execute_no_operation(registers);
            break;
        case 0xC3:
        case 0x20:
            execute_jump(memory, registers, opcode);
            break;
        case 0xAF:
            execute_xor(registers);
            break;
        case 0x21:
        case 0x0E:
        case 0x06:
        case 0x32:
        case 0x3E:
        case 0xE0:
        case 0xF0:
            execute_load(memory, registers, opcode);
            break;
        case 0x05:
        case 0x0D:
            execute_decrease(memory, registers, opcode);
            break;

        
        
        
        case 0xF3:
            execute_disable_interrupts(registers);
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
    fflush(stdout);
}