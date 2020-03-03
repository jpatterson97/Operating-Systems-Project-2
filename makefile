CC = gcc
CFLAGS = -g -Wall -std=c99

make: memsim

memsim: memsim.o
	$(CC) $(CFLAGS) -o memsim memsim.o
	$(RM) memsim.o

memory_sim.o: memory_sim.c
	$(CC) $(CFLAGS) -c memory_sim.c

clean:
	$(RM) *.o *~ memsim

