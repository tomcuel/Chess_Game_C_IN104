#ifndef __BOARD_H__
#define __BOARD_H__


#include "Constants.h"
#include "Piece.h"
#include "Move.h"
#include "Move_Log.h"


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

/*


changing the board

make move : modifed also the log and the captured pieces 
--> make_move pour le board, le log, les captured piece

undo move : modifed also the log and the captured pieces 
--> undo_move pour le board, le log, les captured piece


clear board : close everything and free the memory 
*/




#endif /* __BOARD_H__ */