#include "Board.h"


Piece*** Init_Board(){
    Piece*** board = (Piece***)malloc(BOARD_SIZE * sizeof(Piece**));
    for (int i = 0; i < BOARD_SIZE; i++){
        board[i] = (Piece**)malloc(BOARD_SIZE * sizeof(Piece*));
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j] = Create_Piece();
        }
    }

    // looking for a malloc error 
    if (board == NULL){
        printf("Error: malloc failed in Init_Board\n");
        return NULL;
        for (int i = 0; i < BOARD_SIZE; i++){
            if (board[i] == NULL){
                printf("Error: malloc failed in Init_Board\n");
                return NULL;
            }
            for (int j = 0; j < BOARD_SIZE; j++){
                if (board[i][j] == NULL){
                    printf("Error: malloc failed in Init_Board\n");
                    return NULL;
                }
            }
        }
    }

    // setting the pieces on the board
    // the first two rows are for the black pieces
    // the last two rows are for the white pieces
    // the others for piece that will be initialized with everything to 0 but it's already done with the Create_Piece function
    
    // the only thing to do is to set the row and the col of the piece upto date
    // we can do that for each piece in the board, without having to do that separately for each piece
    // those will not changed for the rest of the game, but will be useful to have a shortcuts to know if a certain type of piece is still on its start position or not
    for (int i = 0; i < BOARD_SIZE; i++){
        for (int j = 0; j < BOARD_SIZE; j++){
            board[i][j]->row = i;
            board[i][j]->col = j;
        }
    }

    // placing all the piece 
    // black pieces
    // rooks
    board[0][0]->type = ROOK;
    board[0][0]->color = BLACK;
    board[0][0]->value = ROOK_VALUE;
    board[0][0]->is_alive = true;
    board[0][0]->is_checked = false;
    board[0][0]->is_on_his_start_position = true;

    board[0][7]->type = ROOK;
    board[0][7]->color = BLACK;
    board[0][7]->value = ROOK_VALUE;
    board[0][7]->is_alive = true;
    board[0][7]->is_checked = false;
    board[0][7]->is_on_his_start_position = true;

    // knights
    board[0][1]->type = KNIGHT;
    board[0][1]->color = BLACK;
    board[0][1]->value = KNIGHT_VALUE;
    board[0][1]->is_alive = true;
    board[0][1]->is_checked = false;
    board[0][1]->is_on_his_start_position = true;

    board[0][6]->type = KNIGHT;
    board[0][6]->color = BLACK;
    board[0][6]->value = KNIGHT_VALUE;
    board[0][6]->is_alive = true;
    board[0][6]->is_checked = false;
    board[0][6]->is_on_his_start_position = true;

    // bishops
    board[0][2]->type = BISHOP;
    board[0][2]->color = BLACK;
    board[0][2]->value = BISHOP_VALUE;
    board[0][2]->is_alive = true;
    board[0][2]->is_checked = false;
    board[0][2]->is_on_his_start_position = true;

    board[0][5]->type = BISHOP;
    board[0][5]->color = BLACK;
    board[0][5]->value = BISHOP_VALUE;
    board[0][5]->is_alive = true;
    board[0][5]->is_checked = false;
    board[0][5]->is_on_his_start_position = true;

    // queen
    board[0][3]->type = QUEEN;
    board[0][3]->color = BLACK;
    board[0][3]->value = QUEEN_VALUE;
    board[0][3]->is_alive = true;
    board[0][3]->is_checked = false;
    board[0][3]->is_on_his_start_position = true;

    // king
    board[0][4]->type = KING;
    board[0][4]->color = BLACK;
    board[0][4]->value = KING_VALUE;
    board[0][4]->is_alive = true;
    board[0][4]->is_checked = false;
    board[0][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[1][i]->type = PAWN;
        board[1][i]->color = BLACK;
        board[1][i]->value = PAWN_VALUE;
        board[1][i]->is_alive = true;
        board[1][i]->is_checked = false;
        board[1][i]->is_on_his_start_position = true;
    }


    // white pieces
    // rooks
    board[7][0]->type = ROOK;
    board[7][0]->color = WHITE;
    board[7][0]->value = ROOK_VALUE;
    board[7][0]->is_alive = true;
    board[7][0]->is_checked = false;
    board[7][0]->is_on_his_start_position = true;

    board[7][7]->type = ROOK;
    board[7][7]->color = WHITE;
    board[7][7]->value = ROOK_VALUE;
    board[7][7]->is_alive = true;
    board[7][7]->is_checked = false;
    board[7][7]->is_on_his_start_position = true;

    // knights
    board[7][1]->type = KNIGHT;
    board[7][1]->color = WHITE;
    board[7][1]->value = KNIGHT_VALUE;
    board[7][1]->is_alive = true;
    board[7][1]->is_checked = false;
    board[7][1]->is_on_his_start_position = true;

    board[7][6]->type = KNIGHT;
    board[7][6]->color = WHITE;
    board[7][6]->value = KNIGHT_VALUE;
    board[7][6]->is_alive = true;
    board[7][6]->is_checked = false;
    board[7][6]->is_on_his_start_position = true;

    // bishops
    board[7][2]->type = BISHOP;
    board[7][2]->color = WHITE;
    board[7][2]->value = BISHOP_VALUE;
    board[7][2]->is_alive = true;
    board[7][2]->is_checked = false;
    board[7][2]->is_on_his_start_position = true;

    board[7][5]->type = BISHOP;
    board[7][5]->color = WHITE;
    board[7][5]->value = BISHOP_VALUE;
    board[7][5]->is_alive = true;
    board[7][5]->is_checked = false;
    board[7][5]->is_on_his_start_position = true;

    // queen
    board[7][3]->type = QUEEN;
    board[7][3]->color = WHITE;
    board[7][3]->value = QUEEN_VALUE;
    board[7][3]->is_alive = true;
    board[7][3]->is_checked = false;
    board[7][3]->is_on_his_start_position = true;

    // king
    board[7][4]->type = KING;
    board[7][4]->color = WHITE;
    board[7][4]->value = KING_VALUE;
    board[7][4]->is_alive = true;
    board[7][4]->is_checked = false;
    board[7][4]->is_on_his_start_position = true;

    // pawns
    for (int i = 0; i < BOARD_SIZE; i++){
        board[6][i]->type = PAWN;
        board[6][i]->color = WHITE;
        board[6][i]->value = PAWN_VALUE;
        board[6][i]->is_alive = true;
        board[6][i]->is_checked = false;
        board[6][i]->is_on_his_start_position = true;
    }

    // finally, we can return the board
    return board;
}


