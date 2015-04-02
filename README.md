# toy-vm

A toy virtual machine in C.

 Assembly:
 > * loadi	r0,#100
 > * loadi	r1,#200
 > * add		r2,r0,r1
 > * halt

Operation Code:
 > * 0	=	nop
 > * 1	=	loadl
 > * 2	=	strl
 > * 3	=	loadw
 > * 4	=	strw
 > * 5	=	loadb
 > * 6	=	strb
 > * 7	=	add
 > * 8	=	sub
 > * 9	=	mul
 > * a	=	div
 > * b	=	push
 > * c	=	pop
 > * ff	=	halt

Machine Code:
 > * Machine Code:
 > * bits 24-31:	operation code
 > * bits 20-23:	reg1
 > * bits 16-19:	reg2
 > * bits 12-15:	reg3
 > * bits 00-15:	imm
  

 References:
 
 http://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C