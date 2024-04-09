CC = gcc
CFLAGS = -Wall -Wextra -std=c99 `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2` -lm

all: game

game: /Users/thomas/Documents/Scolarité/ENSTA/Info/in104/echecs/Chess_Game_C_IN104/jeuch/main.c
	$(CC) $(CFLAGS) jeuch/main.c -o game $(LDFLAGS)

run: game
	./game

clean:
	rm -f game
