#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Constants.h"
#include "Piece.h"


/////////////////////////////////////////////////////////////////////////////////////
// Piece Summary 
/**
 * Players is a structure that represents the players of the game and its parameters
 * 
 * A summary of the supported functions is given below:
 * 
 * Create_Players - to create the two players
 * Get_First_Player - to get the player that will be the first to play
 * Destroy_Players - to destroy the two players
 * IA_Play - to make the IA play (a move will be returned) (will need special implementation in the code to make the move)
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the players and its parameters
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Players{
    int is_player1_an_IA; // HUMAN or AI, to get the type of the player 1
    int player1_color; // WHITE or BLACK
    char* player1_name; // name of the player 1
    
    int is_player2_an_IA; // HUMAN or AI, to get the type of the player 2
    int player2_color; // WHITE or BLACK
    char* player2_name; // name of the player 2

    is_playing; // Player1 or Player2
} Players;


////////////////////////////////////////////////////////////////////////////////////
// Function to create the two players
/**
 * @param player1_name : the name of the player 1
 * @param player2_name : the name of the player 2
 * @param player1_color : the color of the player 1
 * @param player2_color : the color of the player 2
 * @param is_IA : the type of the player 2
**/
/////////////////////////////////////////////////////////////////////////////////////
Players* Create_Players(char* player1_name, char* player2_name, int player1_color, int player2_color, int is_IA);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the player that will be the first to play (the one that has the white pieces)
/**
 * @param player : the players
 * @return the player that will play first : Player1 or Player2
**/
/////////////////////////////////////////////////////////////////////////////////////
int Get_First_Player(Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the two players
/**
 * @param player : the players to destroy
**/
/////////////////////////////////////////////////////////////////////////////////////
void Destroy_Players(Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the IA play, it returns a move the IA will play
// We then have to implement the move made and what it does as for a human player, just the move will not be defined by the player, some things will change in the code
// on how it will be organised when for the IA to play
// AI is always the player2
/**
 * @param board : the board to play on
 * @param level : the level of the IA
 * @param IA_color : the color of the IA (to know which pieces to play)
**/
/////////////////////////////////////////////////////////////////////////////////////
Move* IA_Play(Piece*** board, int level, int IA_color);


#endif /* __PLAYER_H__ */