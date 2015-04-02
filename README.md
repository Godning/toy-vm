# toy-vm

A toy virtual machine in C.

 > loadi	r0,#100
 > loadi	r1,#200
 > add		r2,r0,r1
 > halt

 > 0	=	halt
 > 1	=	loadi
 > 2	=	add
 > f	=	halt

 > bits	15-12	1
 > bits	11-0	register number
 > bits	7-0		immediate value

 > 1064
 > 11C8
 > 2201
 > f000

 References:
 
 http://en.wikibooks.org/wiki/Creating_a_Virtual_Machine/Register_VM_in_C