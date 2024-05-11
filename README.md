# Game Boy Emulator 
Trying to emulate gameboy for understanding how a CPU works in general

![image](https://github.com/subratkatiyar/GameBoy_Emulator/assets/43543908/f4d92bc7-c155-47bb-a1c6-e7aa5f6d1dec)

## Progress:
1. Tile Data can now be drawn using VRAM Dump. [SampleUsed](./roms/VRAM_TEST_DATA/VRAM.dump) </br>![image](https://github.com/subratkatiyar/GameBoy_Emulator/assets/43543908/01511d30-7df6-4879-a9cc-c19dc586f7a5)
2. Where are the colors? I don't know will start working on it.
3. Implemented BackgroundMap and OAM. [CPU Logic is pending, OAM updates happening by reading OAM dumps. ] ![image](https://github.com/subratkatiyar/GameBoy_Emulator/assets/43543908/3d23b81f-e299-4c4d-a022-bc82c5927025)
![ezgif-1-82a3833921](https://github.com/subratkatiyar/GameBoy_Emulator/assets/43543908/c8e8c22f-042a-4222-9584-9fff4ec368f9)



# Memory Regions Observartions.
0x0000 - 0x3FFF = Fixed from cartridge </br>
0x4000 - 0x7FFF = Switchable from cartridge </br>
0x8000 - 0x9FFF = VIDEO RAM ?? </br>
0xA000 - 0xBFFF = 0xFF </br> 
0xC000 - 0xCFFF = Random </br>
0xD000 - 0xDFFF = Random </br>
0xE000 - 0xFDFF = Echo Ram 0xC000 to 0xDDFF </br>
0xFE00 - 0xFE9F = Random </br>
0xFEA0 - 0xFEFF = 0x00 </br>

0xFF00 - 0xFF2F = Constant. </br>
0xFF30 - 0xFF3F = Random. </br>
0xFF40 - 0xFF7F = Constant. </br>

0xFF80 - 0xFFFE = Random. </br>
0xFFFF = 0x00 </br>

## Important Links
- OPCodes: https://gbdev.io/gb-opcodes/optables/
- Made life much easier: [PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine) 
