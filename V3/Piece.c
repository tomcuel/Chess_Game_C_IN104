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
    Piece* piece = Create_Piece();
    // looking for a malloc error
    if (piece == NULL){
        printf("Error: malloc failed in Get_Piece\n");
        return NULL;
    }

    // setting the piece to the one at the position given in parameters
    piece->row = row;
    piece->col = col;
    piece->type = board[row][col]->type;
    piece->color = board[row][col]->color;
    piece->value = board[row][col]->value;
    piece->is_alive = board[row][col]->is_alive;
    piece->is_checked = board[row][col]->is_checked;
    piece->is_on_his_start_position = board[row][col]->is_on_his_start_position;

    // return the piece
    return piece;
}


bool Is_Piece_on_its_start_position(Piece* piece){
    // if the piece is a pawn
    if (piece->type == PAWN){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 2nd row
            if (piece->row == 1){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 7th row
            if (piece->row == 6){
                return true;
            }
        }
    }

    // if the piece is a rook 
    else if (piece->type == ROOK){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 1st column or the 1st row and the 8th column
            if ((piece->row == 0 && piece->col == 0) || (piece->row == 0 && piece->col == 7)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 1st column or the 8th row and the 8th column
            if ((piece->row == 7 && piece->col == 0) || (piece->row == 7 && piece->col == 7)){
                return true;
            }
        }
    }

    // if the piece is a knight
    else if (piece->type == KNIGHT){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 2nd column or the 1st row and the 7th column
            if ((piece->row == 0 && piece->col == 1) || (piece->row == 0 && piece->col == 6)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 2nd column or the 8th row and the 7th column
            if ((piece->row == 7 && piece->col == 1) || (piece->row == 7 && piece->col == 6)){
                return true;
            }
        }
    }

    // if the piece is a bishop
    else if (piece->type == BISHOP){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 3rd column or the 1st row and the 6th column
            if ((piece->row == 0 && piece->col == 2) || (piece->row == 0 && piece->col == 5)){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 3rd column or the 8th row and the 6th column
            if ((piece->row == 7 && piece->col == 2) || (piece->row == 7 && piece->col == 5)){
                return true;
            }
        }
    }

    // if the piece is a queen 
    else if (piece->type == QUEEN){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 4th column
            if (piece->row == 0 && piece->col == 3){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 4th column
            if (piece->row == 7 && piece->col == 3){
                return true;
            }
        }
    }

    // if the piece is a king
    else if (piece->type == KING){
        // if the piece is white
        if (piece->color == WHITE){
            // if the piece is on the 1st row and the 5th column
            if (piece->row == 0 && piece->col == 4){
                return true;
            }
        }
        // if the piece is black
        else if (piece->color == BLACK){
            // if the piece is on the 8th row and the 5th column
            if (piece->row == 7 && piece->col == 4){
                return true;
            }
        }
    }

    return false;
}


