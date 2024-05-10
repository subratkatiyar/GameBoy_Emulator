#pragma once
#include <cstdint>


// Define memory regions and sizes
#define MEM_SIZE        0x10000 // Total memory size of Gameboy (64KB)

#define ROM_SIZE        0x8000  // Size of ROM (32KB)
#define VRAM_SIZE       0x2000  // Video RAM size (8KB)
#define ERAM_SIZE       0x2000  // External RAM size (8KB)
#define WRAM_SIZE       0x2000  // Working RAM size (8KB)
#define ECHO_RAM        0x1E00  // Echo Ram [New]
#define OAM_SIZE        0xA0    // Object Attribute Memory size (160 bytes)
#define NOT_USABLE      0x60    // Not Usable [New]
#define IO_SIZE         0x80    // I/O Registers size (128 bytes)
#define HRAM_SIZE       0x7F    // High RAM size (127 bytes)

// Gameboy memory structure
typedef struct {
    uint8_t rom[ROM_SIZE];      // ROM (read-only)
    uint8_t vram[VRAM_SIZE];    // Video RAM
    uint8_t eram[ERAM_SIZE];    // External RAM (cartridge RAM)
    uint8_t wram[WRAM_SIZE];    // Working RAM
    uint8_t echoram[ECHO_RAM];  // Echo Ram [New]
    uint8_t oam[OAM_SIZE];      // Object Attribute Memory
    uint8_t notuse[NOT_USABLE]; // Not Usable [New]
    uint8_t io[IO_SIZE];        // I/O Registers
    uint8_t hram[HRAM_SIZE];    // High RAM
    uint8_t ie;                 // Interrupt Enable Register
} GameboyMemory;

// Define Gameboy CPU Registers
typedef struct {
    union {
        struct {
            uint8_t f;  // Flags register (Z N H C 0 0 0 0)
            uint8_t a;  // Accumulator register
        };
        uint16_t af;    // AF register pair (A + Flags)
    };

    union {
        struct {
            uint8_t c;
            uint8_t b;
        };
        uint16_t bc;    // BC register pair (B + C)
    };

    union {
        struct {
            uint8_t e;
            uint8_t d;
        };
        uint16_t de;    // DE register pair (D + E)
    };

    union {
        struct {
            uint8_t l;
            uint8_t h;
        };
        uint16_t hl;    // HL register pair (H + L)
    };

    uint16_t sp;        // Stack Pointer
    uint16_t pc;        // Program Counter
} GameboyRegisters;

class MemoryUnit {
    private:
        bool read_binary(uint8_t*, uint16_t, const char*);
    public:
        GameboyMemory memory;
        bool load_rom(const char*);
        bool load_vram(const char*);
};