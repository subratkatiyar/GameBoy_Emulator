import hexReader
import OpcodeParser

# 16 bit REGISTERS
AF = 0x00
BC = 0x00
DE = 0X00
HL = 0x00
SP = 0x00 # Stack Pointer
PC = 0x00 # Program Counter

# FLAGS REGISTERS [To Do]




##########################
def executeOperand(operand):
    if operand.name == 'a16':
        return hexReader.endianessConverter(hexReader.GAME_MODULE[PC+1] << 8 | hexReader.GAME_MODULE[PC+2])
    else:
        raise NotImplementedError

def executeJP(INS):
    global PC
    #JP n16
    if INS.bytes == 3 and len(INS.operands) == 1:
        address = executeOperand(INS.operands[0])
        print(f'Jump to address: {hex(address)}')
        PC = address

    else:
    #JP cc,n16
    #JP HL
        raise NotImplementedError()
    


def executeInstruction(INS):
    global PC
    match INS.name:
        case 'NOP':
            PC += INS.bytes
        case 'JP':
            executeJP(INS)

        case _:
            raise NotImplementedError()





def RunningCPU():
    global PC
    PC = 0x100 # PC set to 0x100

    while True: # Lets keep running
        # Get Instruction
        print()
        print(f'PC = {hex(PC)} --> {hex(hexReader.GAME_MODULE[PC]).upper()}')

        INS  = OpcodeParser.InstructionsObj[hexReader.GAME_MODULE[PC]]
        # INS.getInfo()
        executeInstruction(INS)


OpcodeParser.parse_opcodes() 
hexReader.loadGameIntoMemory()
#NintendoLOGO() Some formatting is done here.
hexReader.GetGameTitle()
hexReader.GetCartridgeType()

print(f'Title:  {hexReader.GAME_TITLE}')
print(f'Type :  {hexReader.CARTRIDGE_TYPE}')
print('###################################')

RunningCPU()