#include <SDL2/SDL.h>

#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Timer Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Main loop flag
    int quit = 0;

    // Event handler
    SDL_Event event;

    // Start time
    Uint32 startTime = SDL_GetTicks();

    // Main loop
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&event) != 0) {
            // User requests quit
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }
        }

        // Get current time
        Uint32 currentTime = currentTime+ SDL_GetTicks();
        printf("Current time: %d\n", currentTime);
        
        // Calculate elapsed time
        Uint32 elapsedTime = currentTime - startTime;

        // Print elapsed time every second
        if (elapsedTime >= 1000) {
            printf("Current time: %d seconds\n", currentTime / 1000);
            startTime = currentTime; // Reset start time
        }

        // Delay to regulate the frame rate
        SDL_Delay(1000);
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
