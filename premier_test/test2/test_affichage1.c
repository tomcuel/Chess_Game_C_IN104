#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SQUARE_SIZE 50
#define SQUARE_SPEED 5

int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Jeu SDL", SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Création du renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Position du carré contrôlé par le joueur
    int squareX = (WINDOW_WIDTH - SQUARE_SIZE) / 2;
    int squareY = WINDOW_HEIGHT - SQUARE_SIZE;

    // Boucle principale
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        squareX -= SQUARE_SPEED;
                        break;
                    case SDLK_RIGHT:
                        squareX += SQUARE_SPEED;
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }
        }

        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Dessin du carré contrôlé par le joueur
        SDL_Rect square = { squareX, squareY, SQUARE_SIZE, SQUARE_SIZE };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &square);

        // Affichage du rendu
        SDL_RenderPresent(renderer);

        // Attente de 16 ms pour viser environ 60 FPS
        SDL_Delay(16);
    }

    // Libération des ressources et fermeture de SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
