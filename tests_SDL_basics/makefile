build:
	gcc -Wall image.c `sdl2-config --libs --cflags` -lm -o image
	gcc -Wall audio.c `sdl2-config --libs --cflags` -lm -o audio
	gcc -Wall mouse+key.c `sdl2-config --libs --cflags` -lm -o mouse+key
	gcc mouse+key.c -o prog -Iinclude -lSDL2main -lSDL2

clean:
	rm -f image audio mouse+key prog