# Game Boy Emulator 
Trying to emulate gameboy for understanding how a CPU works in general

![image](https://github.com/subratkatiyar/GameBoy_Emulator/assets/43543908/f4d92bc7-c155-47bb-a1c6-e7aa5f6d1dec)

## Instructions Set

| UnPrefixed | x0                 | x1 | x2                 | x3                 | x4                 | x5                 | x6 | x7 | x8 | x9 | xA | xB                 | xC                 | xD                 | xE | xF                 |
| ---------- | ------------------ | -- | ------------------ | ------------------ | ------------------ | ------------------ | -- | -- | -- | -- | -- | ------------------ | ------------------ | ------------------ | -- | ------------------ |
| 0x         | :white_check_mark: |    |                    |                    | :white_check_mark: | :white_check_mark: |    |    |    |    |    | :white_check_mark: | :white_check_mark: |
| 1x         | :white_check_mark: |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |
| 2x         | :white_check_mark: |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |
| 3x         |                    |    | :white_check_mark: |                    |                    |                    |    |    |    |    |    |                    |                    | :white_check_mark: |
| 4x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| 5x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| 6x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| 7x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| 8x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| 9x         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| Ax         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    | :white_check_mark: |
| Bx         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| Cx         |                    |    |                    | :white_check_mark: |                    |                    |    |    |    |    |    |                    |                    |                    |    |
| Dx         |                    |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |                    |
| Ex         | :white_check_mark: |    |                    |                    |                    |                    |    |    |    |    |    |                    |                    |                    |    |
| Fx         |                    |    |                    | :white_check_mark: |                    |                    |    |    |    |    |    |                    |                    |                    |    |

| Prefixed ($CB $xx) | x0 | x1 | x2 | x3 | x4 | x5 | x6 | x7 | x8 | x9 | xA | xB | xC | xD | xE | xF |
| ------------------ | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- | -- |
| 0x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 1x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 2x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 3x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 4x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 5x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 6x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 7x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 8x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| 9x                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Ax                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Bx                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Cx                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Dx                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Ex                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |
| Fx                 |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |    |


## Important Links
- OPCodes: https://gbdev.io/gb-opcodes/optables/
