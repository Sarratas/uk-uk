CC = gcc
CFLAGS = -Wall -Wextra -O3

all: main clean

debug: CFLAGS += -DDEBUG
debug: all

main: utils.o main.c
	$(CC) $(CFLAGS) utils.o main.c -o main.out

tests: utils.o
	$(CC) $(CFLAGS) utils.o tests.c -o tests.out

utils.o:
	$(CC) $(CFLAGS) -c utils.h utils.c

clean:
	rm ./*.o;
	rm ./*.gch;