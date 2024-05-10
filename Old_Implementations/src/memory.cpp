#include "memory.h"
#include <stdbool.h>
// #include "INS_load.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cstddef>
#include <cstdint>

// Flag constants
#define FLAG_Z 0b10000000 // Zero flag
#define FLAG_N 0b01000000 // Subtract flag
#define FLAG_H 0b00100000 // Half-carry flag
#define FLAG_C 0b00010000 // Carry flag

void dump_memory(GameboyMemory *memory, uint16_t startAddr, uint16_t size){
    for (uint16_t i = startAddr; i < startAddr+size; i += 16) {
        for (uint16_t j = 0; j < 16; j++) {
            // printf("%02X ", read_memory(memory, i+j));
        }
        // printf("\n");
    }
}
void initialize_memory_regions(GameboyMemory *memory){
    memset(memory->eram, 0xFF, sizeof(memory->eram));
    memset(memory->notuse, 0x00, sizeof(memory->notuse)); // Careful with memset.

    uint8_t IORegister[] = {
        0xcf, 0x00, 0x7e, 0xff, 0xab, 0x00, 0x00, 0xf8,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1,
        0x80, 0xbf, 0xf3, 0xff, 0xbf, 0xff, 0x3f, 0x00,
        0xff, 0xbf, 0x7f, 0xff, 0x9f, 0xff, 0xbf, 0xff,
        0xff, 0x00, 0x00, 0xbf, 0x77, 0xf3, 0xf1, 0xff, 
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Randomly Generated
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // Randomly Generated
        0x91, 0x85, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfc, 
        0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
    };

    for (uint16_t addr = 0xFF00; addr <= 0xFF7F; addr++) {
        write_memory(memory, addr, IORegister[addr-0xFF00]);
    }

}

void initialize_gameboy(GameboyMemory *memory, GameboyRegisters *registers) {
    // Initialize memory to zero
    memset(memory, 0, sizeof(GameboyMemory));
    memory->ie = 0; // Interrupts disabled initially
    
    // Additional initialization if needed
    initialize_memory_regions(memory);
    // Set initial values
    registers->af = 0x01B0;  // Example: Set flags (Z=0, N=1, H=1, C=0)
    registers->bc = 0x0013;  // Example: Set BC register pair
    registers->de = 0x00D8;  // Example: Set DE register pair
    registers->hl = 0x014D;  // Example: Set HL register pair
    registers->sp = 0xFFFE;  // Example: Set Stack Pointer
    registers->pc = 0x0100;  // Example: Set Program Counter

}

// Getter functions
bool get_zero_flag(GameboyRegisters *registers) {
    return (registers->f & FLAG_Z) != 0;
}

bool get_subtract_flag(GameboyRegisters *registers) {
    return (registers->f & FLAG_N) != 0;
}

bool get_half_carry_flag(GameboyRegisters *registers) {
    return (registers->f & FLAG_H) != 0;
}

bool get_carry_flag(GameboyRegisters *registers) {
    return (registers->f & FLAG_C) != 0;
}

// Setter functions
void set_zero_flag(GameboyRegisters *registers, bool value) {
    if (value) {
        registers->f |= FLAG_Z;
    } else {
        registers->f &= ~FLAG_Z;
    }
}

void set_subtract_flag(GameboyRegisters *registers, bool value) {
    if (value) {
        registers->f |= FLAG_N;
    } else {
        registers->f &= ~FLAG_N;
    }
}

void set_half_carry_flag(GameboyRegisters *registers, bool value) {
    if (value) {
        registers->f |= FLAG_H;
    } else {
        registers->f &= ~FLAG_H;
    }
}

void set_carry_flag(GameboyRegisters *registers, bool value) {
    if (value) {
        registers->f |= FLAG_C;
    } else {
        registers->f &= ~FLAG_C;
    }
}

// Function to read from memory
uint8_t read_memory(GameboyMemory *memory, uint16_t address) {
    if (address < ROM_SIZE) {
        return memory->rom[address];
    } else if (address < ROM_SIZE + VRAM_SIZE) {
        return memory->vram[address - ROM_SIZE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
        return memory->eram[address - ROM_SIZE - VRAM_SIZE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
        return memory->wram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM) {
        return memory->echoram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE) {
        return memory->oam[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE) {
        return memory->notuse[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE) {
        return memory->io[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE];
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE + HRAM_SIZE) {
        return memory->hram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE - IO_SIZE];
    } else {
        return memory->ie;
    }
}

uint16_t read_memory_16_le(GameboyMemory *memory, uint16_t pc) {
    uint8_t low_byte = read_memory(memory, pc);       // Read lower byte (least significant byte)
    uint8_t high_byte = read_memory(memory, pc + 1);  // Read higher byte (most significant byte)

    // Combine the bytes to form a 16-bit instruction in little-endian order
    uint16_t data = (high_byte << 8) | low_byte;

    return data;
}

// Function to write to memory
void write_memory(GameboyMemory *memory, uint16_t address, uint8_t value) {
    if (address < ROM_SIZE) {
        memory->rom[address] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE) {
        memory->vram[address - ROM_SIZE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE) {
        memory->eram[address - ROM_SIZE - VRAM_SIZE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE) {
        memory->wram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM) {
        memory->echoram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE) {
        memory->oam[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE) {
        memory->notuse[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE) {
        memory->io[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE] = value;
    } else if (address < ROM_SIZE + VRAM_SIZE + ERAM_SIZE + WRAM_SIZE + ECHO_RAM + OAM_SIZE + NOT_USABLE + IO_SIZE + HRAM_SIZE) {
        memory->hram[address - ROM_SIZE - VRAM_SIZE - ERAM_SIZE - WRAM_SIZE - ECHO_RAM - OAM_SIZE - NOT_USABLE - IO_SIZE] = value;
    } else {
        memory->ie = value;
    }
}

int load_rom(GameboyMemory *memory, const char *filename){

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    file.read(reinterpret_cast<char*>(memory->rom), ROM_SIZE);


    if (!file) {
        std::cerr << "Error reading file: " << filename << std::endl;
        return 1;
    }

    // Output the number of bytes read
    std::cout << "Read " << file.gcount() << " bytes from " << filename << std::endl;

    // Close the file
    file.close();

    return 0;
}

int load_vram(GameboyMemory *memory, const char *filename){

    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    file.read(reinterpret_cast<char*>(memory->vram), VRAM_SIZE);


    if (!file) {
        std::cerr << "Error reading file: " << filename << std::endl;
        return 1;
    }

    // Output the number of bytes read
    std::cout << "Read " << file.gcount() << " bytes from " << filename << std::endl;

    // Close the file
    file.close();

    return 0;
}