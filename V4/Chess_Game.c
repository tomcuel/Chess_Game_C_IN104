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
 * - by adding the en passant to the pawn movement possibilities, in this version th goal is to use the buttons on the menu and do the move only (not considering en passant, the check things)
 * - the goal here is that the rock is working fine (without just the check things)
 * - an effort has been made here to use the log, the state of the rock, the captured pieces (we have checked yet if it works correctly, but it should work in theory, so we will test that in the future)
 * - this part will focus on the implementation of the differents menus during the game and what it implies to the game
 * - the IA is working, but for now, it's really a simple one that just makes a random move, we will need to improve it in the future, but the framework is here
 * - The Move_Log is not shown since it's really a difficult thing to do, because it implies to write a lot of letters, It could be possible to do it in the future (with many screen shots of the caracters we want to print and then do a parsing to print them), but it's not the priority for now
 * - we can't ask yet the player names, we will need to do it in the future if possible
 * 
 * - What is missing : 
 * - an intelligent AI (the different levels have to be implemented, others than the random)(maybe buttons will be to be updated if we want to have more levels of IA)
 * - the pawn promotion (and its visual to choose things, will not be difficult we think, but it will take time)
 * - he check (we think really difficult) and it's implentation in the code, it relies also on making the undo work, since a move that makes the king chekcs must be deleted and the board reinstated as it was before the move to ensure that no check occurs after the move
 * - otherwise if there is not valid moves, the checkmates might be the answer
 * - For now, everything is set up to make the game work, but it's not finished yet, things have not really been tested before being put here because it's just a draft 
 * - It will not be the case for the next versions, we will need to test everything before putting it in the main file
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
#include "Graphics.h"
#include "Audio.h"


// initialize the window and the renderer
#define max_size_log_array 1000
int is_running_game = -1; // setup to -1 for false before the initialization of the game
int last_frame_time = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


///////////////////////////////////////////////////////////////////////////////
// Define a font for rendering digits
///////////////////////////////////////////////////////////////////////////////
const int font[10][FONT_WIDTH] = {
    {0x00, 0x7E, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7E}, // 0
    {0x00, 0x00, 0x42, 0x82, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00}, // 1
    {0x00, 0x42, 0x87, 0x89, 0x91, 0xA1, 0xC1, 0x42, 0x00, 0x00}, // 2
    {0x42, 0x81, 0x81, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 3
    {0x18, 0x28, 0x48, 0x88, 0xFF, 0xFF, 0x08, 0x08, 0x08, 0x00}, // 4
    {0xF2, 0x91, 0x91, 0x91, 0x91, 0x91, 0x89, 0x86, 0x00, 0x00}, // 5
    {0x7E, 0x91, 0x91, 0x91, 0x91, 0x91, 0x91, 0x0E, 0x00, 0x00}, // 6
    {0x80, 0x80, 0x81, 0x82, 0x84, 0x88, 0x90, 0xE0, 0x00, 0x00}, // 7
    {0x76, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x76, 0x00, 0x00}, // 8
    {0x72, 0x89, 0x91, 0x91, 0x91, 0x91, 0x89, 0x7E, 0x00, 0x00}  // 9
};


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
        return -1;
    }
    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN // SDL_WINDOW_FULLSCREEN can be used to make the window fullscreen, 0 to be in the window opened
    );
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // if everything is ok, we return true
    return GAMEPLAY_CHOICE;
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
// Function to know if a point (x,y) is in a rectangle  
/**
 * @param x : the x coordinate of the point
 * @param y : the y coordinate of the point
 * @param rect : the rectangle to check
 * @return bool : true if the point is in the rectangle, false otherwise
**/
///////////////////////////////////////////////////////////////////////////////
bool is_point_in_rect(int x, int y, SDL_Rect rect) {
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}


