PROG = lab01_partie1
CFLAGS = -g -fPIC -m64 -Wall
LFLAGS= -fPIC -m64 -Wall
CC = mpicc

all: $(PROG)

lab01_partie1.o:	lab01_partie1.c
		$(CC) $(CFLAGS) -c lab01_partie1.c
		
lab01_partie1:	lab01_partie1.o
	$(CC) $(LFLAGS)	lab01_partie1.o -o lab01_partie1
run:
	mpirun --hostfile ./hostfile -np 24 ./lab01_partie1

ps:
	ps -fu $$USER

clean:
	/bin/rm -f *~
	/bin/rm -f *.o

test-mpi:
	mpirun --hostfile ./hostfile -np 4 ./lab01_partie1
