/*
 * main.c
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

 bits	15-12	1
 bits	11-0	register number
 bits	7-0		immediate value

 1064
 11C8
 2201
 f000

 References:
 http://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C
 ***************************************/

#include <stdio.h>

enum {
	OP_NOP = 0, OP_LOADI, OP_STRI, OP_ADD, OP_HALT = 0xff
};

#define	NUM_REGS	8
int regs[NUM_REGS];

int prog[] = { 0x01000064, 0x011000C8, 0x03210000, 0xff000000 };

int pc = 0;

int fetch() {

	return prog[pc++];
}

int op_code = 0;

int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;

void decode(int instr) {

	op_code = (instr & 0xff000000) >> 24;
	reg1 = (instr & 0x00f00000) >> 20;
	reg2 = (instr & 0x000f0000) >> 16;
	reg3 = (instr & 0x0000f000) >> 12;
	imm = (instr & 0xffff);
}

int running = 1;

void eval() {

	switch (op_code) {
	case OP_HALT:
		printf("halt\n");
		running = 0;
		break;
	case OP_LOADI:
		printf("loadl r%d,0x%x\n", reg1, imm);
		regs[reg1] = imm;
		break;
	case OP_ADD:
		printf("add r%d,r%d,r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] + regs[reg3];
		break;
	default:
		printf("Error op code.\n");
		break;
	}
}

void showRegs() {

	int i;
	for (i = 0; i < NUM_REGS; i++) {
		printf("%08x ", regs[i]);
	}
	printf("\n");
}

void run() {

	while (running) {
		showRegs();
		int instr = fetch();
		decode(instr);
		eval();
	}
	showRegs();
}

int main() {

	run();
	return 0;
}

