#include "display.h"
// Define light grey color
sf::Color lightGrey(192, 192, 192); // RGB values for light grey

// Define dark grey color
sf::Color darkGrey(128, 128, 128); // RGB values for dark grey

std::vector<sf::Color> colors = {
    sf::Color::White, lightGrey, darkGrey, sf::Color::Black
    // Add more colors here...
};

void createTile(){
    // Define the hexadecimal data as a C++ array of uint8_t
    // data for tile 1 => Image is of 0.
    uint8_t dataArray[] = {
        0x00, 0x00, 0x3c, 0x3c,
        0x66, 0x66, 0x66, 0x66,
        0x66, 0x66, 0x66, 0x66,
        0x3c, 0x3c, 0x00, 0x00
    };
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Gameboy Graphics Map");

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Render the graphics map
        for(uint8_t idx = 0x00; idx<0x0F; idx+=0x02){
            for(uint8_t bit = 0x00; bit<0x08; bit++){
                bool bit1 = dataArray[idx] & (1<<bit);
                bool bit2 = dataArray[idx+1] & (1<<bit);

                uint8_t temp = (bit2<<0x01) | (bit1<0x00);

                // Calculate the position of the tile on the screen
                int posY = (idx/2) * 8;
                int posX = (bit%8) * 8;
                // Draw the tile using a rectangle shape
                sf::RectangleShape tile(sf::Vector2f(8, 8));
                tile.setPosition(posX, posY);
                tile.setFillColor(colors[temp]); // Set the color based on the tile index
                window.draw(tile);
            }
        }
        // Display the window
        window.display();
    }
    

}