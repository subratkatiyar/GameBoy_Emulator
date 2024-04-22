import logging
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)

import hexReader
import OpcodeParser
import MemoryRegions

# 16 bit REGISTERS
REGISTERS = {
    'A': 0x01,
    'F': 0xB0,
    'B': 0x00,
    'C': 0x13,
    'D': 0x00,
    'E': 0xD8,
    'H': 0x01,
    'L': 0x4D,
    'SP': 0xFFFE,
    'PC': 0x00
}

FLAGS = {
    'Z' : 7,
    'N' : 6,
    'H' : 5,
    'C' : 4

}

# STACK = {}

# def getAddressOrData(pos, byteSize):
#     if byteSize == 16:
#         return hexReader.endianessConverter(hexReader.GAME_MODULE[pos] << 8 | hexReader.GAME_MODULE[pos+1])
#     elif byteSize == 8:
#         return hexReader.GAME_MODULE[pos]



    
def getOperation():
    global INS
    r8  = ['A', 'B', 'C', 'D', 'E', 'H', 'L']
    r16 = ['AF', 'BC', 'DE', 'HL', 'SP', 'PC']
    n8  = ['n8']
    n16 = ['n16']
    a16 = ['a16']

    operation = ''
    for operand in INS.operands:
        if operand.name in r8:
            operation+='r8'
        elif operand.name in r16:
            operation+='r16'
        elif operand.name in n8:
            operation+='n8'
        elif operand.name in n16:
            operation+='n16'
        elif operand.name in a16:
            operation+='a16'
        else:
            raise NotImplementedError('getOperation()')
    print(operation)
    return operation

def executeNoOperation():
    global REGISTERS, INS
    logger.info(f'NOP')
    REGISTERS['PC'] += INS.bytes

def executeJump():
    global REGISTERS, INS
    operation = getOperation()
    if operation == 'a16':
        addressLoc = REGISTERS['PC']+0x01
        address = Memory.Get_Memory_Big_Endian_Format(addressLoc, 16)
        logger.info(f'JUMP  {hex(address)}')
        REGISTERS['PC'] = address
    else:
        raise NotImplementedError('executeJump()')

def executeLoad():
    global REGISTERS, INS
    operation = getOperation()

    if operation == 'r16n16':
        dataLoc = REGISTERS['PC']+0x01
        data = Memory.Get_Memory_Big_Endian_Format(dataLoc, 16)
        register = INS.operands[0].name
        if REGISTERS.get(register):
            logger.info(f'LOAD {register} {hex(data)}')
            REGISTERS[register] = data
            REGISTERS['PC']+=INS.bytes
        elif len(register) == 0x02:
            logger.info(f'LOAD {register} {hex(data)}')
            REGISTERS[register[0]] = data >> 8
            REGISTERS[register[1]] = data & 0xFF
            REGISTERS['PC']+=INS.bytes
    
    elif operation == 'r8n8':
        dataLoc = REGISTERS['PC']+0x01
        data = Memory.Get_Memory_Big_Endian_Format(dataLoc, 8)
        register = INS.operands[0].name
        logger.info(f'LOAD {register} {hex(data)}')
        REGISTERS[register] = data
        REGISTERS['PC']+=INS.bytes

    elif operation == 'a16r8':
        addressLoc = REGISTERS['PC']+0x01
        address = Memory.Get_Memory_Big_Endian_Format(addressLoc, 16)
        data = REGISTERS['A']
        logger.info(f'LOAD {address} {hex(data)}')
        Memory.Write_To_Memory(address, data, 0x01)
        REGISTERS['PC']+=INS.bytes

    elif operation == 'r8r8':
        logger.info(f'LOAD A B')
        REGISTERS['A'] = REGISTERS['B']
        REGISTERS['PC']+=INS.bytes

    # elif operation == 'r8r16':
    #     register_1 = INS.operands[0].name
    #     register_2 = INS.operands[1].name

    #     MemoryLoc = REGISTERS[register_2[1]]<<8 + REGISTERS[register_2[1]]

    #     value = Memory.Get_Memory_Big_Endian_Format(MemoryLoc, 16)
    #     print(hex(value))
    #     exit()

    else:
        raise NotImplementedError('executeLoad()')

