CC = gcc
CFLAGS = -Wall -Wextra -std=c99 `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2` -lm

all: game

game: src/main.c
	$(CC) $(CFLAGS) src/main.c -o game $(LDFLAGS)

run: game
	./game

clean:
	rm -f game
