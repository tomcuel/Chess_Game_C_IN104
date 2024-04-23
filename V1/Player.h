#ifndef __PLAYER_H__
#define __PLAYER_H__


#include <stdbool.h>
#include "Constants.h"



typedef struct Players{
    int player1_color; // WHITE or BLACK
    char* player1_name; // name of the player 1
    
    int player2_color; // WHITE or BLACK
    char* player2_name; // name of the player 2
    int is_IA; // HUMAN or AI

} Players;


/*
function to create a player, to destroy a player, to change the name of a player, to change the color of a player, to change the type of a player
function to make the IA play

*/


#endif /* __PLAYER_H__ */