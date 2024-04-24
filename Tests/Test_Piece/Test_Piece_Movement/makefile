CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all: test_piece_move_validity.x test_piece_move_graphic.x

test_piece_move_validity.x: Move.o Move_Log.o Piece.o Player.o Board.o test_piece_move_validity.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_piece_move_graphic.x: Move.o Move_Log.o Piece.o Player.o Board.o Graphic.o test_piece_move_graphic.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x