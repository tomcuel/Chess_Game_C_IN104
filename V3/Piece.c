#include "Piece.h"


Piece* Create_Piece(){
    Piece* piece = (Piece*)malloc(sizeof(Piece));
    // looking for a malloc error
    if (piece == NULL){
        printf("Error: malloc failed in Create_Piece\n");
        return NULL;
    }

    // setting the piece to 0 for each attribute
    piece->row = 0;
    piece->col = 0;
    piece->type = NOTHING;
    piece->color = NO_COLOR;
    piece->value = 0;
    piece->is_alive = false;
    piece->is_checked = false;
    piece->is_on_his_start_position = false;

    // return the piece
    return piece;
}


void Destroy_Piece(Piece* piece){
    // if the piece is not NULL, we can free it
    if (piece != NULL){
        free(piece);
    }
}


Piece* Get_Piece(int row, int col, Piece*** board){

    //Get_Piece - get the piece that is on the board at the given position

    // if the position is out of the board
    if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE){
        return NULL;
    }

    // return the piece at the given position
    return board[row][col];
}


bool Is_Move_Valid(Move* move, Piece* piece, Piece*** board){

    // if the move is not valid for the piece
    if (piece->type == NOTHING){
        return false;
    }

    else if (piece->type == PAWN){
        return Is_Move_Valid_Pawn(move, piece, board);
    }

    else if (piece->type == KNIGHT){
        return Is_Move_Valid_Knight(move, piece, board);
    }

    else if (piece->type == BISHOP){
        return Is_Move_Valid_Bishop(move, piece, board);
    }

    else if (piece->type == ROOK){
        return Is_Move_Valid_Rook(move, piece, board);
    }

    else if (piece->type == QUEEN){
        return Is_Move_Valid_Queen(move, piece, board);
    }

    else if (piece->type == KING){
        return Is_Move_Valid_King(move, piece, board);
    }

    return false;

}


bool Is_Move_Valid_Pawn(Move* move, Piece* piece, Piece*** board){

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == piece->color){
        return false;
    }

    // if the pawn is moving forward
    if (move->previous_col == move->destination_col){
        // if the pawn is moving forward by 1 square
        if (abs(move->previous_row - move->destination_row) == 1){
            // if the destination square is empty
            if (board[move->destination_row][move->destination_col]->type == NOTHING){
                return true;
            }
        }

        // if the pawn is moving forward by 2 squares
        else if (abs(move->previous_row - move->destination_row) == 2){
            // if the pawn is on his start position
            if (piece->is_on_his_start_position){
                // if the destination square is empty
                if (board[move->destination_row][move->destination_col]->type == NOTHING){
                    // if the square between the start and destination squares is empty
                    if (board[(move->previous_row + move->destination_row) / 2][move->destination_col]->type == NOTHING){
                        return true;
                    }
                }
            }
        }
    }

}


bool Get_State_Of_Pawn(Piece* piece, Piece*** board){

}


Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board){

}


bool Is_Move_Valid_Knight(Move* move, Piece* piece, Piece*** board){

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == piece->color){
        return false;
    }
    
    // Calculate differences in row and column positions
    int row_diff = abs(move->destination_row - move->previous_row);
    int col_diff = abs(move->destination_col - move->previous_col);

    // Check if the move forms an "L" shape (2 squares in one direction and 1 square in another)
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)){
        // Check if the destination square is empty or contains a piece of a different color
        if (board[move->destination_row][move->destination_col]->type == NOTHING ||
            board[move->destination_row][move->destination_col]->color != piece->color){
            return true;
        }
    }

    return false;
}



