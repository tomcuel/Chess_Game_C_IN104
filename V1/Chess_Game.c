///////////////////////////////////////////////////////////////////////////////
// Chess_Game.c : main file of the chess game
//  
/**
 * initialize the window and the renderer, is_running_game (global variable to make the game run)
 * 
 * A summary of the supported functions is given below:
 * 
 * initialize_SDL - to initialize the window and the renderer
 * clear_graphics - to clear the graphics
 * main - main function of the game with the game loop
 * 
 * A bit of comments to explain the code of this V1 to will remain incomplete :
 * 
 * - the game loop should work fine here 
 * - the game isn't finished at this state 
 * - the timer_showing isn't implemented yet, a first step is made to know how it works in the tests_SDL_basics directory, but not being able to download the SDL2_ttf library, we can't show it for now
 * - but we can print it in the terminal, even if it's not the best way to show it, and to the way we would have want it to be shown
 * - the IA isn't implemented yet, we will need to do it in the future (it will change a big part of the code since it will skip a big part of the loop concerning what the code need to go through when a player is playing)
 * - the buttons on the game board will not be implemented yet, we will need to do it in the future but the one from the menus will be implemented
 * - the check_mate, the rock will not be completed at this stage, so it could bring trouble to our code, the game will not works as expected sometimes 
 * - We will not show the captured pieces and score yet, we will need to do it in the future, the same issue has been encountered as for the timer function 
 * - The same for the Move_Log 
 * - we can't ask yet the player names, we will need to do it in the future if possible
 * 
 * - Each function made will be tested separately in the Tests directory, but not all function will be there at the stage we're in right now
**/
///////////////////////////////////////////////////////////////////////////////


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
int is_running_game = 0; // setup to 0 for false before the initialization of the game
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window
/**
 * @param **window : the window to initialize that is a global variable
 * @param **renderer : the renderer to initialize that is a global variable
 * @return true (1) if the initialization is successful, false (0) otherwise
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

    // initialize the structure to have the state of the game concerning rock and check
    State_Of_Rock_and_Check* State_Of_RockandCheck = Create_State_Of_Rock_and_Check();

    // initialize the players
    Players* players = Create_Players();

    // initialize the buttons
    Button** Buttons = Create_Buttons(NUMBER_OF_BUTTONS);












    /*
    need to make the basics setup of everything that hasnn't been done yet 
    */


    // playing the game while we don't quit it :
    while (is_running_game != -1) {
        
        /*
        doing the game loop

        getting the SDL event 

        make what need to be done on the chess board depending on numerous conditions


        count the timer for each player as in double_timer 


        */

    }














    // clear the buttons
    Destroy_Buttons(NUMBER_OF_BUTTONS, Buttons);

    // clear the players
    Destroy_Players(players);

    // clear the board
    Clear_Board(board);

    // clear the log
    Destroy_Move_Log_array(Log);

    // clear the captured pieces
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, max_size_captured_pieces_array);

    // clear the state of the rock and check
    Destroy_State_Of_Rock_and_Check(State_Of_RockandCheck);

    // clear the graphics and quit the SDL
    clear_graphics(window, renderer);

    // end the code
    return EXIT_SUCCESS;
}