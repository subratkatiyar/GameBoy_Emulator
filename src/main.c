#include <stdio.h>
#include "memory.h"
#include "cpu.h"

GameboyMemory memory;
GameboyRegisters registers;


int main() {

    // Initialize Gameboy
    initialize_gameboy(&memory, &registers);

    // Load ROM into memory (example function, implement as needed)
    if (load_rom(&memory, "E:\\GitWorkDir\\GameBoy_Emulator\\roms\\Tetris.gb") != 0) {
        fprintf(stderr, "Failed to load ROM. Exiting...\n");
        return -1;
    }

    printf("\n");
    // Emulation loop (execute instructions, handle interrupts, etc.)
    while (1) {
        // Example: Fetch and execute instructions
        uint8_t opcode = read_memory(&memory, registers.pc);

        printf("OPCODE = 0x%02X: ", opcode);
        execute_instruction(&memory, &registers, opcode);
        printf("\n");
    }

    return 0;
}
