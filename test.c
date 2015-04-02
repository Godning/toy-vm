/*
 * test.c
 *
 *  Created on: Apr 2, 2015
 *      Author: hackeris
 */

#include <stdio.h>
#include <assert.h>

#include "tcpu.h"

void test_init_regs() {

	int prog[] = { 0x01000064, 0x011000C8, 0x03210000, 0xff000000 };
	tcpu cpu;
	init_tcpu(&cpu);
	printf("registers after init:\n");
	cpu.dump_regs(&cpu);

	uint32_t instruction = cpu.fetch_instruction(&cpu, prog);
	assert(instruction == prog[0]);
	uint32_t opcode = cpu.decode_instruction(&cpu, instruction);
	cpu.execute(&cpu);
	assert(opcode == 0x01);

	instruction = cpu.fetch_instruction(&cpu, prog);
	assert(instruction == prog[1]);
	opcode = cpu.decode_instruction(&cpu, instruction);
	cpu.execute(&cpu);

	instruction = cpu.fetch_instruction(&cpu, prog);
	assert(instruction == prog[2]);
	opcode = cpu.decode_instruction(&cpu, instruction);
	cpu.execute(&cpu);

	assert(cpu.regs[2] == (0x64+0xc8));
	cpu.dump_regs(&cpu);

	printf("test of cpu\'s functions passed.\n");
}

int main() {

	test_init_regs();
	return 0;
}
