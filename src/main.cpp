#include <stdio.h>
#include "memory.h"
#include "cpu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GameboyMemory memory;
GameboyRegisters registers;

// Constants
constexpr int SCREEN_WIDTH = 160;
constexpr int SCREEN_HEIGHT = 144;
constexpr int SCALE_FACTOR = 3; // Adjust this to scale the display
constexpr int TILE_SIZE = 8;    // Size of each tile in pixels
constexpr int BG_MAP_SIZE = 32; // Background map size in tiles

// Function to render the display using SFML
void renderDisplay(sf::RenderWindow& window, GameboyMemory& gbMemory) {
    // Create SFML texture
    sf::Texture texture;
    texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Create SFML sprite
    sf::Sprite sprite(texture);

    // Clear the texture (screen)
    texture.update(gbMemory.vram);

    // Render the sprite
    window.clear(sf::Color::White);
    window.draw(sprite);
    window.display();
}

// Function to render a tilemap using SFML
void renderTilemap(sf::RenderWindow& window, GameboyMemory& gbMemory) {
    // Create SFML render texture
    sf::RenderTexture renderTexture;
    renderTexture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Clear the render texture
    renderTexture.clear(sf::Color::White);

    // Iterate over each tile in the background map
    for (int y = 0; y < BG_MAP_SIZE; ++y) {
        for (int x = 0; x < BG_MAP_SIZE; ++x) {
            // Get the tile index from the background map
            int tileIndex = gbMemory.vram[y * BG_MAP_SIZE + x];

            // Render the tile onto the render texture
            for (int row = 0; row < TILE_SIZE; ++row) {
                for (int col = 0; col < TILE_SIZE; ++col) {
                    // Get the pixel color for the current pixel in the tile
                    uint8_t colorIndex = gbMemory.vram[(tileIndex * TILE_SIZE + row) * TILE_SIZE + col];

                    // Determine the color based on the color index (for simplicity, assuming a grayscale palette)
                    sf::Color color;
                    switch (colorIndex) {
                        case 0: color = sf::Color::Black; break;
                        case 1: color = sf::Color(85, 85, 85); break; // Light gray
                        case 2: color = sf::Color(170, 170, 170); break; // Dark gray
                        case 3: color = sf::Color::White; break;
                    }

                    // Render the pixel onto the render texture
                    sf::RectangleShape pixel(sf::Vector2f(1, 1));
                    pixel.setPosition(x * TILE_SIZE + col, y * TILE_SIZE + row);
                    pixel.setFillColor(color);
                    renderTexture.draw(pixel);
                }
            }
        }
    }

    // Display the render texture
    renderTexture.display();

    // Create a sprite from the render texture and render it onto the window
    sf::Sprite tilemapSprite(renderTexture.getTexture());
    window.draw(tilemapSprite);
}

int main() {

    char buffer[99999];
    if (setvbuf(stdout, buffer, _IOFBF, sizeof(buffer)) != 0) {
        perror("Failed to set buffer mode for stdout");
        return -1;
    }


    // Initialize Gameboy
    initialize_gameboy(&memory, &registers);

    // Load ROM into memory (example function, implement as needed)
    if (load_rom(&memory, "E:\\GitWorkDir\\GameBoy_Emulator\\roms\\Tetris.gb") != 0) {
        fprintf(stderr, "Failed to load ROM. Exiting...\n");
        return -1;
    }

    printf("\n");

    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH * SCALE_FACTOR, SCREEN_HEIGHT * SCALE_FACTOR), "Game Boy Emulator");

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Emulator logic here...

        // Render the display
         // Render the tilemap
        renderTilemap(window, memory);
    }
    
    // Emulation loop (execute instructions, handle interrupts, etc.)
    // while (1) {
    //     // Example: Fetch and execute instructions
    //     uint8_t opcode = read_memory(&memory, registers.pc);

    //     printf("OPCODE = 0x%02X: ", opcode);
    //     execute_instruction(&memory, &registers, opcode);
    //     printf("\n");
    // }

    return 0;
}
