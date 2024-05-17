#pragma once
#include "MemoryUnit.h"

class CPU {
private:
	void executeNOP();
	void execute_JP_nn();
	void execute_XOR_A();
	void execute_HL_nn();
	void execute_LD_A_n();
	void execute_LD_nn_A();
	void execute_LDH_n_A();
	void execute_LD_HL_n();
	void execute_LDH_A_n();
	void execute_LD_B_n();
	void execute_LD_C_n();
	void execute_LD_HL_dec_A();
	void execute_DEC_B();
	void execute_DEC_C();
	void execute_JR_NZ_n();
	void execute_DI();
	void execute_CP_n();
public:
	MemoryUnit *MemoryUnitObj;
	CPU(MemoryUnit*);
	void initialize_memory();
	void initialize_registers();
	void start_execution();
	void debug_registers();

	void execute_unimplemented();

	

	

	

	

};