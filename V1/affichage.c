#include <SDL2/SDL.h>


int main() {
    // Initialisation de la SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow("Affichage SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // Création du rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Couleur du fond
    SDL_SetRenderDrawColor(renderer, 245, 245, 220, 255); // Beige clair

    // Effacement de l'écran avec la couleur de fond
    SDL_RenderClear(renderer);

    // Chargement de la police
    // SDL_TTF n'est pas utilisé dans cet exemple

    // Création de la surface de texte
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 800, 600, 32, 0, 0, 0, 0);

    

    // Chargement de la police et rendu du texte sur la surface
    // SDL_TTF n'est pas utilisé dans cet exemple, donc le texte est rendu directement sur la surface

    // Création de la texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Affichage de la texture
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Mise à jour de l'affichage
    SDL_RenderPresent(renderer);

    // Boucle principale
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    // Libération des ressources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

