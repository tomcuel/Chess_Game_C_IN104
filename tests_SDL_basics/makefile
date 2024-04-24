build:
	gcc -Wall image.c `sdl2-config --libs --cflags` -lm -o image
	gcc -Wall audio.c `sdl2-config --libs --cflags` -lm -o audio
	gcc -Wall mouse+key.c `sdl2-config --libs --cflags` -lm -o mouse+key
	gcc double_window.c -o double_window -Iinclude -lSDL2main -lSDL2
	gcc mouse+key.c -o mouse+key.x -Iinclude -lSDL2main -lSDL2
	gcc timer.c -o timer.x -Iinclude -lSDL2main -lSDL2

clean:
	rm -f image audio mouse+key double_window mouse+key.x timer.x