///////////////////////////////////////////////////////////////////////////////
// Main function of the game
///////////////////////////////////////////////////////////////////////////////
int main (){

    // initialize the window and the renderer, is_running_game is a global variable that is 0 if the initialization is successful, -1 otherwise
    is_running_game = initialize_SDL();

    // intialize the board
    Piece*** board = Init_Board();
    
    // initialize the move log array
    Move_Log_array* Log = Create_Move_Log_array(max_size_log_array);

    // initialize the captured pieces array
    int max_size_captured_pieces_array = NUMBER_OF_PIECES/2;
    Captured_Piece_and_Score* Captured_Pieces_and_Score = Create_Captured_Piece_and_Score(max_size_captured_pieces_array);

    // initialize the structure to have the state of the game concerning rock and check
    State_Of_Rock_and_Check* State_Of_RockandCheck = Create_State_Of_Rock_and_Check();

    // initialize the structure concerning the last play, but only for pawn that moved two squares (for the en passant)
    Tiles_Pawn* Pawn_Move_State = Create_Tiles_Pawn();

    // initialize the players
    Players* players = Create_Players();

    // initialize the buttons
    Button** Buttons = Create_Buttons(NUMBER_OF_BUTTONS);

    bool has_match_started = false; // boolean to make the timer start; -1 for false, 1 for true

    // making the timer for each player, the time mode will be asked after so this constant here will have no effect later 
    int timer_game_mode=5;
    // making the time of the blitz mode, it will be asked after so this constant here will have no effect later
    // it define how many time a player win by making a move
    int time_of_blitz_mode=0;

    // time remaining for each player
    int seconds_remaining_player_2 = timer_game_mode;
    int last_second_player_2 = 0;

    int seconds_remaining_player_1 = timer_game_mode;
    int last_second_player_1 = 0;

    // player 0 begin to play 
    // both player 1 and player 2 have 5 seconds to play on the screen, after that it close the window and gave us the player that lose, made it
    int loosing_player=-1;

    // parameters to get the IA level
    int level_IA = NONE;

    // making int variable to know if the first clicked is done and the second clicked is done
    int is_clicked_1 = 0;
    int is_clicked_2 = 0;
    bool is_clicked_on_board = false; // to track if a click (and only one) has been done on the board or not
    // later there will be more, but here we don't care about the other clicks for buttons, etc, …

    // parameters to know if a pawn promotion is happening, and to make the promotion has desired by the player
    bool is_pawn_promotion_happening = false;
    int color_promoted_pawn = NO_COLOR;
    int type_promoted_pawn = NOTHING; // always to nothing, but we will change it directly in the log without modfiying it here

    // preparing a move implementation
    Move* move = Create_Move(0, 0, 0, 0);

    // SDL_rect to draw the red boundary when we move a piece to know it's the piece that is selected
    SDL_Rect draw_red_boundary_move={0, 0, 0, 0};

    SDL_Event event;
    // playing the game while we don't quit it :
    while (is_running_game != -1) {
        
        // gestion of the events
        while (SDL_PollEvent(&event)) {
            // condition to quit the game
            if (event.type == SDL_QUIT) {
                is_running_game = -1;
            } 
            // what happens when a key is pressed (the escape key to quit the game)
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        is_running_game = -1;
                        break;
                }
            }

            // taking the mouse event, here it's the mouse button down, so we've pressed the mouse button
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                
                // when we choose the game mode
                // the part (color_choice or difficulty_choice) will be skipped otherwise
                if (is_running_game == GAMEPLAY_CHOICE){

                    // if the button to seleect a 1v1 game is clicked
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[PLAYER_VS_PLAYER_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h;
                            Buttons[PLAYER_VS_PLAYER_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, HUMAN, HUMAN);
                            level_IA = NONE;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if the button to seleect a 1vAI game is clicked
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[PLAYER_VS_AI_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[PLAYER_VS_AI_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[PLAYER_VS_AI_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[PLAYER_VS_AI_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[PLAYER_VS_AI_BUTTON]->rect.h;
                            Buttons[PLAYER_VS_AI_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, IA, IA);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the next button, but it can only be a second click
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_GAME_CHOICE]->rect)){

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            if (players->is_player1_an_IA == IA && players->is_player2_an_IA == IA){
                                is_running_game = COLOR_CHOICE;
                            }
                            else {
                                is_running_game = TIME_CHOICE;
                            }
                            Reset_Buttons_State(Buttons);
                        }
                    }
                    
                    // if we click on the quit menu 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_GAME_CHOICE]->rect) && Buttons[PLAYER_VS_PLAYER_BUTTON]->state == UNACTIVE && Buttons[PLAYER_VS_AI_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                    is_clicked_1 = 0;
                    is_clicked_2 = 0;
                    Reset_Buttons_State(Buttons);
                }

                }

                // when we choose the color we want to have against the IA
                else if (is_running_game == COLOR_CHOICE){
                    
                    // if we click on the black button
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[BLACK_COLOR_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BLACK_COLOR_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[BLACK_COLOR_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[BLACK_COLOR_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[BLACK_COLOR_BUTTON]->rect.h;
                            Buttons[BLACK_COLOR_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, IA, HUMAN);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the white button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[WHITE_COLOR_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[WHITE_COLOR_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[WHITE_COLOR_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[WHITE_COLOR_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[WHITE_COLOR_BUTTON]->rect.h;
                            Buttons[WHITE_COLOR_BUTTON]->state = ACTIVE;
                            Setup_Players(players, WHITE, BLACK, HUMAN, IA);
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }
               
                    // if we click on the quit button, we go out of the game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }
                
                    // if we click on the main menu button, we go back to the first menu
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }

                    }

                    // if we click on the back button, we go back to the IA_type choice
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_COLOR_CHOICE]->rect) && Buttons[BLACK_COLOR_BUTTON]->state == UNACTIVE && Buttons[WHITE_COLOR_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the next button, we go to the difficulty choice menu, but it's only a second click 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_COLOR_CHOICE]->rect)){
                    
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = DIFFICULTY_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }

                }

                // when we choose the difficulty of the AI, but only if we're playing against the AI
                else if (is_running_game == DIFFICULTY_CHOICE){

                    // for the easy difficulty button
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[EASY_DIFFICULTY_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[EASY_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[EASY_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[EASY_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[EASY_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[EASY_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = EASY;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the moderate difficulty button
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MODERATE_DIFFICULTY_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[MODERATE_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[MODERATE_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = MEDIUM;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the hard difficulty button
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[HARD_DIFFICULTY_BUTTON]->rect)){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[HARD_DIFFICULTY_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[HARD_DIFFICULTY_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[HARD_DIFFICULTY_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[HARD_DIFFICULTY_BUTTON]->rect.h;
                            Buttons[HARD_DIFFICULTY_BUTTON]->state = ACTIVE;
                            level_IA = HARD;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the quit button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_IA_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }

                    // for the menu button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_IA_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }
                    }

                    // for the back button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_IA_CHOICE]->rect) && Buttons[EASY_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[MODERATE_DIFFICULTY_BUTTON]->state == UNACTIVE && Buttons[HARD_DIFFICULTY_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = COLOR_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // for the next button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEXT_BUTTON_IA_CHOICE]->rect)){
                        
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go to the time choice menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = TIME_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }
                    
                }

                // then we choose the time mode of the game
                else if (is_running_game == TIME_CHOICE){
                    
                    // if we clicked on the short blitz button 
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[SHORT_BLITZ_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[SHORT_BLITZ_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[SHORT_BLITZ_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[SHORT_BLITZ_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[SHORT_BLITZ_BUTTON]->rect.h;
                            Buttons[SHORT_BLITZ_BUTTON]->state = ACTIVE;
                            timer_game_mode = 3*60;
                            time_of_blitz_mode = 5;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }
                    }

                    // if we click on the long blitz button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LONG_BLITZ_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[LONG_BLITZ_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[LONG_BLITZ_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[LONG_BLITZ_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[LONG_BLITZ_BUTTON]->rect.h;
                            Buttons[LONG_BLITZ_BUTTON]->state = ACTIVE;
                            timer_game_mode = 5*60;
                            time_of_blitz_mode = 3;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the short time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[SHORT_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[SHORT_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[SHORT_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[SHORT_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[SHORT_BUTTON]->rect.h;
                            Buttons[SHORT_BUTTON]->state = ACTIVE;
                            timer_game_mode = 10*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);   
                        }

                    }

                    // if we click on the medium time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MODERATE_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MODERATE_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[MODERATE_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[MODERATE_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[MODERATE_BUTTON]->rect.h;
                            Buttons[MODERATE_BUTTON]->state = ACTIVE;
                            timer_game_mode = 30*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the long time mode game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LONG_BUTTON]->rect)){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[LONG_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[LONG_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[LONG_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[LONG_BUTTON]->rect.h;
                            Buttons[LONG_BUTTON]->state = ACTIVE;
                            timer_game_mode = 60*60;
                            time_of_blitz_mode = 0;
                        }

                        // if another click is done, we cancel the selection
                        else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                            is_clicked_1 = 0;
                            Reset_Buttons_State(Buttons);   
                        }

                        // if two clicks have been done, we cancel the selection
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the quit button, we go out of the game 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }

                    }
                
                    // if we click on the main menu button, we go back to the first menu
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the first menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            level_IA = NONE;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }

                    }

                    // if we click on the back button, we go back to the IA_type choice
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BACK_BUTTON_TIME_CHOICE]->rect) && Buttons[SHORT_BLITZ_BUTTON]->state == UNACTIVE && Buttons[LONG_BLITZ_BUTTON]->state == UNACTIVE && Buttons[SHORT_BUTTON]->state == UNACTIVE && Buttons[MODERATE_BUTTON]->state == UNACTIVE && Buttons[LONG_BUTTON]->state == UNACTIVE){
                    
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.x;
                            draw_red_boundary_move.y = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.y;
                            draw_red_boundary_move.w = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.w;
                            draw_red_boundary_move.h = Buttons[BACK_BUTTON_TIME_CHOICE]->rect.h;
                            Buttons[BACK_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we go back to the IA_type choice
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            if (players->is_player1_an_IA == IA || players->is_player2_an_IA == IA){
                                is_running_game = DIFFICULTY_CHOICE;
                            }
                            else if (players->is_player1_an_IA == HUMAN && players->is_player2_an_IA == HUMAN){
                                is_running_game = GAMEPLAY_CHOICE;
                            }
                            has_match_started = false;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // if we click on the load button, we go to the game, but it's only a second click 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[LOAD_BUTTON]->rect)){
                    
                        // a second click 
                        if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            is_clicked_2 = 1;
                        }

                        // if the two clicks have be done, we load the game by changing the type of part we're in, we go to CHESSBOARD_RENDER
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_running_game = CHESSBOARD_RENDER;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                        }

                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        Reset_Buttons_State(Buttons);
                    }

                }

                // when we're in the game, pressing the mouse button do things differently than in the menu
                else if (is_running_game == CHESSBOARD_RENDER){
                    
                    // if we don't have to take care of the pawn promotion
                    // making the translation of the mouse click to the row and the column of the board
                    int row = (event.button.y-WINDOW_TOP_MARGIN) / SQUARE_SIZE;
                    int col = (event.button.x-WINDOW_LEFT_MARGIN) / SQUARE_SIZE;
                    
                    bool is_player_playing_human = true;
                    if (players->is_playing == Player1 && players->is_player1_an_IA == IA){
                        is_player_playing_human = false;
                    }
                    else if (players->is_playing == Player2 && players->is_player2_an_IA == IA){
                        is_player_playing_human = false;
                    }

                    // it need to be in the board
                    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && has_match_started == true && is_player_playing_human == true && is_pawn_promotion_happening == false){

                        // if no piece has been selected
                        // it marked the first piece as selected if it's a piece of the player that is playing (looking at its color), and if it's not a nothing piece, so it's a piece that can be moved
                        // then it's the first coordinate of the move
                        if (is_clicked_1==0 && board[row][col]->type != NOTHING && board[row][col]->color == players->color_player_that_is_playing) {
                            // update the click, of the source piece here
                            is_clicked_1 = 1;
                            // start the move
                            move->previous_row = row;
                            move->previous_col = col;

                            // draw the red boundary here since it's the first click and the destination is not yet selected
                            draw_red_boundary_move.x = col * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
                            draw_red_boundary_move.y = row * SQUARE_SIZE+WINDOW_TOP_MARGIN;
                            draw_red_boundary_move.w = SQUARE_SIZE;
                            draw_red_boundary_move.h = SQUARE_SIZE;
                            is_clicked_on_board = true;
                        }

                        // if a piece has been selected, but not its destination yet, we searched for its heading
                        // the destination is the second coordinate of the move, it need not to be one of the player's piece
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            // update the position of the destination with the position of the mouse
                            move->destination_row = row;
                            move->destination_col = col;

                            // the second click has been made
                            is_clicked_2 = 1;

                        }

                        if (is_clicked_1 == 1 && is_clicked_2 == 1) {
                            // reseting the selected piece
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            is_clicked_on_board = false;

                            // getting if a rock was done
                            int is_rock_possible_type = Is_Rock_Possible(move, State_Of_RockandCheck, board);
                            // getting if an en passant was done
                            bool is_en_passant_done = Is_En_Passant_Possible(move, board, Pawn_Move_State);
                            int en_passant_type = NO_EN_PASSANT;
                            // if we have an en passant, we need to get the corresponding int
                            if (is_en_passant_done == true){
                                en_passant_type = EN_PASSANT;
                            }

                            // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
                            int piece_taken_type = NOTHING;
                            int piece_taken_color = NO_COLOR;
                            // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
                            bool will_capture_a_piece = Will_Capture(move, board);
                            if (will_capture_a_piece == true && Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){
                                piece_taken_type = board[move->destination_row][move->destination_col]->type;
                                piece_taken_color = board[move->destination_row][move->destination_col]->color;
                            }
                            // udpating the datas concerning the en passant move, so the log can be able to undo it, because techincally, the piece is not taken, it's just removed from the board
                            if (is_en_passant_done == true){
                                if (board[move->previous_row][move->previous_col]->color == WHITE){
                                    piece_taken_type = PAWN;
                                    piece_taken_color = BLACK;
                                }
                                else if (board[move->previous_row][move->previous_col]->color == BLACK){
                                    piece_taken_type = PAWN;
                                    piece_taken_color = WHITE;
                                }
                            }

                            // concerning the pawn promotion
                            is_pawn_promotion_happening = Is_Pawn_Promotion_Possible(move, board);
                            color_promoted_pawn = NO_COLOR;
                            type_promoted_pawn = NOTHING;
                            if (is_pawn_promotion_happening == true){
                                color_promoted_pawn = board[move->previous_row][move->previous_col]->color;
                            }


                            // getting the check state
                            bool is_check_before_move = Is_Check(players->color_player_that_is_playing, board); 

                            // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
                            // making the move if it's valid, here we don't care about the special moves and what it does to other pieces
                            // we will need to do it in the future, here we also don't care about the check
                            if (Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){

                                // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                                // but only a valid move will be added to the log
                                Move_Log_Element* element = Create_Element_Move_Log();
                                Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, is_check_before_move, piece_taken_type, piece_taken_color, is_rock_possible_type, en_passant_type, color_promoted_pawn, type_promoted_pawn);
                                Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element);
                                if (message != LOG_LIST_SUCCESS){
                                    printf("Error: the log is full\n");
                                    is_running_game = -1;
                                }

                                Destroy_Move_Log_Element(element);
                                
                                // if we're in a blitz mode, the time of the player that is playing is increased by the time of the blitz mode after each move he makes
                                if (players->is_playing == Player1){
                                    seconds_remaining_player_1 = seconds_remaining_player_1 + time_of_blitz_mode;
                                }
                                else if (players->is_playing == Player2){
                                    seconds_remaining_player_2 = seconds_remaining_player_2 + time_of_blitz_mode;
                                }

                                // trying to make the rock effective by getting the real moves linked to the rock that has been made
                                if (is_rock_possible_type != NO_ROCK){
                                    Move* king_move_during_rock=Create_King_Move_during_Rock(move, board, State_Of_RockandCheck);
                                    Move* rook_move_during_rock=Create_Rook_Move_during_Rock(move, board, State_Of_RockandCheck);
                                    // we need to make the two moves, the king and the rock, and put the places there were to zero 
                                    // but also udpating the parameters others than the log, to keep track of the state of the game
                                    Make_Rock_Move(board, move, king_move_during_rock, rook_move_during_rock, players);
                                    Change_Others_Structures_during_Rock(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);

                                    // free the memory
                                    Destroy_Move(king_move_during_rock);
                                    Destroy_Move(rook_move_during_rock);

                                    // since it's a rock, we can reset the tile pawn structure for the next turn
                                    Reset_Tiles_Pawn(Pawn_Move_State);

                                    // play the sound of the rock
                                    play_sound("rock.wav");
                                }
                                // en passant move
                                else if (is_en_passant_done == true){

                                    // we need to clear the piece that has been eaten by the en passant on the board, before making the move, because we need the initial position of the pawn to know where to clear the piece
                                    Clear_En_Passant_Piece(move, board, Pawn_Move_State);
                                    
                                    // making the move and updating the parameters others than the log, to keep track of the state of the game
                                    Make_Move(board, move, players);
                                    Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                                    
                                    // en passant mean that we can reset the tile pawn structure for the next turn
                                    Reset_Tiles_Pawn(Pawn_Move_State);

                                    // play the sound of the en passant (take)
                                    play_sound("take.wav");
                                }
                                // classic move
                                else {
                                    // we need to file the tile pawn structure for the next turn, before making the move, because we need the initial position of the pawn to know if it can move two squares
                                    Fill_Tile_Pawn(move, board, Pawn_Move_State);

                                    // making the move and updating the parameters others than the log, to keep track of the state of the game
                                    Make_Move(board, move, players);
                                    Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);

                                    if (will_capture_a_piece == false){
                                        // play the sound of the take
                                        play_sound("chess.wav");
                                    }
                                    else if (will_capture_a_piece == true) {
                                        // play the sound of the move
                                        play_sound("take.wav");
                                    }
                                }   
                                // changing the player that is playing is included in the Make_Move function

                                int color_we_are_checking = NO_COLOR;
                                if (players->color_player_that_is_playing == WHITE){
                                    color_we_are_checking = BLACK;
                                }
                                else if (players->color_player_that_is_playing == BLACK){
                                    color_we_are_checking = WHITE;
                                }
                                // get the check state of the player that was playing the last move
                                bool check_state = Is_Check(color_we_are_checking, board);
                                // if the king of the color is in check after making a move, we need to remove the move
                                if (check_state == true){
                                    Undo_Last_Move(board, Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, Pawn_Move_State);
                                    // play the sound of the invalid move link to a check
                                    play_sound("check.wav");
                                }
                            }

                        }

                    }

                    else if (is_pawn_promotion_happening == true){
                        
                        // if we cliked on the queen button, then we need to udpate the type of the pawn that has been promoted in the log and on the board
                        // we also need to tell that the pawn promotion is not happening anymore
                        
                        // if we select the queen button
                        if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUEEN_BUTTON]->rect)){
                            
                            // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                            if (is_clicked_1 == 0){
                                is_clicked_1 = 1;
                                is_clicked_2 = 0;
                                draw_red_boundary_move.x = Buttons[QUEEN_BUTTON]->rect.x;
                                draw_red_boundary_move.y = Buttons[QUEEN_BUTTON]->rect.y;
                                draw_red_boundary_move.w = Buttons[QUEEN_BUTTON]->rect.w;
                                draw_red_boundary_move.h = Buttons[QUEEN_BUTTON]->rect.h;
                            }

                            // if another click is done, we cancel the selection
                            else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                                is_clicked_2 = 1;
                            }

                            // if two clicks have been done, we cancel the selection
                            if (is_clicked_1 == 1 && is_clicked_2 == 1){
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                Log->Move_Log[Log->actual_size-1]->type_of_pawn_promoted = QUEEN;
                                board[Log->Move_Log[Log->actual_size-1]->move->destination_row][Log->Move_Log[Log->actual_size-1]->move->destination_col]->type = QUEEN;
                                is_pawn_promotion_happening = false;
                            }
                        }

                        // if we select the rook button 
                        else if (is_point_in_rect(event.button.x, event.button.y, Buttons[ROOK_BUTTON]->rect)){
                            
                            // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                            if (is_clicked_1 == 0){
                                is_clicked_1 = 1;
                                is_clicked_2 = 0;
                                draw_red_boundary_move.x = Buttons[ROOK_BUTTON]->rect.x;
                                draw_red_boundary_move.y = Buttons[ROOK_BUTTON]->rect.y;
                                draw_red_boundary_move.w = Buttons[ROOK_BUTTON]->rect.w;
                                draw_red_boundary_move.h = Buttons[ROOK_BUTTON]->rect.h;
                            }

                            // if another click is done, we cancel the selection
                            else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                                is_clicked_2 = 1;
                            }

                            // if two clicks have been done, we cancel the selection
                            if (is_clicked_1 == 1 && is_clicked_2 == 1){
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                Log->Move_Log[Log->actual_size-1]->type_of_pawn_promoted = ROOK;
                                board[Log->Move_Log[Log->actual_size-1]->move->destination_row][Log->Move_Log[Log->actual_size-1]->move->destination_col]->type = ROOK;
                                is_pawn_promotion_happening = false;
                            }
                        }

                        // if we select the bishop button
                        else if (is_point_in_rect(event.button.x, event.button.y, Buttons[BISHOP_BUTTON]->rect)){
                            
                            // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                            if (is_clicked_1 == 0){
                                is_clicked_1 = 1;
                                is_clicked_2 = 0;
                                draw_red_boundary_move.x = Buttons[BISHOP_BUTTON]->rect.x;
                                draw_red_boundary_move.y = Buttons[BISHOP_BUTTON]->rect.y;
                                draw_red_boundary_move.w = Buttons[BISHOP_BUTTON]->rect.w;
                                draw_red_boundary_move.h = Buttons[BISHOP_BUTTON]->rect.h;
                            }

                            // if another click is done, we cancel the selection
                            else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                                is_clicked_2 = 1;
                            }

                            // if two clicks have been done, we cancel the selection
                            if (is_clicked_1 == 1 && is_clicked_2 == 1){
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                Log->Move_Log[Log->actual_size-1]->type_of_pawn_promoted = BISHOP;
                                board[Log->Move_Log[Log->actual_size-1]->move->destination_row][Log->Move_Log[Log->actual_size-1]->move->destination_col]->type = BISHOP;
                                is_pawn_promotion_happening = false;
                            }
                        }

                        // if we select the knight button
                        else if (is_point_in_rect(event.button.x, event.button.y, Buttons[KNIGHT_BUTTON]->rect)){
                            
                            // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                            if (is_clicked_1 == 0){
                                is_clicked_1 = 1;
                                is_clicked_2 = 0;
                                draw_red_boundary_move.x = Buttons[KNIGHT_BUTTON]->rect.x;
                                draw_red_boundary_move.y = Buttons[KNIGHT_BUTTON]->rect.y;
                                draw_red_boundary_move.w = Buttons[KNIGHT_BUTTON]->rect.w;
                                draw_red_boundary_move.h = Buttons[KNIGHT_BUTTON]->rect.h;
                            }

                            // if another click is done, we cancel the selection
                            else if (is_clicked_1 ==1 && is_clicked_2 == 0){
                                is_clicked_2 = 1;
                            }

                            // if two clicks have been done, we cancel the selection
                            if (is_clicked_1 == 1 && is_clicked_2 == 1){
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                Log->Move_Log[Log->actual_size-1]->type_of_pawn_promoted = KNIGHT;
                                board[Log->Move_Log[Log->actual_size-1]->move->destination_row][Log->Move_Log[Log->actual_size-1]->move->destination_col]->type = KNIGHT;
                                is_pawn_promotion_happening = false;
                            }
                        }

                        // we still need to be able to quit the game, but no others things on the differents buttons can be done
                        else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_IN_GAME]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                            
                            // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                            if (is_clicked_1 == 0){
                                is_clicked_1 = 1;
                                is_clicked_2 = 0;
                                draw_red_boundary_move.x = Buttons[QUIT_BUTTON_IN_GAME]->rect.x;
                                draw_red_boundary_move.y = Buttons[QUIT_BUTTON_IN_GAME]->rect.y;
                                draw_red_boundary_move.w = Buttons[QUIT_BUTTON_IN_GAME]->rect.w;
                                draw_red_boundary_move.h = Buttons[QUIT_BUTTON_IN_GAME]->rect.h;
                            }

                            // a second click 
                            else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                                if (is_clicked_on_board == false){
                                    is_clicked_2 = 1;
                                }
                                else {
                                    is_clicked_1 = 0;
                                    is_clicked_2 = 0;
                                    is_clicked_on_board = false;
                                }
                            }

                            // if the two clicks have be done, we quit the game
                            if (is_clicked_1 == 1 && is_clicked_2 == 1){
                                is_running_game = -1;
                            }
                        }

                        // when we don't click on anything, we reset the clicks
                        else {
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                        }


                    }
                        
                    // otherwise it can be on some buttons that are on the right side of the window
                    // for the start button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[START_BUTTON]->rect)){
                        
                        Buttons[START_BUTTON]->state = ACTIVE;
                        has_match_started = true;

                        // play the sound of the start of the game
                        play_sound("chessstart.wav");
                    
                    }

                    // for the restart button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[RESTART_BUTTON_IN_GAME]->rect)&& Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[RESTART_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[RESTART_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[RESTART_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[RESTART_BUTTON_IN_GAME]->rect.h;
                            Buttons[RESTART_BUTTON_IN_GAME]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we reset the game to its original parameters
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = CHESSBOARD_RENDER;
                            has_match_started = false;
                            // reset the players, the board, the log, the captured pieces, the state of the rock and the check, the timer
                            
                            players->is_playing = Player1;
                            loosing_player = -1;
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                            seconds_remaining_player_1 = timer_game_mode;
                            seconds_remaining_player_2 = timer_game_mode;

                            // reset the board
                            Reset_Board(board);

                            // reset the log (putting the size to 0 is enough)
                            Log->actual_size = 0;

                            // reset the captured pieces
                            Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

                            // reset the state of the rock and the check
                            Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);

                            // reset the tiles pawn structures
                            Reset_Tiles_Pawn(Pawn_Move_State);

                            // reset the players, but since the parameters are the same, we don't need to reset everything from the beginning concerning the player type, the color, the name, etc
                            players->is_playing = Player1;
                            players->color_player_that_is_playing = WHITE;
                        }
                    }

                    // for the new_game button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEW_GAME_BUTTON_IN_GAME]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[NEW_GAME_BUTTON_IN_GAME]->rect.h;
                            Buttons[NEW_GAME_BUTTON_IN_GAME]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we go back to the first load menu
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = GAMEPLAY_CHOICE;
                            has_match_started = false;
                            Reset_Buttons_State(Buttons);
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            players->is_playing = Player1;
                            players->color_player_that_is_playing = WHITE;
                            loosing_player = -1;
                        }
                    }

                    // for the quit button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_IN_GAME]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[UNDO_BUTTON]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[QUIT_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = Buttons[QUIT_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = Buttons[QUIT_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = Buttons[QUIT_BUTTON_IN_GAME]->rect.h;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we quit the game
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_running_game = -1;
                        }
                    }

                    // for the undo button 
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[UNDO_BUTTON]->rect) && Buttons[RESTART_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[NEW_GAME_BUTTON_IN_GAME]->state == UNACTIVE && Buttons[QUIT_BUTTON_IN_GAME]->state == UNACTIVE){
                        
                        // the first click is making the button be circle by a red rectangle to make the user know it has been selected
                        if (is_clicked_1 == 0){
                            is_clicked_1 = 1;
                            is_clicked_2 = 0;
                            draw_red_boundary_move.x = Buttons[UNDO_BUTTON]->rect.x;
                            draw_red_boundary_move.y = Buttons[UNDO_BUTTON]->rect.y;
                            draw_red_boundary_move.w = Buttons[UNDO_BUTTON]->rect.w;
                            draw_red_boundary_move.h = Buttons[UNDO_BUTTON]->rect.h;
                            Buttons[UNDO_BUTTON]->state = ACTIVE;
                        }

                        // a second click 
                        else if (is_clicked_1 == 1 && is_clicked_2 == 0){
                            if (is_clicked_on_board == false){
                                is_clicked_2 = 1;
                            }
                            else {
                                is_clicked_1 = 0;
                                is_clicked_2 = 0;
                                is_clicked_on_board = false;
                            }
                        }

                        // if the two clicks have be done, we undo the last move
                        if (is_clicked_1 == 1 && is_clicked_2 == 1){
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                            
                            // Undo the last move
                            Undo_Last_Move(board, Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, Pawn_Move_State);
                            // if we're playing against the IA we need to supress the two last moves
                            if (players->is_player1_an_IA == IA || players->is_player2_an_IA == IA){
                                Undo_Last_Move(board, Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, Pawn_Move_State);
                            }
                            // printf("is(%d,%d) on its starting position : %d\n", Log->Move_Log[Log->actual_size-1]->move->previous_row, Log->Move_Log[Log->actual_size-1]->move->previous_col, board[Log->Move_Log[Log->actual_size-1]->move->previous_row][Log->Move_Log[Log->actual_size-1]->move->previous_col]->is_on_his_start_position);

                        }
                    }

                    // when we don't click on anything, we reset the buttons state
                    else {
                            is_clicked_1 = 0;
                            is_clicked_2 = 0;
                            Reset_Buttons_State(Buttons);
                        }

                }

                // if we're in the victory menu
                else if (is_running_game == VICTORY_MENU){
                    // if we're in the victory menu, we need to check if a button has been clicked to quit the game or to go play again

                    // if we click on the new game button, we go back to the first load menu
                    if (is_point_in_rect(event.button.x, event.button.y, Buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = GAMEPLAY_CHOICE;
                        has_match_started = false;
                        Buttons[START_BUTTON]->state = UNACTIVE;
                    }

                    // if we click on the restart button, we restart the game back to with the same parameters
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[RESTART_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = CHESSBOARD_RENDER;
                        has_match_started = false;
                        Buttons[START_BUTTON]->state = UNACTIVE;
                        // reset the players, the board, the log, the captured pieces, the state of the rock and the check, the timer
                        
                        players->is_playing = Player1;
                        loosing_player = -1;
                        is_clicked_1 = 0;
                        is_clicked_2 = 0;
                        seconds_remaining_player_1 = timer_game_mode;
                        seconds_remaining_player_2 = timer_game_mode;

                        // reset the board
                        Reset_Board(board);

                        // reset the log (putting the size to 0 is enough)
                        Log->actual_size = 0;

                        // reset the captured pieces
                        Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

                        // reset the state of the rock and the check
                        Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);

                        // reset the tiles pawn structures
                        Reset_Tiles_Pawn(Pawn_Move_State);

                        // reset the players, but since the parameters are the same, we don't need to reset everything from the beginning concerning the player type, the color, the name, etc
                        players->is_playing = Player1;
                        players->color_player_that_is_playing = WHITE;

                    }

                    // if we click on the quit button, we quit the game
                    else if (is_point_in_rect(event.button.x, event.button.y, Buttons[QUIT_BUTTON_VICTORY_MENU]->rect)){
                        is_running_game = -1;
                    }

                }

            }
        }

        // to know if it's to the IA to play
        bool is_player_playing_IA = false;
        if (players->is_playing == Player1 && players->is_player1_an_IA == IA){
            is_player_playing_IA = true;
        }
        else if (players->is_playing == Player2 && players->is_player2_an_IA == IA){
            is_player_playing_IA = true;
        }
        // if it's the IA turn to play, we make it play
        if (is_player_playing_IA == true && has_match_started == true && is_pawn_promotion_happening == false){
            int IA_color = players->color_player_that_is_playing;
            // the move changed is here supposed to be possible; otherwise the game will stop working
            IA_Play(move, board, level_IA, IA_color, State_Of_RockandCheck, Pawn_Move_State);
            // printf("IA_color : %d\n", IA_color);

            // getting if a rock was done
            int is_rock_possible_type_IA = Is_Rock_Possible(move, State_Of_RockandCheck, board);
            // getting if an en passant was done
            bool is_en_passant_done_IA = Is_En_Passant_Possible(move, board, Pawn_Move_State);
            int en_passant_type_IA = NO_EN_PASSANT;
            // if we have an en passant, we need to get the corresponding int
            if (is_en_passant_done_IA == true){
                en_passant_type_IA = EN_PASSANT;
            }

            // if a piece is taken, we need to know what type and what color it is, in case we want to undo it later, we can track the piece that has been taken to reinstall it on the board
            int piece_taken_type_IA = NOTHING;
            int piece_taken_color_IA = NO_COLOR;
            // if a move is valid, then we can also ask if a piece is taken, and if it's the case, we can know what type and what color it is
            bool will_capture_a_piece = Will_Capture(move, board);
            if (will_capture_a_piece == true && Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true){
                piece_taken_type_IA = board[move->destination_row][move->destination_col]->type;
                piece_taken_color_IA = board[move->destination_row][move->destination_col]->color;
            }
            if (is_en_passant_done_IA == true){
                if (board[move->previous_row][move->previous_col]->color == WHITE){
                    piece_taken_type_IA = PAWN;
                    piece_taken_color_IA = BLACK;
                }
                else if (board[move->previous_row][move->previous_col]->color == BLACK){
                    piece_taken_type_IA = PAWN;
                    piece_taken_color_IA = WHITE;
                }
            }

            // concerning the pawn promotion fro the IA
            bool is_IA_pawn_promotion_happening = Is_Pawn_Promotion_Possible(move, board);
            int color_IA_promoted_paxwn = NO_COLOR;
            int type_IA_promoted_pawn = NOTHING;
            if (is_pawn_promotion_happening == true){
                color_IA_promoted_paxwn = board[move->previous_row][move->previous_col]->color;
            }

            // if you touch the piece once, as in the real game, you're forced to play this piece, there isn't any way to cancel the move
            // making the move if it's valid, here we don't care about the special moves and what it does to other pieces
            // we will need to do it in the future, here we also don't care about the check
            if (Is_Move_Valid(move, board, State_Of_RockandCheck, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){

                // making the move log update that is crucial for Make_Move to work since we go searching for an index actual_size-1 and only adding an element to Move_Log will make actual_size-1 positive, not to have a segmentation fault
                // but only a valid move will be added to the log
                Move_Log_Element* element = Create_Element_Move_Log();
                Change_Move_Log_Element(element, move->previous_row, move->previous_col, move->destination_row, move->destination_col, NO_CHECK, piece_taken_type_IA, piece_taken_color_IA, is_rock_possible_type_IA, en_passant_type_IA, color_IA_promoted_paxwn, type_IA_promoted_pawn);
                Move_Log_array_MESSAGE_TYPE message = Add_Element_to_the_end_of_Move_Log_array(Log, element);
                if (message != LOG_LIST_SUCCESS){
                    printf("Error: the log is full\n");
                    is_running_game = -1;
                }

                Destroy_Move_Log_Element(element);
                    
                // if we're in a blitz mode, the time of the player that is playing is increased by the time of the blitz mode after each move he makes
                if (players->is_playing == Player1){
                    seconds_remaining_player_1 = seconds_remaining_player_1 + time_of_blitz_mode;
                }
                else if (players->is_playing == Player2){
                    seconds_remaining_player_2 = seconds_remaining_player_2 + time_of_blitz_mode;
                }

                // trying to make the rock effective by getting the real moves linked to the rock that has been made
                if (is_rock_possible_type_IA != NO_ROCK){
                    Move* king_move_during_rock=Create_King_Move_during_Rock(move, board, State_Of_RockandCheck);
                    Move* rook_move_during_rock=Create_Rook_Move_during_Rock(move, board, State_Of_RockandCheck);
                    // we need to make the two moves, the king and the rock, and put the places there were to zero 
                    // but also udpating the parameters others than the log, to keep track of the state of the game
                    Make_Rock_Move(board, move, king_move_during_rock, rook_move_during_rock, players);
                    Change_Others_Structures_during_Rock(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);

                    // free the memory
                    Destroy_Move(king_move_during_rock);
                    Destroy_Move(rook_move_during_rock);

                    // since it's a rock, we can reset the tile pawn structure for the next turn
                    Reset_Tiles_Pawn(Pawn_Move_State);
                }
                // en passant move
                else if (is_en_passant_done_IA == true){

                    // we need to clear the piece that has been eaten by the en passant on the board, before making the move, because we need the initial position of the pawn to know where to clear the piece
                    Clear_En_Passant_Piece(move, board, Pawn_Move_State);
                    
                    // making the move and updating the parameters others than the log, to keep track of the state of the game
                    Make_Move(board, move, players);
                    Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                    
                    // en passant mean that we can reset the tile pawn structure for the next turn
                    Reset_Tiles_Pawn(Pawn_Move_State);
                }
                // classic move
                else {
                    // we need to file the tile pawn structure for the next turn, before making the move, because we need the initial position of the pawn to know if it can move two squares
                    Fill_Tile_Pawn(move, board, Pawn_Move_State);

                    // making the move and updating the parameters others than the log, to keep track of the state of the game
                    Make_Move(board, move, players);
                    Change_Others_Structures(Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, board);
                }
                // changing the player that is playing is included in the Make_Move function
            }

            // now we need to do the pawn promotion for the IA
            if (is_IA_pawn_promotion_happening == true){
                Make_Pawn_Promotion_for_IA(move, board, Log, level_IA);
            }

            // if after the move made by the IA, it's in check, we need to undo the move and make another one
            int color_we_are_checking_IA = NO_COLOR;
            if (players->color_player_that_is_playing == WHITE){
                color_we_are_checking_IA = BLACK;
            }
            else if (players->color_player_that_is_playing == BLACK){
                color_we_are_checking_IA = WHITE;
            }
            // get the check state of the player that was playing the last move
            bool check_state = Is_Check(color_we_are_checking_IA, board);
            // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
            if (check_state == true){
                Undo_Last_Move(board, Log, Captured_Pieces_and_Score, State_Of_RockandCheck, players, Pawn_Move_State);
            }

        }
    

        // the timer is also present when we're in the game 
        // the game need to be running
        if (is_running_game == CHESSBOARD_RENDER && has_match_started == true){

            // Countdown for each player at the end of the event that happened
            // for player 2
            if (players->is_playing == Player2 && players->is_player2_an_IA == HUMAN) {
                if (seconds_remaining_player_2 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_2--;
                        last_frame_time = current_time;
                        if (last_second_player_2 != seconds_remaining_player_2) {
                            // printf("Current time remaining for player 2 : %d seconds\n", seconds_remaining_player_2);
                            last_second_player_2 = seconds_remaining_player_2;
                        }
                    }
                } 
                else {
                    loosing_player=Player2;
                }
            }
            
            // for player 1
            else if (players->is_playing == Player1 && players->is_player1_an_IA == HUMAN) {
                if (seconds_remaining_player_1 > 0) {
                    int current_time = SDL_GetTicks();
                    int elapsed_time = current_time - last_frame_time;
                    if (elapsed_time >= 1000) {
                        seconds_remaining_player_1--;
                        last_frame_time = current_time;
                        if (last_second_player_1 != seconds_remaining_player_1) {
                            // printf("Current time remaining for player 1 : %d seconds\n", seconds_remaining_player_1);
                            last_second_player_1 = seconds_remaining_player_1;
                        }
                    }
                } 
                else {
                    loosing_player=Player1;
                }
            }
        
        }


        // the render is not the same if we're in the game or in the menu
        if (is_running_game == GAMEPLAY_CHOICE || is_running_game == COLOR_CHOICE || is_running_game == DIFFICULTY_CHOICE || is_running_game == TIME_CHOICE ){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the load menu
            Show_Load_Menu(renderer, is_running_game, Buttons, is_clicked_1, is_clicked_2, draw_red_boundary_move);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            // in the menu, we reset the game parameters
            players->is_playing = Player1;
            loosing_player = -1;
            seconds_remaining_player_1 = timer_game_mode;
            seconds_remaining_player_2 = timer_game_mode;

            // reset the board
            Reset_Board(board);

            // reset the log (putting the size to 0 is enough)
            Log->actual_size = 0;

            // reset the captured pieces
            Reset_Captured_Piece_and_Score(Captured_Pieces_and_Score);

            // reset the state of the rock and the check
            Reset_State_Of_Rock_and_Check(State_Of_RockandCheck);
        }

        // if we're in the game, we show the chess board
        if (is_running_game == CHESSBOARD_RENDER){
            // reset the renderer, the screen of the graphic card to a grey color that is no too dark but not too light
            SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            SDL_RenderClear(renderer);

            // show the buttons in the game
            Show_Menu_Button_in_Game(renderer, Buttons, is_pawn_promotion_happening, color_promoted_pawn);

            // show the captured pieces
            Show_Captured_Pieces(renderer, Captured_Pieces_and_Score);

            // Draw the score of the game (drawing it next to the piece captured, on the winning side)
            int number = Captured_Pieces_and_Score->score;
            int x;
            int y;
            if (Captured_Pieces_and_Score->player_that_is_winning == WHITE){
                y=WINDOW_HEIGHT-WINDOW_TOP_MARGIN+20;
                x=WINDOW_LEFT_MARGIN + (2*SQUARE_SIZE/10-10)*Captured_Pieces_and_Score->number_of_black_pieces_captured+30;
            }
            else if (Captured_Pieces_and_Score->player_that_is_winning == BLACK){
                y=20;
                x=WINDOW_LEFT_MARGIN + (2*SQUARE_SIZE/10-10)*Captured_Pieces_and_Score->number_of_white_pieces_captured+30;
            }
            
            while (number > 0) {
                int digit = number % 10;
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
                for (int i = 0; i < FONT_HEIGHT; i++) {
                    for (int j = 0; j < FONT_WIDTH; j++) {
                        if (font[digit][j] & (1 << (FONT_WIDTH - i - 1))) {
                            SDL_RenderDrawPoint(renderer, x + j, y + i);
                        }
                    }
                }
                x -= FONT_WIDTH/3; // Move right for the next digit
                number /= 10;
            }

            // show the timer
            Show_Updated_Timer(renderer, seconds_remaining_player_1, seconds_remaining_player_2, players->is_playing);

            // for the log we show it only if there is no pawn promotion happening
            if (is_pawn_promotion_happening == false){
                // show the log
                Show_Log(renderer, Log); /* still to be implemented at this point */
            }

            // show the chess board
            Show_Chess_Board(renderer, board, is_clicked_1, is_clicked_2, draw_red_boundary_move);

            // show the trajectory of the piece that is selected
            // printf("is_clicked_on_board : %d\n", is_clicked_on_board);
            Show_Trajectory(renderer, board, move, State_Of_RockandCheck, Pawn_Move_State, is_clicked_1, is_clicked_2, is_clicked_on_board);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            /*
            // we now need to look at the check state of the game
            int check_mate_state = Is_Check_Mate(players->color_player_that_is_playing, board, State_Of_RockandCheck, Log);

            // the check mate function doesn't return the good values yet for the check mate state
            
            // if a draw is happening the player that is playing now loose, so the opposite of the player we're checking
            if (check_mate_state == DRAW){
                if (players->color_player_that_is_playing == WHITE){
                    loosing_player = Player2;
                }
                else if (players->color_player_that_is_playing == BLACK){
                    loosing_player = Player1;
                }
            }
            else if (check_mate_state == WHITE_CHECKMATE || check_mate_state == BLACK_CHECKMATE){
                loosing_player = players->is_playing;
            }
            */
           // we also need to play the endgame song when one of the previous options will be true

            // if a player has lost, we need to stop the game and go to the end of the game
            if (loosing_player != -1){
                is_running_game = is_running_game + 1;
            }

        }

        // if we're in the win menu screen 
        if (is_running_game == VICTORY_MENU){
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show the victory menu
            Show_Victory_Menu(renderer, Buttons, loosing_player, players);

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);
        }
        
    }

    // free the move
    Destroy_Move(move);

    // clear the buttons
    Destroy_Buttons(NUMBER_OF_BUTTONS, Buttons);

    // clear the players
    Destroy_Players(players);

    // clear the board
    Clear_Board(board);

    // clear the log
    Destroy_Move_Log_array(Log);

    // clear the tiles pawn structures
    Destroy_Tiles_Pawn(Pawn_Move_State);

    // clear the captured pieces
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score, max_size_captured_pieces_array);

    // clear the state of the rock and check
    Destroy_State_Of_Rock_and_Check(State_Of_RockandCheck);

    // clear the graphics and quit the SDL
    clear_graphics(window, renderer);

    // end the code
    return EXIT_SUCCESS;
}