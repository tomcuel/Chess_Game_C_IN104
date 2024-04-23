#include <stdio.h> // pour le printf
#include <stdlib.h> // pour le scanf
#include <math.h> // pour les fonctions mathématiques 
#include <string.h> // pour les chaînes de caractères, strlen par exemple
#include <stdbool.h> // pour les booléens 
#include <time.h> // pour les randint 
#include <limits.h> // pour les limites
#include <ctype.h> // pour isalpha 
#include <unistd.h> // pour getpid 

#include "SDL2/SDL.h"

#include "Constants.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "Mouse.h"
#include "Timer.h"
#include "Graphics.h"





// initialize the window and the renderer
#define max_size_log_array 1000
int is_running_game = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
/**
 * @param **window : the window to initialize that is a global variable
 * @param **renderer : the renderer to initialize that is a global variable
**/
///////////////////////////////////////////////////////////////////////////////
int initialize_SDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0 // SDL_WINDOW_FULLSCREEN can be used to make the window fullscreen, if we've the timer on it thanks to tff
        // otherwise, we will need to print it in the terminal
    );
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return false;
    }

    // create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return false;
    }

    // if everything is ok, we return true
    return true;
}


///////////////////////////////////////////////////////////////////////////////
// Function to clear the graphics
/**
 * @param *window : the window to destroy
 * @param *renderer : the renderer to destroy 
**/
///////////////////////////////////////////////////////////////////////////////
void clear_graphics(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


///////////////////////////////////////////////////////////////////////////////
// Main function of the game
///////////////////////////////////////////////////////////////////////////////
int main (){

    // initialize the window and the renderer, is_running_game is a global variable that is 0 if the initialization is successful, -1 otherwise
    is_running_game= initialize_SDL();

    // intialize the board
    Piece*** board = Init_Board();

    // initialize the move log array
    Move_Log_array* Log = Create_Move_Log_array(max_size_log_array);

    // initialize the captured pieces array
    int max_size_captured_pieces_array = NUMBER_OF_PIECES;
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Create_Captured_Piece_and_Score(max_size_captured_pieces_array);





    /*
    need to make the basics setup of everything : 
    */


    // playing the game while we don't quit it :
    while (is_running_game != -1) {
        
        /*
        doing the game loop
        */

    }


    // clear the board
    Clear_Board(board);

    // clear the log
    Destroy_Move_Log_array(Log);

    // clear the captured pieces
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, max_size_captured_pieces_array);

    // clear the graphics and quit the SDL
    clear_graphics(window, renderer);

    // end the code
    return EXIT_SUCCESS;
}