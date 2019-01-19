CC = gcc
CFLAGS = -Wall -Wextra -O3

all: clean main

debug: CFLAGS += -DDEBUG
debug: all

main: utils.o main.c
	$(CC) $(CFLAGS) utils.o main.c -o main.out

utils.o:
	$(CC) $(CFLAGS) -c utils.h utils.c

clean:
	rm ./*.o;
	rm ./*.gch;