bool Is_Move_Valid(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

    // if the move is making no move, since it's an empty position at the beggining
    if (move->previous_row == move->destination_row && move->previous_col == move->destination_col){
        return false;
    }

    // if the move is out of the board
    if (move->previous_row < 0 || move->previous_row > 7 || move->previous_col < 0 || move->previous_col > 7 || move->destination_row < 0 || move->destination_row > 7 || move->destination_col < 0 || move->destination_col > 7){
        return false;
    }

    // if this place on the board is empty
    if (board[move->previous_row][move->previous_col]->type == NOTHING){
        return false;
    }

    else if (board[move->previous_row][move->previous_col]->type == PAWN){
        return Is_Move_Valid_Pawn(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == KNIGHT){
        return Is_Move_Valid_Knight(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == BISHOP){
        return Is_Move_Valid_Bishop(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == ROOK){
        return Is_Move_Valid_Rook(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == QUEEN){
        return Is_Move_Valid_Queen(move, board);
    }

    else if (board[move->previous_row][move->previous_col]->type == KING){
        return Is_Move_Valid_King(move, board, State_Of_Rock_and_Check, Move_Log);
    }

    return false;

}


bool Is_Move_Valid_Pawn(Move* move, Piece*** board){

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // depending on the color of the pawn we want to move, different cases are to be considered


}


Piece** Get_Pawn_Neighbors(Piece* piece, Piece*** board){
    // creating an array of 4 pieces
    Piece** neighbors_of_pawn = (Piece**)malloc(NUMBER_OF_NEIGHBORS_PAWN * sizeof(Piece*));
    // looking for a malloc error
    if (neighbors_of_pawn == NULL){
        printf("Error: malloc failed in Get_Pawn_Neighbors\n");
        return NULL;
    }

    // setting the neighbors to a piece to 0 for each attribute
    for (int i=0; i<NUMBER_OF_NEIGHBORS_PAWN; i++){
        neighbors_of_pawn[i] = Create_Piece();
        // looking for a malloc error
        if (neighbors_of_pawn[i] == NULL){
            printf("Error: malloc failed in Get_Pawn_Neighbors\n");
            return NULL;
        }
    }

    // looking at the neighbor one case on the left and adding it to the array
    if (piece->row -1 >= 0){
        neighbors_of_pawn[0]->row = piece->row -1;
        neighbors_of_pawn[0]->col = piece->col;
        neighbors_of_pawn[0]->type = board[piece->row -1][piece->col]->type;
        neighbors_of_pawn[0]->color = board[piece->row -1][piece->col]->color;
        neighbors_of_pawn[0]->value = board[piece->row -1][piece->col]->value;
        neighbors_of_pawn[0]->is_alive = board[piece->row -1][piece->col]->is_alive;
        neighbors_of_pawn[0]->is_checked = board[piece->row -1][piece->col]->is_checked;
        neighbors_of_pawn[0]->is_on_his_start_position = board[piece->row -1][piece->col]->is_on_his_start_position;
    }

    // looking at the neighbor one case on the right and adding it to the array
    else if (piece->row +1 <= 7){
        neighbors_of_pawn[1]->row = piece->row +1;
        neighbors_of_pawn[1]->col = piece->col;
        neighbors_of_pawn[1]->type = board[piece->row +1][piece->col]->type;
        neighbors_of_pawn[1]->color = board[piece->row +1][piece->col]->color;
        neighbors_of_pawn[1]->value = board[piece->row +1][piece->col]->value;
        neighbors_of_pawn[1]->is_alive = board[piece->row +1][piece->col]->is_alive;
        neighbors_of_pawn[1]->is_checked = board[piece->row +1][piece->col]->is_checked;
        neighbors_of_pawn[1]->is_on_his_start_position = board[piece->row +1][piece->col]->is_on_his_start_position;
    }

    // the two diagonals depend on the color of the piece we want to move 
    // if the piece is white
    if (piece->color == WHITE){
        // the one up and on the left of the piece
        if (piece->row -1 >= 0 && piece->col -1 >= 0){
            neighbors_of_pawn[2]->row = piece->row -1;
            neighbors_of_pawn[2]->col = piece->col -1;
            neighbors_of_pawn[2]->type = board[piece->row -1][piece->col -1]->type;
            neighbors_of_pawn[2]->color = board[piece->row -1][piece->col -1]->color;
            neighbors_of_pawn[2]->value = board[piece->row -1][piece->col -1]->value;
            neighbors_of_pawn[2]->is_alive = board[piece->row -1][piece->col -1]->is_alive;
            neighbors_of_pawn[2]->is_checked = board[piece->row -1][piece->col -1]->is_checked;
            neighbors_of_pawn[2]->is_on_his_start_position = board[piece->row -1][piece->col -1]->is_on_his_start_position;
        }

        // the one up and on the right of the piece
        if (piece->row -1 >= 0 && piece->col +1 <= 7){
            neighbors_of_pawn[3]->row = piece->row -1;
            neighbors_of_pawn[3]->col = piece->col +1;
            neighbors_of_pawn[3]->type = board[piece->row -1][piece->col +1]->type;
            neighbors_of_pawn[3]->color = board[piece->row -1][piece->col +1]->color;
            neighbors_of_pawn[3]->value = board[piece->row -1][piece->col +1]->value;
            neighbors_of_pawn[3]->is_alive = board[piece->row -1][piece->col +1]->is_alive;
            neighbors_of_pawn[3]->is_checked = board[piece->row -1][piece->col +1]->is_checked;
            neighbors_of_pawn[3]->is_on_his_start_position = board[piece->row -1][piece->col +1]->is_on_his_start_position;
        }

    }

    // if the piece is black 
    if (piece->color == BLACK){
        // the one down and on the left of the piece
        if (piece->row +1 <= 7 && piece->col -1 >= 0){
            neighbors_of_pawn[2]->row = piece->row +1;
            neighbors_of_pawn[2]->col = piece->col -1;
            neighbors_of_pawn[2]->type = board[piece->row +1][piece->col -1]->type;
            neighbors_of_pawn[2]->color = board[piece->row +1][piece->col -1]->color;
            neighbors_of_pawn[2]->value = board[piece->row +1][piece->col -1]->value;
            neighbors_of_pawn[2]->is_alive = board[piece->row +1][piece->col -1]->is_alive;
            neighbors_of_pawn[2]->is_checked = board[piece->row +1][piece->col -1]->is_checked;
            neighbors_of_pawn[2]->is_on_his_start_position = board[piece->row +1][piece->col -1]->is_on_his_start_position;
        }

        // the one down and on the right of the piece
        if (piece->row +1 <= 7 && piece->col +1 <= 7){
            neighbors_of_pawn[3]->row = piece->row +1;
            neighbors_of_pawn[3]->col = piece->col +1;
            neighbors_of_pawn[3]->type = board[piece->row +1][piece->col +1]->type;
            neighbors_of_pawn[3]->color = board[piece->row +1][piece->col +1]->color;
            neighbors_of_pawn[3]->value = board[piece->row +1][piece->col +1]->value;
            neighbors_of_pawn[3]->is_alive = board[piece->row +1][piece->col +1]->is_alive;
            neighbors_of_pawn[3]->is_checked = board[piece->row +1][piece->col +1]->is_checked;
            neighbors_of_pawn[3]->is_on_his_start_position = board[piece->row +1][piece->col +1]->is_on_his_start_position;
        }

    }


    // returning the neighbors
    return neighbors_of_pawn;
}


bool Is_Move_Valid_Pawn_En_Passant(Move* move, Piece*** board){
    
}


Piece* Taken_En_Passant(Move* move, Piece*** board){
    
}


bool Is_Move_Valid_Knight(Move* move, Piece*** board){

    // if the destination is a piece of the same color as the piece we want to move
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }
    
    // Calculate differences in row and column positions
    int row_diff = abs(move->destination_row - move->previous_row);
    int col_diff = abs(move->destination_col - move->previous_col);

    // Check if the move forms an "L" shape (2 squares in one direction and 1 square in another)
    if ((row_diff == 2 && col_diff == 1) || (row_diff == 1 && col_diff == 2)){
        // Check if the destination square is empty or contains a piece of a different color
        if (board[move->destination_row][move->destination_col]->type == NOTHING || board[move->destination_row][move->destination_col]->color != board[move->previous_row][move->previous_col]->color){
            return true;
        }
    }

    return false;
}


bool Is_Move_Valid_Bishop(Move* move, Piece*** board){
    
    // if it's not a diagonal move
    if (abs(move->previous_row - move->destination_row) == abs(move->previous_col - move->destination_col)){
        return false;
    }

    // if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
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


bool Is_Move_Valid_Rook(Move* move, Piece*** board){

    // check if the move is not horizontal or vertical
    if (move->previous_row != move->destination_row || move->previous_col != move->destination_col){
        return false;
    }

    // check if the destination is a piece of the same color
    if (board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }


    // move to the right horizontally
    if (move->previous_row == move->destination_row && move->previous_col < move->destination_col){
        for (int j = move->previous_col + 1; j < move->destination_col; j++){
            // if the rook found a piece in the line to the right (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }


    // move to the left horizontally
    else if (move->previous_row == move->destination_row && move->previous_col > move->destination_col){
        for (int j = move->previous_col - 1; j > move->destination_col; j--){
            // if the rook found a piece in the line to the left (it can be of any color)
            if (board[move->previous_row][j]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically down
    else if (move->previous_row < move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row + 1; i < move->destination_row; i++){
            // if the rook found a piece in the line down (it can be of any color)
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }

    // move vertically up
    else if (move->previous_row > move->destination_row && move->previous_col == move->destination_col){
        for (int i = move->previous_row - 1; i > move->destination_row; i--){
            // if the rook found a piece in the line up (it can be of any color)
            if (board[i][move->previous_col]->type != NOTHING){
                return false;
            }
        }
        return true;
    }
    
    // if the move is not horizontal or vertical
    return false; 
}


bool Is_Move_Valid_Queen(Move* move, Piece*** board){

    // Check if the destination is occupied by a piece of the same color
    if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
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


bool Is_Move_Valid_King(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

    // Check if the destination is occupied by a piece of the same color
    if (board[move->destination_row][move->destination_col]->type != NOTHING && board[move->destination_row][move->destination_col]->color == board[move->previous_row][move->previous_col]->color){
        return false;
    }

    // Check if the move is horizontal, vertical or diagonal but here it's only one case, its moving by one square
    // when the move make the piece remain at the same place, it's already checked in Is_Move_Valid
    if (abs(move->previous_row - move->destination_row) > 1 || abs(move->previous_col - move->destination_col) > 1){
        return false;
    }

    // Check if the move is horizontal
    /*
    need to that 
    */

    // also checking when it can be a rock

    // if the move is not horizontal, vertical or diagonal
    return false; 
}



State_Of_Rock_and_Check* Create_State_Of_Rock_and_Check(){
    State_Of_Rock_and_Check* state_of_rock_and_check = (State_Of_Rock_and_Check*)malloc(sizeof(State_Of_Rock_and_Check));
    // looking for a malloc error
    if (state_of_rock_and_check == NULL){
        printf("Error: malloc failed in Create_State_Of_Rock_and_Check\n");
        return NULL;
    }

    // setting the state of the rock and the check to false
    state_of_rock_and_check->white_rock_done = false;
    state_of_rock_and_check->white_king_moved = false;
    state_of_rock_and_check->white_left_rook_moved = false;
    state_of_rock_and_check->white_right_rook_moved = false;

    state_of_rock_and_check->is_white_king_checked = false;
                
    state_of_rock_and_check->black_rock_done = false;
    state_of_rock_and_check->black_king_moved = false;
    state_of_rock_and_check->black_left_rook_moved = false;
    state_of_rock_and_check->black_right_rook_moved = false;

    state_of_rock_and_check->is_black_king_checked = false;

    // return the state of the rock and the check
    return state_of_rock_and_check;
}


void Reset_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){
    // if the state of the rock and the check is not NULL, we can reset it
    if (State_Of_Rock_and_Check != NULL){
        // setting the state of the rock and the check to false
        State_Of_Rock_and_Check->white_rock_done = false;
        State_Of_Rock_and_Check->white_king_moved = false;
        State_Of_Rock_and_Check->white_left_rook_moved = false;
        State_Of_Rock_and_Check->white_right_rook_moved = false;

        State_Of_Rock_and_Check->is_white_king_checked = false;
                    
        State_Of_Rock_and_Check->black_rock_done = false;
        State_Of_Rock_and_Check->black_king_moved = false;
        State_Of_Rock_and_Check->black_left_rook_moved = false;
        State_Of_Rock_and_Check->black_right_rook_moved = false;

        State_Of_Rock_and_Check->is_black_king_checked = false;
    }
}


void Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check* State_Of_Rock_and_Check){
    // if the state of the rock and the check is not NULL, we can free it
    if (State_Of_Rock_and_Check != NULL){
        free(State_Of_Rock_and_Check);
    }
}



bool Is_Rock_Possible(int color /* same as player */, State_Of_Rock_and_Check* State_Of_Rock_and_Check){

}


int Get_Type_Of_Rock(Move* move, Piece*** board){

}


Move* Create_Rook_Move_during_Rock(Move* move, Piece*** board){

}


Move* Create_King_Move_during_Rock(Move* move, Piece*** board){

}


void Undo_Rook_during_Rock(Move* move, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


bool Will_Capture(Move* move, Piece*** board){

}


Captured_Piece_and_Score* Create_Captured_Piece_and_Score(int max_number_of_pieces){
    Captured_Piece_and_Score* captured_piece_and_score = (Captured_Piece_and_Score*)malloc(sizeof(Captured_Piece_and_Score));
    // looking for a malloc error
    if (captured_piece_and_score == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // allocating the memory for the array of white pieces captured
    captured_piece_and_score->white_pieces_captured = (Piece**)malloc(max_number_of_pieces * sizeof(Piece*));
    // looking for a malloc error
    if (captured_piece_and_score->white_pieces_captured == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // allocating the memory for the array of black pieces captured
    captured_piece_and_score->black_pieces_captured = (Piece**)malloc(max_number_of_pieces * sizeof(Piece*));
    // looking for a malloc error
    if (captured_piece_and_score->black_pieces_captured == NULL){
        printf("Error: malloc failed in Create_Captured_Piece_and_Score\n");
        return NULL;
    }

    // setting the number of white pieces captured to 0
    captured_piece_and_score->number_of_white_pieces_captured = 0;
    // setting the number of black pieces captured to 0
    captured_piece_and_score->number_of_black_pieces_captured = 0;
    // setting the max number of pieces
    captured_piece_and_score->max_number_of_pieces = max_number_of_pieces;
    // setting the score to 0
    captured_piece_and_score->score = 0;
    // setting the player that is winning to Player1
    captured_piece_and_score->player_that_is_winning = NO_COLOR;

    // return the captured piece and score
    return captured_piece_and_score;
}


void Reset_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score){
    // setting the number of white pieces captured to 0
    captured_piece_and_score->number_of_white_pieces_captured = 0;
    // setting the number of black pieces captured to 0
    captured_piece_and_score->number_of_black_pieces_captured = 0;

    // setting the score to 0
    captured_piece_and_score->score = 0;
    // setting the player that is winning to Player1
    captured_piece_and_score->player_that_is_winning = NO_COLOR;
}


void Destroy_Captured_Piece_and_Score(Captured_Piece_and_Score* captured_piece_and_score, int max_number_of_pieces){
    // if the captured piece and score is not NULL, we can free it
    if (captured_piece_and_score != NULL){
        // for each white piece captured, we free it
        for (int i = 0; i < max_number_of_pieces; i++){
            if (captured_piece_and_score->white_pieces_captured[i] != NULL){
                free(captured_piece_and_score->white_pieces_captured[i]);
            }
        }
        // free the array of white pieces captured
        if (captured_piece_and_score->white_pieces_captured != NULL){
            free(captured_piece_and_score->white_pieces_captured);
        }

        // for each black piece captured, we free it
        for (int i = 0; i < max_number_of_pieces; i++){
            if (captured_piece_and_score->black_pieces_captured[i] != NULL){
                free(captured_piece_and_score->black_pieces_captured[i]);
            }
        }
        // free the array of black pieces captured
        if (captured_piece_and_score->black_pieces_captured != NULL){
            free(captured_piece_and_score->black_pieces_captured);
        }

        // free the captured piece and score
        free(captured_piece_and_score);
    }
}


int Get_Value_Of_Piece(int piece_type){
    // if the piece is a pawn
    if (piece_type == PAWN){
        return PAWN_VALUE;
    }

    // if the piece is a rook
    else if (piece_type == ROOK){
        return ROOK_VALUE;
    }

    // if the piece is a knight
    else if (piece_type == KNIGHT){
        return KNIGHT_VALUE;
    }

    // if the piece is a bishop
    else if (piece_type == BISHOP){
        return BISHOP_VALUE;
    }

    // if the piece is a queen
    else if (piece_type == QUEEN){
        return QUEEN_VALUE;
    }

    // if the piece is a king
    else if (piece_type == KING){
        return KING_VALUE;
    }

    // if the piece is nothing
    return 0;
}


bool Is_Check(int color, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


int Is_Check_Mate(int color, Piece*** board, State_Of_Rock_and_Check* State_Of_Rock_and_Check, Move_Log_array* Move_Log){

}


Piece* Get_King(int color, Piece*** board){

}


Piece** Get_Pieces_That_Check_King(int color, Piece*** board, int* number_of_pieces_that_are_checking_king, Move_Log_array* Move_Log, State_Of_Rock_and_Check* state_of_rock_and_check){

}