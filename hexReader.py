GAME_MODULE = []
NINTENDO_LOGO = ''
GAME_TITLE = ''
CARTRIDGE_TYPE = ''


def endianessConverter(value):
    # print(type(value))
    return ((value & 0xFF00) >> 8) | ((value & 0xFF) << 8)

def firstByte(value):
    return value >> 8

def secondByte(value):
    return value & 0xFF

def loadGameIntoMemory(): # Benefit of having lot of memory. 
    tempData = ''
    with open('./roms/snake.gb', 'rb') as file:
        # Read binary data from the file
        file.read
        tempData = file.read(1) # We read bytes at a time, helpful for coverting little/big endianess
        while(tempData):
            data = int(tempData.hex(),16)
            GAME_MODULE.append(data)
            tempData = file.read(1)

def getChunk(left, right): 
    response = ''
    for idx in range(left, right+1):
        response += chr(GAME_MODULE[idx])
    return response 

def NintendoLOGO(): # 0x104 - 0x133
    logo = getChunk(0x104, 0x133)
    print(f'LOGO: {logo}')

def GetGameTitle(): # 0x134 - 0x143
    global GAME_TITLE
    GAME_TITLE = getChunk(0x134, 0x143)

def GetCartridgeType(): # More types to be added later
    global CARTRIDGE_TYPE
    tempByte = GAME_MODULE[0x147]
    if tempByte == 0x00:
        CARTRIDGE_TYPE = 'ROM ONLY'
    else:
        CARTRIDGE_TYPE = 'UNKNOWN'