def executeCall():
    global REGISTERS, INS
    operation = getOperation()
    if operation == 'a16':
        addressLoc = REGISTERS['PC']+0x01
        address = Memory.Get_Memory_Big_Endian_Format(addressLoc, 16)
        logger.info(f'CALL {hex(address)}')
        Memory.Write_To_Memory(REGISTERS['SP']-0x02, REGISTERS['PC']+INS.bytes, 0x02)
        REGISTERS['SP'] -= 0x02
        REGISTERS['PC'] = address
    else:
        raise NotImplementedError('executeCall()')

def executeReturn():

    if len(INS.operands) == 0:
        logger.info('RET')
        REGISTERS['PC'] = Memory.Get_Memory_Big_Endian_Format(REGISTERS['SP'], 16)
        REGISTERS['SP'] += 0x02
    
    elif len(INS.operands) == 1:
        logger.info(f'RET {INS.operands[0].name}')
        register_1 = INS.operands[0].name[-1]
        if REGISTERS['F'] & (1<<FLAGS[register_1]) == 1<<FLAGS[register_1]:
            REGISTERS['PC'] = Memory.Get_Memory_Big_Endian_Format(REGISTERS['SP'], 16)
            REGISTERS['SP'] += 0x02
        else:
            REGISTERS['PC'] += INS.bytes

def executeOr():
    register_1 = INS.operands[0].name
    register_2 = INS.operands[1].name

    REGISTERS[register_1] = REGISTERS[register_1] | REGISTERS[register_2]  
    logger.info(f'OR {register_1} {register_2} ')

    if REGISTERS[register_1] == 0x00:    
        REGISTERS['F'] =  REGISTERS['F'] | (1<<7)  # Set Z if result = 0 
    else:
        REGISTERS['F'] =  REGISTERS['F'] & ~(1<<7)  # UnSet Z if result = 0 
    
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<6) # N
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<5) # H
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<4) # C

    REGISTERS['PC']+=INS.bytes

def executeXor():
    register_1 = INS.operands[0].name
    register_2 = INS.operands[1].name

    REGISTERS[register_1] = REGISTERS[register_1] ^ REGISTERS[register_2]  
    logger.info(f'XOR {register_1} {register_2} ')

    if REGISTERS[register_1] == 0x00:    
        REGISTERS['F'] =  REGISTERS['F'] | (1<<7)  # Set Z if result = 0 
    else:
        REGISTERS['F'] =  REGISTERS['F'] & ~(1<<7)  # UnSet Z if result = 0 
    
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<6) # N
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<5) # H
    REGISTERS['F'] =  REGISTERS['F'] & ~(1<<4) # C

    REGISTERS['PC']+=INS.bytes



def executeInstruction():
    global REGISTERS, INS
    match INS.name:
        case 'NOP':
            executeNoOperation()
        case 'JP':
            executeJump()
        case 'LD':
            executeLoad()
        case 'CALL':
            executeCall()
        case 'RET':
            executeReturn()
        case 'OR':
            executeOr()
        case 'XOR':
            executeXor()
        case _:
            raise NotImplementedError()





def RunningCPU():
    global REGISTERS, INS
    REGISTERS['PC'] = 0x100 # PC set to 0x100

    while True: # Lets keep running
        # Get Instruction
        print()
        print(f'PC = {hex(REGISTERS["PC"])} --> {hex(hexReader.GAME_MODULE[REGISTERS["PC"]]).upper()}')
        INS  = OpcodeParser.InstructionsObj[hexReader.GAME_MODULE[REGISTERS['PC']]]
        executeInstruction()
        
        for register in REGISTERS.keys():
            print(f"{register} = {format(REGISTERS[register], '#04x')}", end = ', ')
        
        print()
        # if STACK.get(REGISTERS['SP']) == None:
        #     print(f'Stack --> None')
        # else:
        #     print(f"Stack --> {format(STACK.get(REGISTERS['SP']),'#04x')}")


OpcodeParser.parse_opcodes() 
Memory = MemoryRegions.MemoryRegions()   
hexReader.GetGameTitle()
hexReader.GetCartridgeType()

print(f'Title:  {hexReader.GAME_TITLE}')
print(f'Type :  {hexReader.CARTRIDGE_TYPE}')
print('###################################')

RunningCPU()