CC=gcc
LD=gcc

CCFLAGS= -g
LDFLAGS= -g

OBJS=toyvm.o

all:toyvm
everything:toyvm

%.o:	%.c
	$(CC) $(CCFLAGS) -c $<

toyvm:$(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

clean:
	rm $(OBJS) toyvm.exe toyvm