bool Is_Move_Valid_Bishop(Move* move, Piece* piece, Piece*** board){
    
    // if it's not a diagonal move
    if (abs(move->previous_row - move->destination_row) == abs(move->previous_col - move->destination_col)){
        return false;
    }

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == piece->color){
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

    // check if the move is not horizontal or vertical
    if (move->previous_row != move->destination_row || move->previous_col != move->destination_col){
        return false;
    }

    // check if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == piece->color){
        return false;
    }


    // move to the right horizontally
    if (move->previous_row == move->destination_row && move->previous_col < move->destination_col){
        for (int j = move->previous_col + 1; j < move->destination_col; j++){
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }


    // move to the left horizontally
    else if (move->previous_row == move->destination_row && move->previous_col > move->destination_col){
        for (int j = move->previous_col - 1; j > move->destination_col; j--){
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically down
    else if (move->previous_row < move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row + 1; i < move->destination_row; i++){
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically up
    else if (move->previous_row > move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row - 1; i > move->destination_row; i--){
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }
    
    // if the move is not horizontal or vertical
    return false; 
}



bool Is_Move_Valid_Queen(Move* move, Piece* piece, Piece*** board){

    // Check if the destination is occupied by a piece of the same color
    if (board[move->destination_row][move->destination_col]->type != NOTHING &&
        board[move->destination_row][move->destination_col]->color == piece->color){
        return false;
    }

    // Check horizontal moves to the right
    if (move->previous_row == move->destination_row && move->previous_col < move->destination_col){
        for (int j = move->previous_col + 1; j < move->destination_col; j++){
            // if the queen found a piece in the horizontal move to the right (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // Check horizontal moves to the left
    else if (move->previous_row == move->destination_row && move->previous_col > move->destination_col){
        for (int j = move->previous_col - 1; j > move->destination_col; j--){
            if (board[move->previous_row][j]->type != NOTHING){
                // if the queen found a piece in the horizontal move to the left (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check vertical moves downward
    else if (move->previous_row < move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row + 1; i < move->destination_row; i++){
            if (board[i][move->previous_col]->type != NOTHING){
                // if the queen found a piece in the vertical down move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check vertical moves upward
    else if (move->previous_row > move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row - 1; i > move->destination_row; i--){
            if (board[i][move->previous_col]->type != NOTHING){
                // if the queen found a piece in the vertical up move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves upward and to the right
    else if (move->previous_row > move->destination_row && move->previous_col < move->destination_col){
        for (int i = move->previous_row - 1, j = move->previous_col + 1; i > move->destination_row && j < move->destination_col; i--, j++){
            if (board[i][j]->type != NOTHING){
                // if the queen found a piece in the diagonal up and right move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves upward and to the left
    else if (move->previous_row > move->destination_row && move->previous_col > move->destination_col){
        for (int i = move->previous_row - 1, j = move->previous_col - 1; i > move->destination_row && j > move->destination_col; i--, j--){
            if (board[i][j]->type != NOTHING){
                // if the queen found a piece in the diagonal up and left move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves downward and to the right
    else if (move->previous_row < move->destination_row && move->previous_col < move->destination_col){
        for (int i = move->previous_row + 1, j = move->previous_col + 1; i < move->destination_row && j < move->destination_col; i++, j++){
            if (board[i][j]->type != NOTHING){
                // if the queen found a piece in the diagonal down and right move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves downward and to the left
    else if (move->previous_row < move->destination_row && move->previous_col > move->destination_col){
        for (int i = move->previous_row + 1, j = move->previous_col - 1; i < move->destination_row && j > move->destination_col; i++, j--){
            if (board[i][j]->type != NOTHING){
                // if the queen found a piece in the diagonal down and left move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    return false;

}


bool Is_Move_Valid_King(Move* move, Piece* piece, Piece*** board){

    // Check if the destination is occupied by a piece of the same color
    if (board[move->destination_row][move->destination_col]->type != NOTHING &&
        board[move->destination_row][move->destination_col]->color == piece->color){
        return false;
    }

    // Check horizontal moves to the right
    if (move->previous_row == move->destination_row && move->previous_col < move->destination_col){
        for (int j = move->previous_col + 1; j < move->destination_col; j++){
            // if the king found a piece in the horizontal move to the right (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // Check horizontal moves to the left
    else if (move->previous_row == move->destination_row && move->previous_col > move->destination_col){
        for (int j = move->previous_col - 1; j > move->destination_col; j--){
            if (board[move->previous_row][j]->type != NOTHING){
                // if the king found a piece in the horizontal move to the left (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check vertical moves downward
    else if (move->previous_row < move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row + 1; i < move->destination_row; i++){
            if (board[i][move->previous_col]->type != NOTHING){
                // if the king found a piece in the vertical down move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check vertical moves upward
    else if (move->previous_row > move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row - 1; i > move->destination_row; i--){
            if (board[i][move->previous_col]->type != NOTHING){
                // if the king found a piece in the vertical up move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves upward and to the right
    else if (move->previous_row > move->destination_row && move->previous_col < move->destination_col){
        for (int i = move->previous_row - 1, j = move->previous_col + 1; i > move->destination_row && j < move->destination_col; i--, j++){
            if (board[i][j]->type != NOTHING){
                // if the king found a piece in the diagonal up and right move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves upward and to the left
    else if (move->previous_row > move->destination_row && move->previous_col > move->destination_col){
        for (int i = move->previous_row - 1, j = move->previous_col - 1; i > move->destination_row && j > move->destination_col; i--, j--){
            if (board[i][j]->type != NOTHING){
                // if the king found a piece in the diagonal up and left move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves downward and to the right
    else if (move->previous_row < move->destination_row && move->previous_col < move->destination_col){
        for (int i = move->previous_row + 1, j = move->previous_col + 1; i < move->destination_row && j < move->destination_col; i++, j++){
            if (board[i][j]->type != NOTHING){
                // if the king found a piece in the diagonal down and right move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    // Check diagonal moves downward and to the left
    else if (move->previous_row < move->destination_row && move->previous_col > move->destination_col){
        for (int i = move->previous_row + 1, j = move->previous_col - 1; i < move->destination_row && j > move->destination_col; i++, j--){
            if (board[i][j]->type != NOTHING){
                // if the king found a piece in the diagonal down and left move (it can be of any color)
                return false;
            }
        }
        return true;
    }

    return false; 
}



State_Of_Rock_and_Check* Create_State_Of_Rock_and_Check(){

}


void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


bool Is_Rock_Possible(int color /* same as player */, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


int Get_Type_Of_Rock(Move* move, Piece*** board){

}


Move* Create_Rook_Move_during_Rock(Piece* piece, Move* move, Piece*** board){

}


Move* Create_King_Move_during_Rock(Piece* piece, Move* move, Piece*** board){

}


void Undo_Rook_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


bool Will_Capture(Move* move, Piece*** board){

}


Captured_Piece_and_Score* Create_Captured_Piece_and_Score(int max_number_of_pieces){

}


void Destroy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score, int max_number_of_pieces){

}


void Add_Piece_To_Captured_Pieces(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score){

}


void Update_Score(Piece* piece, Captured_Piece_and_Score* captured_piece_and_score){

}


bool Is_Check(int color, Piece*** board){

}


bool Is_Check_Mate(int color, Piece*** board){

}


Piece** Get_Pieces_That_Check_King(int color, Piece*** board, int* number_of_pieces_that_are_checking_king){

}