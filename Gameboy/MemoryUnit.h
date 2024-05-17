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

/*
0000	3FFF	16 KiB ROM bank 00	From cartridge, usually a fixed bank
4000	7FFF	16 KiB ROM Bank 01–NN	From cartridge, switchable bank via mapper(if any)

Read from dump
    8000	9FFF	8 KiB Video RAM(VRAM)	In CGB mode, switchable bank 0 / 1

0xFF
    A000	BFFF	8 KiB External RAM	From cartridge, switchable bank if any

Seems to be random
    C000	CFFF	4 KiB Work RAM(WRAM)
    D000	DFFF	4 KiB Work RAM(WRAM)	In CGB mode, switchable bank 1–7
    E000	FDFF	Echo RAM(mirror of C000–DDFF)	Nintendo says use of this area is prohibited.
    FE00	FE9F	Object attribute memory(OAM)

0x00
    FEA0	FEFF	Not Usable	Nintendo says use of this area is prohibited.

Read from dump. 0xFE30 - 0xFE3F seems to be random
    FF00	FF7F	I / O Registers

FF80	FFFE	High RAM(HRAM)

0x00
    FFFF	FFFF	Interrupt Enable register (IE)
*/

// Flag constants
#define FLAG_Z 0b10000000 // Zero flag
#define FLAG_N 0b01000000 // Subtract flag
#define FLAG_H 0b00100000 // Half-carry flag
#define FLAG_C 0b00010000 // Carry flag

class MemoryUnit {
    private:
        bool read_binary(uint8_t*, uint16_t, const char*);
    public:
        GameboyMemory memory;
        GameboyRegisters registers;
        bool load_rom(const char*);
        bool load_vram(const char*);
        bool load_oam(const char*);

        void reset_eram();
        void reset_ieregister();
        void reset_notusuable();
        bool load_ioregisters(const char*);

        bool get_flag(uint16_t);
        void set_flag(uint16_t, bool);
        void checknset_halfcarry_flag(uint16_t flag);
        uint8_t read_memory(uint16_t address);
        uint16_t read_memory_16_le(uint16_t pc);
        void write_memory(uint16_t address, uint8_t value);
};