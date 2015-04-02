/*
 * main.c
 *
 *  Created on: Apr 2, 2015
 *      Author: hackeris
 */

#include <stdio.h>

#include "tcpu.h"

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

void exec() {

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
		running = 0;
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
		exec();
	}
	showRegs();
}

int main() {

	run();
	return 0;
}

