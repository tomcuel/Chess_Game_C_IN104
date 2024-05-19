#ifndef __IA_H__
#define __IA_H__

#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "Move_Log.h"
#include "Piece.h"
#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns a random number between two numbers
/**
 * @param min : the minimum number
 * @param max : the maximum number
 * @return int : the random number generated
**/
/////////////////////////////////////////////////////////////////////////////////////
int Random_Int(int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function that makes the IA play depending on the level
/**
 * @param move : the move to play
 * @param board : the board
 * @param level : the level of the IA
 * @param IA_color : the color of the IA
 * @param state_of_rock_and_check : the state of rock and check
 * @param Pawn_Move_State : the state of the pawns
**/
/////////////////////////////////////////////////////////////////////////////////////
void IA_Play(Move* move, Piece*** board, int level, int IA_color, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make the pawn promotion for the IA
/**
 * @param move : the move to play
 * @param board : the board
 * @param Log : the log of the moves
 * @param IA_level : the level of the IA
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Pawn_Promotion_for_IA(Move* move, Piece*** board, Move_Log_array* Log, int level_IA);


#endif /* __IA_H__ */