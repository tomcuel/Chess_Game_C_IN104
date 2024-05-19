#include "IA.h"


int Random_Int(int min, int max) {
    return min + rand() % (max - min + 1);
}


void IA_Play(Move* move, Piece*** board, int level, int IA_color, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State){
    bool is_move_correct = false;  
    // a level EASY IA will play a random move
    if (level == EASY){
        while (is_move_correct == false){
            move->previous_row = Random_Int(0, 7);
            move->previous_col = Random_Int(0, 7);
            move->destination_row = Random_Int(0, 7);
            move->destination_col = Random_Int(0, 7);
            if (Is_Move_Valid(move, board, state_of_rock_and_check, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){
                is_move_correct = true;
            }
        }
    }

    // a level MEDIUM IA will play a random move, but will try to capture a piece if it can
    if (level == MEDIUM){
        // getting the random move 
        while (is_move_correct == false){
            move->previous_row = Random_Int(0, 7);
            move->previous_col = Random_Int(0, 7);
            move->destination_row = Random_Int(0, 7);
            move->destination_col = Random_Int(0, 7);
            if (Is_Move_Valid(move, board, state_of_rock_and_check, Pawn_Move_State) == true && board[move->previous_row][move->previous_col]->color == IA_color){
                is_move_correct = true;
            }
        }
        // creating the temporary move
        Move* move_temp = Create_Move(-1, -1, -1, -1);
        // integer to track the value of the piece captured
        int value_of_piece_captured = 0;
        // if a piece can be captured, the IA will capture it by changing the move accoordingly
        // going through the starting position of the IA pieces
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                // we check if it's a valid starting position for the piece
                if (board[i][j]->type != NOTHING && board[i][j]->color == IA_color){
                    // going through the destination position of the IA pieces
                    for (int k = 0; k < 8; k++){
                        for (int l = 0; l < 8; l++){
                            move_temp->previous_row = i;
                            move_temp->previous_col = j;
                            move_temp->destination_row = k;
                            move_temp->destination_col = l;
                            // if the move is valid and the colors are the good ones
                            // here : a white piece of the IA color can capture a black piece
                            if (IA_color == WHITE && board[k][l]->color == BLACK && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // we check if the value of the piece captured is higher than the one we already have
                                if (value_of_piece_captured < board[k][l]->value){
                                    move->previous_row = i;
                                    move->previous_col = j;
                                    move->destination_row = k;
                                    move->destination_col = l;
                                    value_of_piece_captured = board[k][l]->value;
                                }
                            }
                            // here : a black piece of the IA color can capture a white piece
                            else if (IA_color == BLACK && board[k][l]->color == WHITE && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // we check if the value of the piece captured is higher than the one we already have
                                if (value_of_piece_captured < board[k][l]->value){
                                    move->previous_row = i;
                                    move->previous_col = j;
                                    move->destination_row = k;
                                    move->destination_col = l;
                                    value_of_piece_captured = board[k][l]->value;
                                }
                            }
                        }
                    }
                }
            }
        }
        // Destroying the temporary move
        Destroy_Move(move_temp);
    }

    // a level HARD is still to be implemented
    if (level == HARD){
        //Move* move_temp = Find_Best_Move(board, state_of_rock_and_check, Pawn_Move_State, IA_color);
        

        
        //Destroy_Move(move_temp);
    }
}


void Make_Pawn_Promotion_for_IA(Move* move, Piece*** board, Move_Log_array* Log, int level_IA){
     // a level EASY IA will play a random move
    if (level_IA == EASY){
        int random_piece = Random_Int(1, 4);
        switch (random_piece){
            case 1:
                board[move->destination_row][move->destination_col]->type = QUEEN;
                break;
            case 2:
                board[move->destination_row][move->destination_col]->type = ROOK;
                break;
            case 3:
                board[move->destination_row][move->destination_col]->type = BISHOP;
                break;
            case 4:
                board[move->destination_row][move->destination_col]->type = KNIGHT;
                break;
        }
    }

    // a level MEDIUM IA will play a random move, but will try to capture a piece if it can
    if (level_IA == MEDIUM){
        // this level suppose that making a queen will be the best thing to do
        board[move->destination_row][move->destination_col]->type = QUEEN;
    }

    // a level HARD is still to be implemented
    if (level_IA == HARD){
        // here it might depend if we treathe a king, if we can take more than one piece by making a fork, …
        // it's bewteen a queen and a knight
        // we take the knight if it can fork the king and another piece, fork two pieces without being taken without losses
    }

    // we might need to also do others levels of IA, if it's possible
}