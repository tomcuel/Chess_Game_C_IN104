build:
	gcc -Wall image.c `sdl2-config --libs --cflags` -lm -o image
	gcc -Wall audio.c `sdl2-config --libs --cflags` -lm -o audio
	gcc -Wall mouse+key.c `sdl2-config --libs --cflags` -lm -o mouse+key

run:
	./game

clean:
	rm game