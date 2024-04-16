import json

class Flags:
    Z:chr
    N:chr
    H:chr
    C:chr

    def __init__(self, dictionary):
        if len(dictionary) > 4:
            print(dictionary)
            exit()
        self.Z = dictionary['Z']
        self.N = dictionary['N']
        self.H = dictionary['H']
        self.C = dictionary['C']

class Operand:
    name:str
    immediate:bool
    bytes:int | None


    def __init__(self, dictionary):
        self.name = dictionary['name']
        self.bytes = dictionary.get('bytes')
        self.immediate = dictionary['immediate']

class Instruction:
    opcode:int
    name:str
    bytes:int
    cycles: list[int]
    operands:list[Operand]
    immediate: bool
    flags:Flags

    def __init__(self, dictionary, instruction, operands, flags):
        self.opcode = instruction
        self.name = dictionary['mnemonic']
        self.bytes = dictionary['bytes']
        self.cycles = dictionary['cycles']
        self.operands = operands
        self.immediate = dictionary['immediate']
        self.flags = flags

#Global Variable    

InstructionsObj = {}

def parse_opcodes():
    f = open('Opcode.json')
    data = json.load(f)
    for instrucion in data['unprefixed']:
        OperandsObj: list[Operand] = []
        FlagsObj = Flags(data['unprefixed'][instrucion]['flags'])
        for operand in data['unprefixed'][instrucion]['operands']:
            OperandObj = Operand(operand)
            OperandsObj.append(OperandObj)
        InstructionObj = Instruction(data['unprefixed'][instrucion], int(instrucion,16), OperandsObj, FlagsObj)
        InstructionsObj[int(instrucion,16)] = InstructionObj
    
    # for instrucion in data['prefixed']:
    #     OperandsObj: list[Operand] = []
    #     FlagsObj = Flags(data['prefixed'][instrucion]['flags'])
    #     for operand in data['prefixed'][instrucion]['operands']:
    #         OperandObj = Operand(operand)
    #         OperandsObj.append(OperandObj)
    #     InstructionObj = Instruction(data['prefixed'][instrucion], instrucion, OperandsObj, FlagsObj)
    #     InstructionsObj.append(InstructionObj)
parse_opcodes()
