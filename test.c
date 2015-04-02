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
	cpu.dump_regs(&cpu);
	assert(cpu.fetch_instruction(&cpu, prog) == prog[0]);
	assert(cpu.fetch_instruction(&cpu, prog) == prog[1]);
	assert(cpu.fetch_instruction(&cpu, prog) == prog[2]);
	assert(cpu.fetch_instruction(&cpu, prog) == prog[3]);
}

int main() {

	test_init_regs();
	return 0;
}
