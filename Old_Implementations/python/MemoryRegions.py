import logging
logger = logging.getLogger(__name__)
logging.basicConfig(level=logging.INFO)
import hexReader

class MemoryRegions:
    # Complete copy of memory
    ECHO_MEMORY = {}
    # The Game Boy has a 16-bit address bus, which is used to address ROM, RAM, and I/O.
    ROM_BANK_00 = {} # 0000 - 3FFF
    ROM_BANK_01 = {} # 4000 - 7FFF
    VIDEO_RAM = {} # 8000 - 9FFF
    EXTERNAL_RAM = {} # A000 - BFFF
    WORK_RAM_BANK_0 = {} # C000 - CFFF
    WORK_RAM_BANK_1 = {} # D000 - DFFF 
    ECHO_RAM = {} #E000 - FDFF  
    OAM = {} # FE00 - FE9F
    NOT_USABLE = {} # FEA0 - FEFF
    IO_REGISTERS = {} # FF00 - FF7F
    HIGH_RAM = {} # FF80 - FFFE
    INTERRUPT_ENABLE_REGISTER = {} # FFFF - FFFF

    def __init__(self):
        hexReader.loadGameIntoMemory()
        addrLen = len(hexReader.GAME_MODULE)
        if addrLen != 0x8000:
            raise Exception("Rom Size exceeds 0x8000")
        
        logger.info('Writing to ROM [Only Possible Here]')
        for address in range(0, addrLen):
            self.ECHO_MEMORY[address] = hexReader.GAME_MODULE[address]
            if address >= 0x000 and address <= 0X3FFF:
                self.ROM_BANK_00[address] = hexReader.GAME_MODULE[address]
            elif address >= 0x4000 and address <= 0x7FFF:
                self.ROM_BANK_01[address] = hexReader.GAME_MODULE[address]

    def Write_To_Memory(self, address, data, byteSize):
        if byteSize == 1:
           self.WRITE(address, data)
        elif byteSize == 2:
             self.WRITE(address+0x01, data >> 8)
             self.WRITE(address, data & 0xFF)
        else:
            raise Exception('Write To Memory more than 2 bytes.')

    def WRITE(self, address, data):
        if address >= 0x000 and address <= 0X3FFF:
            logger.warn(f'ROM_BANK_0 [WRITE IGNORED] {hex(address)} = {hex(data)}')
        elif address >= 0x4000 and address <= 0x7FFF:
            logger.warn(f'ROM_BANK_1 [WRITE IGNORED] {hex(address)} = {hex(data)}')
        elif address >= 0x8000 and address <= 0x9FFF:
            logger.info(f'VIDEO_RAM --> {hex(address)} = {hex(data)}')
            self.VIDEO_RAM[address] = data
            self.ECHO_MEMORY[address] = data
        
        elif address >= 0xA000 and address <= 0xBFFF:
            logger.info(f'EXTERNAL_RAM --> {hex(address)} = {hex(data)}')
            self.EXTERNAL_RAM[address] = data
            self.ECHO_MEMORY[address] = data
        
        elif address >= 0xC000 and address <= 0xCFFF:
            logger.info(f'WORK_RAM_BANK_0 --> {hex(address)} = {hex(data)}')
            self.WORK_RAM_BANK_0[address] = data
            self.ECHO_MEMORY[address] = data

        elif address >= 0xD000 and address <= 0xDFFF:
            logger.info(f'WORK_RAM_BANK_1 --> {hex(address)} = {hex(data)}')
            self.WORK_RAM_BANK_1[address] = data
            self.ECHO_MEMORY[address] = data

        else:
            raise NotImplementedError('Write to memory')
    
    def Get_Memory_Big_Endian_Format(self, address, bitsLen):
        if bitsLen == 16:
            return hexReader.endianessConverter(self.ECHO_MEMORY[address] << 8 | self.ECHO_MEMORY[address+0x01])
        elif bitsLen == 8:
            return self.ECHO_MEMORY[address]
    
