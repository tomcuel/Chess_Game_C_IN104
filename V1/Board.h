#ifndef __BOARD_H__
#define __BOARD_H__


#include "Constants.h"
#include "Piece.h"
#include "Move.h"
#include "Move_Log.h"
#include "Player.h"


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the board
/**
 * @param board : the board to initialize
**/
/////////////////////////////////////////////////////////////////////////////////////
Piece*** Init_Board();


/////////////////////////////////////////////////////////////////////////////////////
// Function to clear the board
/**
 * @param board : the board to clear
**/
/////////////////////////////////////////////////////////////////////////////////////
void Clear_Board(Piece*** board);


/////////////////////////////////////////////////////////////////////////////////////
// Function to make a move on the board
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to make the move
 * @param move : the move to make
 * @param log : the log to modify
 * @param captured_pieces : the captured pieces to modify
 * @param player : the players (to get the player that is playing)
**/
/////////////////////////////////////////////////////////////////////////////////////
void Make_Move(Piece*** board, Move* move, Move_Log_array* log, Captured_Piece_and_Score* captured_pieces, Players* player);


/////////////////////////////////////////////////////////////////////////////////////
// Function to undo a move on the board
// It modifies the board, the log and the captured pieces, and the players structure, to change the player that is playing
/**
 * @param board : the board to undo the move
 * @param log : the log to modify
 * @param captured_pieces : the captured pieces to modify
 * @param player : the players (to get the player that is playing)
**/
/////////////////////////////////////////////////////////////////////////////////////
void Undo_Move(Piece*** board, Move_Log_array* log, Captured_Piece_and_Score* captured_pieces, Players* player);


#endif /* __BOARD_H__ */