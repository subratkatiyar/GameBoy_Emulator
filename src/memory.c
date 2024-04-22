#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_gameboy(GameboyMemory *memory, GameboyRegisters *registers) {
    // Initialize memory to zero
    memset(memory, 0, sizeof(GameboyMemory));
    memory->ie = 0; // Interrupts disabled initially
    
    // Additional initialization if needed
    // Set initial values
    registers->af = 0x01B0;  // Example: Set flags (Z=0, N=1, H=1, C=0)
    registers->bc = 0x0013;  // Example: Set BC register pair
    registers->de = 0x00D8;  // Example: Set DE register pair
    registers->hl = 0x014D;  // Example: Set HL register pair
    registers->sp = 0xFFFE;  // Example: Set Stack Pointer
    registers->pc = 0x0100;  // Example: Set Program Counter
}



uint8_t read_memory(GameboyMemory *memory, uint16_t addr) {
    if (addr < ROM_SIZE) {
        return memory->rom[addr];   // Reading from ROM
    } else if (addr < ROM_SIZE + VRAM_SIZE) {
        return memory->vram[addr - ROM_SIZE];  // Reading from Video RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
        return memory->eram[addr - ROM_SIZE - VRAM_SIZE];  // Reading from External RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
        return memory->wram[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE];  // Reading from Working RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE) {
        return memory->oam[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE];   // Reading from OAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE + IO_SIZE) {
        return memory->io[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - OAM_SIZE];    // Reading from I/O Registers
    } else if (addr < MEM_SIZE - 1) {
        return memory->hram[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - OAM_SIZE - IO_SIZE];  // Reading from High RAM
    } else {
        return memory->ie;  // Interrupt Enable Register
    }
}

uint16_t read_memory_16_le(GameboyMemory *memory, uint16_t pc) {
    uint8_t low_byte = read_memory(memory, pc);       // Read lower byte (least significant byte)
    uint8_t high_byte = read_memory(memory, pc + 1);  // Read higher byte (most significant byte)

    // Combine the bytes to form a 16-bit instruction in little-endian order
    uint16_t data = (high_byte << 8) | low_byte;

    return data;
}

void write_memory(GameboyMemory *memory, uint16_t addr, uint8_t value) {
    printf("0x%04X = 0x%02X --> 0x%02X\n", addr, read_memory(memory, addr), value);
    if (addr < ROM_SIZE) {
        // Writing to ROM (usually ignored in emulation)
    } else if (addr < ROM_SIZE + VRAM_SIZE) {
        memory->vram[addr - ROM_SIZE] = value;  // Writing to Video RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
        memory->eram[addr - ROM_SIZE - VRAM_SIZE] = value;  // Writing to External RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
        memory->wram[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE] = value;  // Writing to Working RAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE) {
        memory->oam[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE] = value;   // Writing to OAM
    } else if (addr < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + OAM_SIZE + IO_SIZE) {
        memory->io[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - OAM_SIZE] = value;    // Writing to I/O Registers
    } else if (addr < MEM_SIZE - 1) {
        memory->hram[addr - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - OAM_SIZE - IO_SIZE] = value;  // Writing to High RAM
    } else {
        memory->ie = value;  // Writing to Interrupt Enable Register
    }
}

int load_rom(GameboyMemory *memory, const char *filename){
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open ROM file '%s'\n", filename);
        return -1;
    }

    // Read ROM data into memory.rom
    printf("ROM file found: Reading into memory\n");
    size_t bytesRead = fread(memory->rom, sizeof(uint8_t), ROM_SIZE, file);
    fclose(file);

    if (bytesRead != ROM_SIZE) {
        fprintf(stderr, "Error: Failed to read ROM file '%s'\n", filename);
        return -1;
    }

    printf("ROM loaded successfully: %s\n", filename);
    return 0;
}