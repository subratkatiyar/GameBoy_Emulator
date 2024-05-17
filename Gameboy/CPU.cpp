#include "CPU.h"
#include "iostream"
#include <iomanip>
#include <cassert>

void CPU::executeNOP()
{
	std::cout << "nop\n";
	MemoryUnitObj->registers.pc++;
}

void CPU::execute_XOR_A() {
	// XOR A
	MemoryUnitObj->registers.a ^= MemoryUnitObj->registers.a;

	// Update flags
	MemoryUnitObj->set_flag(FLAG_Z, MemoryUnitObj->registers.a == 0);
	MemoryUnitObj->set_flag(FLAG_N, 0);
	MemoryUnitObj->set_flag(FLAG_H, 0);
	MemoryUnitObj->set_flag(FLAG_C, 0);

	//Update PC
	MemoryUnitObj->registers.pc++;

	std::cout << "XOR A\n";
}

void CPU::execute_HL_nn() {
	MemoryUnitObj->registers.pc++;
	uint16_t nn = MemoryUnitObj->read_memory_16_le(MemoryUnitObj->registers.pc);
	MemoryUnitObj->registers.hl = nn;
	MemoryUnitObj->registers.pc += 2;
	std::cout << "ld hl " << std::setw(4) << std::setfill('0') << std::hex << nn << "\n";

}

CPU::CPU(MemoryUnit *memoryUnitPointer)
{
	MemoryUnitObj = memoryUnitPointer;
	initialize_memory();
	initialize_registers();
	MemoryUnitObj->load_rom("..\\roms\\Tetris.gb");
}

void CPU::initialize_memory()
{
	MemoryUnitObj->load_vram("..\\roms\\VRAM.dump");
	MemoryUnitObj->reset_eram();
	MemoryUnitObj->reset_notusuable();
	MemoryUnitObj->load_ioregisters("..\\roms\\IO.dump");
	MemoryUnitObj->reset_ieregister();
}

void CPU::initialize_registers()
{
	MemoryUnitObj->registers.af = 0x01B0;  // Example: Set flags (Z=0, N=1, H=1, C=0)
	MemoryUnitObj->registers.bc = 0x0013;  // Example: Set BC register pair
	MemoryUnitObj->registers.de = 0x00D8;  // Example: Set DE register pair
	MemoryUnitObj->registers.hl = 0x014D;  // Example: Set HL register pair
	MemoryUnitObj->registers.sp = 0xFFFE;  // Example: Set Stack Pointer
	MemoryUnitObj->registers.pc = 0x0100;  // Example: Set Program Counter
}

void CPU::debug_registers() {
	std::cout << "AF = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.af << " ";
	std::cout << "BC = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.bc << " ";
	std::cout << "DE = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.de << " ";
	std::cout << "HL = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.hl << " ";
	std::cout << "SP = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.sp << " ";
	std::cout << "PC = 0x" << std::setw(4) << std::setfill('0') << std::hex << MemoryUnitObj->registers.pc << " ";
	std::cout << "INS = 0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc)) << "\n";
}

void CPU::execute_unimplemented() {
	// Print an error message
	std::cout<<"Error: Instruction not implemented\n";
	assert(0); // This will cause the program to terminate with an error message
}

void CPU::start_execution()
{
	while (true) {
		debug_registers();
		uint8_t opcode = MemoryUnitObj->read_memory(MemoryUnitObj->registers.pc);
		switch (opcode) {
			case 0x00:
				executeNOP();
				break;
			case 0x05:
				execute_DEC_B();
				break;
			case 0x06:
				execute_LD_B_n();
				break;
			case 0x0D:
				execute_DEC_C();
				break;
			case 0x0E:
				execute_LD_C_n();
				break;
			case 0x20:
				execute_JR_NZ_n();
				break;
			case 0x21:
				execute_HL_nn();
				break;
			case 0x32:
				execute_LD_HL_dec_A();
				break;
			case 0x36:
				execute_LD_HL_n();
				break;
			case 0x3E:
				execute_LD_A_n();
				break;
			case 0xAF:
				execute_XOR_A();
				break;
			case 0xC3:
				execute_JP_nn();
				break;
			case 0xE0:
				execute_LDH_n_A();
				break;
			case 0xEA:
				execute_LD_nn_A();
				break;
			case 0xF0:
				execute_LDH_A_n();
				break;
			case 0xF3:
				execute_DI();
				break;
			case 0xFE:
				execute_CP_n();
				break;
			default:
//				debug_registers();
				execute_unimplemented();
				break;
		}
	}
}
