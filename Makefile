CC=gcc
CCFLAGS=-march=native -Wall -Werror -Wextra

all: program

debug: CCFLAGS += -DDEBUG -g
debug: program

benchmark: benchmark.c utils.o pagerank.o
	$(CC) -o benchmark benchmark.c utils.o pagerank.o $(CCFLAGS)
	rm -f *.o

program: main.c utils.o pagerank.o
	$(CC) -o program main.c utils.o pagerank.o $(CCFLAGS)
	rm -f *.o

utils: utils.h
	$(CC) -c utils.c $(CCFLAGS)

pagerank: pagerank.h
	$(CC) -c pagerank.c $(CCFLAGS)

clean:
	rm -f *.o program benchmark