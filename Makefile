CC=gcc
LD=gcc

CCFLAGS= -g
LDFLAGS= -g

OBJS=tcpu.o

all:toyvm
everything:toyvm

%.o:	%.c
	$(CC) $(CCFLAGS) -c $<

toyvm:$(OBJS) toyvm.o 
	$(LD) $(LDFLAGS) toyvm.o $(OBJS) -o $@

clean:
	rm $(OBJS) toyvm.exe toyvm vmtest.exe vmtest test.o toyvm.o

vmtest: test.o $(OBJS)
	$(LD) $(LDFLAGS) test.o $(OBJS) -o $@

test:vmtest
	./vmtest
