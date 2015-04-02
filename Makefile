CC=gcc
LD=gcc

OBJS=toyvm.o

all:toyvm
everything:toyvm

%.o:	%.c
	$(CC) -c $<

toyvm:$(OBJS)
	$(LD) $(OBJS) -o $@

clean:
	rm $(OBJS) toyvm.exe toyvm
