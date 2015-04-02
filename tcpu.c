/*
 * tcpu.c
 *
 *  Created on: Apr 2, 2015
 *      Author: hackeris
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tcpu.h"

void init_tcpu(tcpu* p_tcpu) {

	memset(&p_tcpu->regs, 0, sizeof(tcpu));
	p_tcpu->dump_regs = dump_regs;
	p_tcpu->fetch_instruction = fetch_instruction;
}

uint32_t fetch_instruction(tcpu *p_tcpu, void* mem) {

	uint32_t instruction = ((uint32_t*) mem)[p_tcpu->IP>> 2];
	p_tcpu->IP+= 4;
	return instruction;
}

void dump_regs(tcpu* p_tcpu) {

	int i;
	int counter = 1;
	for (i = 0; i < NUM_REGISTERS; i++) {
		printf("r%d=0x%08x ", i, p_tcpu->regs[i]);
		if (counter % 4 == 0) {
			printf("\n");
		}
		counter++;
	}
}
