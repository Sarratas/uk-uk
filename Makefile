CC = gcc
CFLAGS = -Wall -Wextra -O3

all: main clean

debug: CFLAGS += -DDEBUG
debug: all

test: tests clean

main: utils.o moves.o display_map.o display_player.o display_utils.o main.c
	$(CC) $(CFLAGS) utils.o moves.o display_map.o display_player.o display_utils.o main.c -o main.out

tests: utils.o tests.c
	$(CC) $(CFLAGS) utils.o tests.c -o tests.out

utils.o:
	$(CC) $(CFLAGS) -c utils.h utils.c

moves.o:
	$(CC) $(CFLAGS) -c control/moves.h control/moves.c

display_utils.o:
	$(CC) $(CFLAGS) -c display/display_utils.h display/display_utils.c

display_player.o:
	$(CC) $(CFLAGS) -c display/display_player.h display/display_player.c

display_map.o:
	$(CC) $(CFLAGS) -c display/display_map.h display/display_map.c

clean:
	rm -rf ./*.o;
	rm -rf ./*.gch;
	rm -rf ./*/*.o;
	rm -rf ./*/*.gch;
