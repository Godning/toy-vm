/*
 * tcpu.h
 *
 *  Created on: Apr 2, 2015
 *      Author: hackeris
 */

/**************************************
 loadi	r0,#100
 loadi	r1,#200
 add		r2,r0,r1
 halt

 0	=	nop
 1	=	loadl
 2	=	strl
 3	=	loadw
 4	=	strw
 5	=	loadb
 6	=	strb
 7	=	add
 8	=	sub
 9	=	mul
 a	=	div
 b	=	push
 c	=	pop
 ff	=	halt

 Machine Code:
 bits 24-31:	operation code
 bits 20-23:	reg1
 bits 16-19:	reg2
 bits 12-15:	reg3
 bits 00-15:	imm


 References:
 http://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C
 ***************************************/

#ifndef TCPU_H_
#define TCPU_H_

#include "types.h"

#define NUM_REGISTERS	16

enum {
	OP_NOP = 0, OP_LOADI, OP_STRI, OP_ADD, OP_HALT = 0xff
};

enum {
	REG_R0 = 0,
	REG_R1,
	REG_R2,
	REG_R3,
	REG_R4,
	REG_R5,
	REG_R6,
	REG_R7,
	REG_R8,
	REG_R9,
	REG_R10,
	REG_R11,
	REG_R12,
	REG_R13,
	REG_R14,
	REG_R15
};

#define	REF_FLAGS 13
#define REG_SP	14
#define REG_IP	15

#define FLAGS regs[REG_FLAGS];
#define IP	regs[REG_IP]
#define SP	regs[REG_SP]

typedef struct _tinstrution {
	uint32_t opcode;
	int32_t reg_1st;
	int32_t reg_2nd;
	int32_t reg_3rd;
	int32_t imm;
} tinstrution;

typedef struct _tcpu {
	uint32_t regs[NUM_REGISTERS];
	tinstrution instruction;
	void (*dump_regs)(struct _tcpu*);
	uint32_t (*fetch_instruction)(struct _tcpu*, void*);
	uint32_t (*decode_instruction)(struct _tcpu*);
	uint32_t (*execute)(struct _tcpu*);
} tcpu;

void init_tcpu(tcpu *p_tcpu);

void dump_regs(tcpu* p_tcpu);

uint32_t fetch_instruction(tcpu *p_tcpu, void*);

#endif		/* TCPU_H_ */

