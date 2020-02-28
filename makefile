CC = gcc
CFLAGS = -g -Wall -std=c99

make: memsim

memsim: memory_sim.o
	$(CC) $(CFLAGS) -o memsim memory_sim.o
	$(RM) memory_sim.o

memory_sim.o: memory_sim.c memory_sim.h
	$(CC) $(CFLAGS) -c memory_sim.c

clean:
	$(RM) *.o *~ memsim