void Clear_Board(Piece*** board){
    // if the board is not NULL (malloc error), we can free it
    if (board != NULL){
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++){
                Destroy_Piece(board[i][j]);
            }
            free(board[i]);
        }
        free(board);
    }
}


void Make_Move(Piece*** board, Move* move, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players){
    // we suppose that the log is updated before calling this function
    // we suppose that the move is valid
    // that the piece that will move will have it's parameters updated 
    // - for example : if a pawn got out of his start position, we will update the is_on_his_start_position attribute before calling this function
    // we can move the piece
    // first we update the destination piece with the source piece, before suppressing the source piece on the board by reinitializing it
    
    // udpating the destination piece
    board[move->destination_row][move->destination_col]->type = board[move->previous_row][move->previous_col]->type;
    board[move->destination_row][move->destination_col]->color = board[move->previous_row][move->previous_col]->color;
    board[move->destination_row][move->destination_col]->value = board[move->previous_row][move->previous_col]->value;
    board[move->destination_row][move->destination_col]->is_alive = board[move->previous_row][move->previous_col]->is_alive;
    board[move->destination_row][move->destination_col]->is_checked = board[move->previous_row][move->previous_col]->is_checked;
    board[move->destination_row][move->destination_col]->is_on_his_start_position = Is_Piece_on_its_start_position(board[move->previous_row][move->previous_col]); // here we don't have any others choice than to check if the piece is on its start position or not, not with a smart way
    // suppressing the source piece
    board[move->previous_row][move->previous_col]->type = NOTHING;
    board[move->previous_row][move->previous_col]->color = NO_COLOR;
    board[move->previous_row][move->previous_col]->value = 0;
    board[move->previous_row][move->previous_col]->is_alive = false;
    board[move->previous_row][move->previous_col]->is_checked = false;
    board[move->previous_row][move->previous_col]->is_on_his_start_position = false;

    // updating the captured pieces and the score

    // if the piece in the updated log at the last index (for the last move) is not NOTHING, then we have a captured piece
    if (log->Move_Log[log->actual_size-1]->taken_piece_type != NOTHING){
        // it then depend on the color of the piece to know which player captured it
        // if it's white : 
        if (log->Move_Log[log->actual_size-1]->taken_piece_color == WHITE){
            // updating the captured piece by its coordinates
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->col = log->Move_Log[log->actual_size-1]->move->destination_col;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->row = log->Move_Log[log->actual_size-1]->move->destination_row;
            
            // updating the other attributes of the piece
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->type = log->Move_Log[log->actual_size-1]->taken_piece_type;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->color = log->Move_Log[log->actual_size-1]->taken_piece_color;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->value = Get_Value_Of_Piece(log->Move_Log[log->actual_size-1]->taken_piece_type);
            
            // in reality, we don't care about it, but we can update it not to let it to false (NULL here)
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_alive = false;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_checked = false;
            captured_piece_and_score->white_pieces_captured[captured_piece_and_score->number_of_white_pieces_captured]->is_on_his_start_position = false;

            // incrementing the number of white pieces captured
            captured_piece_and_score->number_of_white_pieces_captured++;
            printf("test1\n");
        }
    

        // if it's black : 
        else if (log->Move_Log[log->actual_size-1]->taken_piece_color == BLACK){
            // updating the captured piece by its coordinates
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->col = log->Move_Log[log->actual_size-1]->move->destination_col;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->row = log->Move_Log[log->actual_size-1]->move->destination_row;

            // updating the other attributes of the piece
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->type = log->Move_Log[log->actual_size-1]->taken_piece_type;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->color = log->Move_Log[log->actual_size-1]->taken_piece_color;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->value = Get_Value_Of_Piece(log->Move_Log[log->actual_size-1]->taken_piece_type);

            // in reality, we don't care about it, but we can update it not to let it to false (NULL here)
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_alive = false;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_checked = false;
            captured_piece_and_score->black_pieces_captured[captured_piece_and_score->number_of_black_pieces_captured]->is_on_his_start_position = false;

            // incrementing the number of black pieces captured
            captured_piece_and_score->number_of_black_pieces_captured++;
        }
    }

    // updating the state of the rock and the check 

    // first we need to udpate the rock state
    // if it's a rock move, we need to update the state of the rock
    if (log->Move_Log[log->actual_size-1]->rock_type != NO_ROCK){
        // if it's a white rock
        if (log->Move_Log[log->actual_size-1]->taken_piece_color == WHITE){
            // we need to tell that the white_rock happened
            state_of_rock_and_check->white_rock_done = true;
        }
        // if it's a black rock
        else if (log->Move_Log[log->actual_size-1]->taken_piece_color == BLACK){
            // we need to tell that the black_rock happened
            state_of_rock_and_check->black_rock_done = true;
        }
    }

    // then we need to tell if the differents rooks are still on their start position

    // if the top left corner piece is not a black rook that is still on its starting line, then the black left rook moved
    if (board[0][0]->type != ROOK || board[0][0]->color != BLACK || board[0][0]->is_on_his_start_position == false){
        state_of_rock_and_check->black_left_rook_moved = true;
    }

    // if the top right corner piece is not a black rook that is still on its starting line, then the black right rook moved
    if (board[0][7]->type != ROOK || board[0][7]->color != BLACK || board[0][7]->is_on_his_start_position == false){
        state_of_rock_and_check->black_right_rook_moved = true;
    }

    // if the bottom left corner piece is not a white rook that is still on its starting line, then the white left rook moved
    if (board[7][0]->type != ROOK || board[7][0]->color != WHITE || board[7][0]->is_on_his_start_position == false){
        state_of_rock_and_check->white_left_rook_moved = true;
    }

    // if the bottom right corner piece is not a white rook that is still on its starting line, then the white right rook moved
    if (board[7][7]->type != ROOK || board[7][7]->color != WHITE || board[7][7]->is_on_his_start_position == false){
        state_of_rock_and_check->white_right_rook_moved = true;
    }

    // then we need to update the check state (we will deal with checkmate in another function, another part of the program)
    // we need to check if the move put the other player in check
    // the log will tell us that 
    if (log->Move_Log[log->actual_size-1]->check_state == WHITE_CHECK){
        state_of_rock_and_check->is_white_king_checked = true;
    }
    else if (log->Move_Log[log->actual_size-1]->check_state == BLACK_CHECK){
        state_of_rock_and_check->is_black_king_checked = true;
    }

    // updating the players
    Change_Players_that_is_Playing(players);

}



void Undo_Move(Piece*** board, Move* move, Move_Log_array* log, Captured_Piece_and_Score* captured_piece_and_score, State_Of_Rock_and_Check* state_of_rock_and_check, Players* players){
    // we suppose that the log is updated before calling this function
    // we suppose that the move is valid, that we can go back to the previous state (before the move is done)

}