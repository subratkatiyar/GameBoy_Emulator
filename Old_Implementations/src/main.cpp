#include "memory.h"
#include "display.h"

GameboyMemory memory;
GameboyRegisters registers;

int main() {
    // show_pallete();
    // char buffer[99999];
    // if (setvbuf(stdout, buffer, _IOFBF, sizeof(buffer)) != 0) {
    //     perror("Failed to set buffer mode for stdout");
    //     return -1;
    // }


    // Initialize Gameboy
    initialize_gameboy(&memory, &registers);
    
    // // Load ROM into memory
    // if (load_rom(&memory, "E:\\GitWorkDir\\GameBoy_Emulator\\roms\\Tetris.gb") != 0) {
    //     fprintf(stderr, "Failed to load ROM. Exiting...\n");
    //     return -1;
    // }

    // // Load VRAM into memory
    // if (load_vram(&memory, "E:\\GitWorkDir\\GameBoy_Emulator\\roms\\VRAM.dump") != 0) {
    //     fprintf(stderr, "Failed to load VRAM. Exiting...\n");
    //     return -1;
    // }
    createTile();
    printf("\n");
    
    // // Emulation loop (execute instructions, handle interrupts, etc.)
    // // while (1) {
    // //     // Example: Fetch and execute instructions
    // //     uint8_t opcode = read_memory(&memory, registers.pc);

    // //     printf("OPCODE = 0x%02X: ", opcode);
    // //     execute_instruction(&memory, &registers, opcode);
    // //     printf("\n");
    // // }

    // return 0;
}
