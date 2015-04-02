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

 0	=	halt
 1	=	loadi
 2	=	add
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

#define	NUM_REGS	3
int regs[NUM_REGS];

int prog[] = { 0x1064, 0x11C8, 0x2201, 0xf000 };

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
	case 0xf:
		printf("halt\n");
		running = 0;
		break;
	case 0x1:
		printf("loadi r%d,#%d\n", reg1, imm);
		regs[reg1] = imm;
		break;
	case 0x2:
		printf("add r%d,r%d,r%d\n", reg1, reg2, reg3);
		regs[reg1] = regs[reg2] + regs[reg3];
		break;
	}
}

void showRegs() {

	int i;
	for (i = 0; i < NUM_REGS; i++) {
		printf("%04x ", regs[i]);
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
