#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <stdbool.h>
#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// Structure that represents the players
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Players{
    int player1_color; // WHITE or BLACK
    char* player1_name; // name of the player 1
    
    int is_IA; // HUMAN or AI, to get the type of the player 2
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
// AI is always player2
/**
 * @param board : the board to play on
 * @param level : the level of the IA
 * @param IA_color : the color of the IA (to know which pieces to play)
**/
/////////////////////////////////////////////////////////////////////////////////////
Move* IA_Play(Piece*** board, int level, int IA_color);


#endif /* __PLAYER_H__ */