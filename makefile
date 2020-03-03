CC = gcc
CFLAGS = -g -Wall -std=c99

make: memsim

memsim: memsim.o
	$(CC) $(CFLAGS) -o memsim memsim.o
	$(RM) memsim.o

memory_sim.o: memsim.c
	$(CC) $(CFLAGS) -c memsim.c

clean:
	$(RM) *.o *~ memsim

