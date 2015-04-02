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
 1	=	loadi
 2	=	stri
 3	=	add
 4	=	sub
 5	=	mul
 6	=	div
 f	=	halt

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
	OP_NOP = 0, OP_LOADI, OP_STRI, OP_ADD, OP_HALT = 0xf
};

#define	NUM_REGS	8
int regs[NUM_REGS];

int prog[] = { 0x1064, 0x11C8, 0x3201, 0xf000 };

int pc = 0;

int fetch() {

	return prog[pc++];
}

int instrNum = 0;

int reg1 = 0;
int reg2 = 0;
int reg3 = 0;
int imm = 0;

void decode(int instr) {

	instrNum = (instr & 0xf000) >> 12;
	reg1 = (instr & 0xf00) >> 8;
	reg2 = (instr & 0xf0) >> 4;
	reg3 = (instr & 0xf);
	imm = (instr & 0xff);
}

int running = 1;

void eval() {

	switch (instrNum) {
	case OP_HALT:
		printf("halt\n");
		running = 0;
		break;
	case OP_LOADI:
		printf("loadi r%d,0x%x\n", reg1, imm);
		regs[reg1] = imm;
		break;
	case OP_ADD:
		printf("add r%d,r%d,r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] + regs[reg3];
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

