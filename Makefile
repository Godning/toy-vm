CC=gcc
LD=gcc

OBJS=toyvm.o

everything:toyvm

.c.o:
	$(CC) -c $<

toyvm:$(OBJS)
	$(LD) $(OBJS) -o $@

clean:
	rm $(OBJS) toyvm.exe toyvm
