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
	p_tcpu->decode_instruction = decode_instruction;
}

uint32_t fetch_instruction(tcpu *p_tcpu, void* mem) {

	uint32_t instruction = ((uint32_t*) mem)[p_tcpu->IP>> 2];
	p_tcpu->IP+= 4;
	return instruction;
}

uint32_t decode_instruction(tcpu *p_tcpu, uint32_t instr) {

	uint32_t op_code = (instr & 0xff000000) >> 24;
	p_tcpu->instruction.opcode = op_code;
	p_tcpu->instruction.reg_1st = (instr & 0x00f00000) >> 20;
	p_tcpu->instruction.reg_2nd = (instr & 0x00f00000) >> 16;
	p_tcpu->instruction.reg_3rd = (instr & 0x00f00000) >> 12;
	p_tcpu->instruction.imm = (instr & 0xffff);
	return op_code;
}

uint32_t exec(tcpu *p_tcpu) {

	tinstrution *p_tinstr = &p_tcpu->instruction;
	switch (p_tinstr->opcode) {
	case OP_LOADI:
		printf("loadi r%d,0x%x\n", p_tinstr->reg_1st, p_tinstr->imm);
		p_tcpu->regs[p_tinstr->reg_1st] = p_tinstr->imm;
		break;
	case OP_ADD:
		printf("loadi r%d,r%d,r%d\n", p_tinstr->reg_1st, p_tinstr->reg_2nd,
				p_tinstr->reg_3rd);
		p_tcpu->regs[p_tinstr->reg_1st] = p_tcpu->regs[p_tinstr->reg_2nd]
				+ p_tcpu->regs[p_tinstr->reg_3rd];
		break;
	case OP_HALT:
		break;
	}
	return p_tinstr->opcode;
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
