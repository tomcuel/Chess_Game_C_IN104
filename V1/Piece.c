#include "Piece.h"


Piece* Create_Piece(){

}


void Destroy_Piece(Piece* piece){

}


Piece* Get_Piece(int row, int col, Piece*** board){

}


bool Is_Move_Valid(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Pawn(Move* move, Piece* piece, Piece*** board){

}


bool Get_State_Of_Pawn(Piece* piece, Piece*** board){

}


Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Knight(Move* move, Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Bishop(Move* move, Piece* piece, Piece*** board){
    
    // if it's not a diagonal move
    if (abs(move->previous_row - move->destination_row) == abs(move->previous_col - move->destination_col)){
        return false;
    }

    // otherwise making cases depending on the direction of the move (the diagonal direction)
    
    // moving to the right and down
    if (move->previous_row < move->destination_row && move->previous_col < move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row + 1, j = move->previous_col + 1; i < move->destination_row && j < move->destination_col; i++, j++){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the left and down 
    else if (move->previous_row < move->destination_row && move->previous_col > move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row + 1, j = move->previous_col - 1; i < move->destination_row && j > move->destination_col; i++, j--){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the right and up
    else if (move->previous_row > move->destination_row && move->previous_col < move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row - 1, j = move->previous_col + 1; i > move->destination_row && j < move->destination_col; i--, j++){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // moving to the left and up 
    else if (move->previous_row > move->destination_row && move->previous_col > move->destination_col){
        // going trough the diagonal
        for (int i = move->previous_row - 1, j = move->previous_col - 1; i > move->destination_row && j > move->destination_col; i--, j--){
            // if the bishop found a piece in the diagonal (it can be of any color)
            if (board[i][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    
}


bool Is_Move_Valid_Rook(Move* move, Piece* piece, Piece*** board){

}