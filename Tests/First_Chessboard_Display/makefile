CC = gcc
CFLAGS = -Wall -Wfatal-errors
LDFLAGS = -Iinclude -lSDL2main -lSDL2

all: main_test_1.x aff.x

main_test_1.x: Piece.o Image.o Audio.o main_test_1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

aff.x: Image.o affichage_fin.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

realclean: clean
	rm -f *.x