#include "IA.h"


#define DEPTH_MEDIUM 1
#define DEPTH_HARD 2
#define CHECKMATE 1000000
#define STALEMATE 0


// arrays that defines the preferencial position of each type of piece
int whiteKnightScores[BOARD_SIZE][BOARD_SIZE] = {{-50,-40,-30,-30,-30,-30,-40,-50},
                                                {-40,-20,  0,  0,  0,  0,-20,-40},
                                                {-30,  0, 10, 15, 15, 10,  0,-30},
                                                {-30,  5, 15, 20, 20, 15,  5,-30},
                                                {-30,  0, 15, 20, 20, 15,  0,-30},
                                                {-30,  5, 10, 15, 15, 10,  5,-30},
                                                {-40,-20,  0,  5,  5,  0,-20,-40},
                                                {-50,-40,-30,-30,-30,-30,-40,-50}};

int blackKnightScores[BOARD_SIZE][BOARD_SIZE] = {{-50,-40,-30,-30,-30,-30,-40,-50},
                                                {-40,-20,  0,  5,  5,  0,-20,-40},
                                                {-30,  5, 10, 15, 15, 10,  5,-30},
                                                {-30,  0, 15, 20, 20, 15,  0,-30},
                                                {-30,  5, 15, 20, 20, 15,  5,-30},
                                                {-30,  0, 10, 15, 15, 10,  0,-30},
                                                {-40,-20,  0,  0,  0,  0,-20,-40},
                                                {-50,-40,-30,-30,-30,-30,-40,-50}};

int whiteBishopScores[BOARD_SIZE][BOARD_SIZE] =  {{-20,-10,-10,-10,-10,-10,-10,-20},
                                                {-10,  0,  0,  0,  0,  0,  0,-10},
                                                {-10,  0,  5, 10, 10,  5,  0,-10},
                                                {-10,  5,  5, 10, 10,  5,  5,-10},
                                                {-10,  0, 10, 10, 10, 10,  0,-10},
                                                {-10, 10, 10, 10, 10, 10, 10,-10},
                                                {-10,  5,  0,  0,  0,  0,  5,-10},
                                                {-20,-10,-10,-10,-10,-10,-10,-20}};

int blackBishopScores[BOARD_SIZE][BOARD_SIZE] = {{-20,-10,-10,-10,-10,-10,-10,-20},
                                                {-10,  5,  0,  0,  0,  0,  5,-10},
                                                {-10, 10, 10, 10, 10, 10, 10,-10},
                                                {-10,  0, 10, 10, 10, 10,  0,-10},
                                                {-10,  5,  5, 10, 10,  5,  5,-10},
                                                {-10,  0,  5, 10, 10,  5,  0,-10},
                                                {-10,  0,  0,  0,  0,  0,  0,-10},
                                                {-20,-10,-10,-10,-10,-10,-10,-20}};

int whiteRookScores[BOARD_SIZE][BOARD_SIZE] =  {{0,  0,  0,  0,  0,  0,  0,  0},
                                                {5, 10, 10, 10, 10, 10, 10,  5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {0,  0,  0,  5,  5,  0,  0,  0}};

int blackRookScores[BOARD_SIZE][BOARD_SIZE] = {{0,  0,  0,  5,  5,  0,  0,  0},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {-5,  0,  0,  0,  0,  0,  0, -5},
                                                {5, 10, 10, 10, 10, 10, 10,  5},
                                                {0,  0,  0,  0,  0,  0,  0,  0}};

int whiteQueenScores[BOARD_SIZE][BOARD_SIZE] = {{-20,-10,-10, -5, -5,-10,-10,-20},
                                                {-10,  0,  0,  0,  0,  0,  0,-10},
                                                {-10,  0,  5,  5,  5,  5,  0,-10},
                                                {-5,   0,  5,  5,  5,  5,  0, -5},
                                                {0,    0,  5,  5,  5,  5,  0, -5},
                                                {-10,  5,  5,  5,  5,  5,  0,-10},
                                                {-10,  0,  5,  0,  0,  0,  0,-10},
                                                {-20,-10,-10, -5, -5,-10,-10,-20}};

int blackQueenScores[BOARD_SIZE][BOARD_SIZE] = {{-20,-10,-10, -5, -5,-10,-10,-20},
                                                {-10,  0,  5,  0,  0,  0,  0,-10},
                                                {-10,  5,  5,  5,  5,  5,  0,-10},
                                                {0,    0,  5,  5,  5,  5,  0, -5},
                                                {-5,   0,  5,  5,  5,  5,  0, -5},
                                                {-10,  0,  5,  5,  5,  5,  0,-10},
                                                {-10,  0,  0,  0,  0,  0,  0,-10},
                                                {-20,-10,-10, -5, -5,-10,-10,-20}};

int whiteKingScores[BOARD_SIZE][BOARD_SIZE] = {{-80, -70, -70, -70, -70, -70, -70, -80}, 
                                                {-60, -60, -60, -60, -60, -60, -60, -60}, 
                                                {-40, -50, -50, -60, -60, -50, -50, -40}, 
                                                {-30, -40, -40, -50, -50, -40, -40, -30}, 
                                                {-20, -30, -30, -40, -40, -30, -30, -20}, 
                                                {-10, -20, -20, -20, -20, -20, -20, -10}, 
                                                {20,  20,  -5,  -5,  -5,  -5,  20,  20}, 
                                                {20,  30,  10,   0,   0,  10,  30,  20}};

int whiteKingScores_end[BOARD_SIZE][BOARD_SIZE] = {{-20, -10, -10, -10, -10, -10, -10, -20},
                                                    {-5,   0,   5,   5,   5,   5,   0,  -5},
                                                    {-10, -5,   20,  30,  30,  20,  -5, -10},
                                                    {-15, -10,  35,  45,  45,  35, -10, -15},
                                                    {-20, -15,  30,  40,  40,  30, -15, -20},
                                                    {-25, -20,  20,  25,  25,  20, -20, -25},
                                                    {-30, -25,   0,   0,   0,   0, -25, -30},
                                                    {-50, -30, -30, -30, -30, -30, -30, -50}};

int blackKingScores[BOARD_SIZE][BOARD_SIZE] = {{20,  30,  10,   0,   0,  10,  30,  20}, 
                                                {20,  20,  -5,  -5,  -5,  -5,  20,  20}, 
                                                {-10, -20, -20, -20, -20, -20, -20, -10}, 
                                                {-20, -30, -30, -40, -40, -30, -30, -20}, 
                                                {-30, -40, -40, -50, -50, -40, -40, -30}, 
                                                {-40, -50, -50, -60, -60, -50, -50, -40}, 
                                                {-60, -60, -60, -60, -60, -60, -60, -60}, 
                                                {-80, -70, -70, -70, -70, -70, -70, -80}};

int blackKingScores_end[BOARD_SIZE][BOARD_SIZE] = {{-50, -30, -30, -30, -30, -30, -30, -50},
                                                    {-30, -25,   0,   0,   0,   0, -25, -30},
                                                    {-25, -20,  20,  25,  25,  20, -20, -25},
                                                    {-20, -15,  30,  40,  40,  30, -15, -20},
                                                    {-15, -10,  35,  45,  45,  35, -10, -15},
                                                    {-10, -5,   20,  30,  30,  20,  -5, -10},
                                                    {-5,   0,   5,   5,   5,   5,   0,  -5},
                                                    {-20, -10, -10, -10, -10, -10, -10, -20}};

int whitePawnScores[BOARD_SIZE][BOARD_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                                {50, 50, 50, 50, 50, 50, 50, 50},
                                                {10, 10, 20, 30, 30, 20, 10, 10},
                                                {5, 5, 10, 25, 25, 10, 5, 5},
                                                {0, 0, 0, 20, 20, 0, 0, 0},
                                                {5, -5, -10, 0, 0, -10, -5, 5},
                                                {5, 10, 10, -20, -20, 10, 10, 5},
                                                {0, 0, 0, 0, 0, 0, 0, 0}};

int whitePawnScores_end[BOARD_SIZE][BOARD_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                                {80, 80, 80, 80, 80, 80, 80, 80}, 
                                                {50, 50, 50, 50, 50, 50, 50, 50},
                                                {30, 30, 30, 30, 30, 30, 30, 30},
                                                {20, 20, 20, 20, 20, 20, 20, 20},
                                                {10, 10, 10, 10, 10, 10, 10, 10},
                                                {10, 10, 10, 10, 10, 10, 10, 10},
                                                {0, 0, 0, 0, 0, 0, 0, 0}};

int blackPawnScores[BOARD_SIZE][BOARD_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                            {5, 10, 10, -20, -20, 10, 10, 5},
                                            {5, -5, -10, 0, 0, -10, -5, 5},
                                            {0, 0, 0, 20, 20, 0, 0, 0},
                                            {5, 5, 10, 25, 25, 10, 5, 5},
                                            {10, 10, 20, 30, 30, 20, 10, 10},
                                            {50, 50, 50, 50, 50, 50, 50, 50},
                                            {0, 0, 0, 0, 0, 0, 0, 0}};

int blackPawnScores_end[BOARD_SIZE][BOARD_SIZE] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                                {10, 10, 10, 10, 10, 10, 10, 10},
                                                {10, 10, 10, 10, 10, 10, 10, 10},
                                                {20, 20, 20, 20, 20, 20, 20, 20},
                                                {30, 30, 30, 30, 30, 30, 30, 30},
                                                {50, 50, 50, 50, 50, 50, 50, 50},
                                                {80, 80, 80, 80, 80, 80, 80, 80},
                                                {0, 0, 0, 0, 0, 0, 0, 0}};


int Evaluate_Board_Medium(Piece*** board){
 
    // getting a score of the board 
    // a positive score means that it's good for the white player
    // a negative score means that it's good for the black player
    int Score_Board = 0;
    for (int i=0; i< BOARD_SIZE; i++){
        for (int j=0; j< BOARD_SIZE; j++){
            // getting a score for each piece on the board
            // a piece will have a postion score if it's white, a negative one if it's black
            int piece_position_score = 0;
            // we want it to be different from nothing and king (there are of no interest to evaluate the board)
            if (board[i][j]->type != NOTHING){

                if (board[i][j]->color == WHITE){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = whitePawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = whiteKnightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = whiteBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = whiteRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = whiteQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = whiteKingScores[i][j];
                            break;
                    }
                    Score_Board += board[i][j]->value*100 + piece_position_score;
                }
                else if (board[i][j]->color == BLACK){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = blackPawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = blackKnightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = blackBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = blackRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = blackQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = blackKingScores[i][j];
                            break;
                    }
                    Score_Board -= board[i][j]->value*100 + piece_position_score;
                }
            }
        }
    }
    return Score_Board;
}


int Nega_Max_Alpha_Beta_Search_Medium(int depth, int alpha, int beta, Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){
    
    if (depth == 0){
        // first version
        int turncolor = 0;
        if (players->color_player_that_is_playing == WHITE){
            turncolor = 1;
        }
        else if (players->color_player_that_is_playing == BLACK){
            turncolor = -1;
        }
        return turncolor * Evaluate_Board_Medium(board);
    }

    // getting the next valid moves
    int number_of_valid_moves = 0;
    Move** Valid_Moves = Get_Valid_Moves(&number_of_valid_moves, players->color_player_that_is_playing, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);
    // if there are no valid moves
    if (number_of_valid_moves == 0){
        // if the player is in check 
        if (Is_Check(players->color_player_that_is_playing, board) == true){
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }
            return -CHECKMATE;
        }
        // free the memory of the valid moves
        if (Valid_Moves != NULL){
            for (int i=0; i<8*8*8*8; i++){
                Destroy_Move(Valid_Moves[i]);
            }
            free(Valid_Moves);
        }
        return STALEMATE;
    }

    // going through all the valid moves
    for (int i=0; i<number_of_valid_moves; i++){
        // make the move on the board
        Make_IA_Global_Move_and_Udpate_structures(Valid_Moves[i], board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, MEDIUM);
        // recursive call
        int score = 0;
        int color_that_was_playing = NO_COLOR;
        if (players->color_player_that_is_playing == WHITE){
            color_that_was_playing = BLACK;
        }
        else if (players->color_player_that_is_playing == BLACK){
            color_that_was_playing = WHITE;
        }
        if (Is_Check(color_that_was_playing, board) == false){
            score = - Nega_Max_Alpha_Beta_Search_Medium(depth - 1, -beta, -alpha, move, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
        }
        // Undo the last Move made 
        Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
        
        // making the pruning of the tree
        if (score >= beta){
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }
            return beta;
        }
        if (score > alpha){
            alpha = score;
            if (depth == DEPTH_MEDIUM){
                move->previous_row = Valid_Moves[i]->previous_row;
                move->previous_col = Valid_Moves[i]->previous_col;
                move->destination_row = Valid_Moves[i]->destination_row;
                move->destination_col = Valid_Moves[i]->destination_col;
            }
        }
    }

    // free the memory of the valid moves
    if (Valid_Moves != NULL){
        for (int i=0; i<8*8*8*8; i++){
            Destroy_Move(Valid_Moves[i]);
        }
        free(Valid_Moves);
    }
    return alpha;
}


int Evaluate_Board_Hard(Piece*** board){
 
    // getting a score of the board 
    // a positive score means that it's good for the white player
    // a negative score means that it's good for the black player
    int Score_Board = 0;
    for (int i=0; i< BOARD_SIZE; i++){
        for (int j=0; j< BOARD_SIZE; j++){
            // getting a score for each piece on the board
            // a piece will have a postion score if it's white, a negative one if it's black
            int piece_position_score = 0;
            // we want it to be different from nothing and king (there are of no interest to evaluate the board)
            if (board[i][j]->type != NOTHING){

                if (board[i][j]->color == WHITE){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = whitePawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = whiteKnightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = whiteBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = whiteRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = whiteQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = whiteKingScores[i][j];
                            break;
                    }
                    Score_Board += board[i][j]->value*100 + piece_position_score;
                }
                else if (board[i][j]->color == BLACK){
                    switch (board[i][j]->type){
                        case PAWN:
                            piece_position_score = blackPawnScores[i][j];
                            break;
                        case KNIGHT:
                            piece_position_score = blackKnightScores[i][j];
                            break;
                        case BISHOP:
                            piece_position_score = blackBishopScores[i][j];
                            break;
                        case ROOK:
                            piece_position_score = blackRookScores[i][j];
                            break;
                        case QUEEN:
                            piece_position_score = blackQueenScores[i][j];
                            break;
                        case KING:
                            piece_position_score = blackKingScores[i][j];
                            break;
                    }
                    Score_Board -= board[i][j]->value*100 + piece_position_score;
                }
            }
        }
    }
    return Score_Board;
}


int Nega_Max_Alpha_Beta_Search_Captures_Hard(int alpha, int beta, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){

    // getting the basic evaluation of the board
    int turncolor = 0;
    if (players->color_player_that_is_playing == WHITE){
        turncolor = 1;
    }
    else if (players->color_player_that_is_playing == BLACK){
        turncolor = -1;
    }
    int evaluation = turncolor * Evaluate_Board_Hard(board);

    // making the pruning of the tree
    if (evaluation >= beta){
        return beta;
    }
    if (evaluation > alpha){
        alpha = evaluation;
    }

    // getting the next valid moves, but only the ones that can capture a piece here in this function
    int number_of_valid_moves_that_dont_capture = 0;
    Move** Captures_Moves = Get_Valid_Moves_that_Capture(&number_of_valid_moves_that_dont_capture, players->color_player_that_is_playing, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);
   
    // if there are no valid moves that can capture a piece we return the basic evaluation of the board 
    if (number_of_valid_moves_that_dont_capture == 0){
        if (Captures_Moves != NULL && number_of_valid_moves_that_dont_capture > 0){
            for (int i=0; i<8*8*8*8; i++){
                Destroy_Move(Captures_Moves[i]);
            }
            free(Captures_Moves);
        }
        return evaluation;
    }
    
    // for each valid move found, we order them by preferences
    Order_Moves_Hard(Captures_Moves, number_of_valid_moves_that_dont_capture, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);
   
    // doing the algorithm for each capture move
    for (int i=0; i<number_of_valid_moves_that_dont_capture; i++){
        
        // make the move on the board
        Make_IA_Global_Move_and_Udpate_structures(Captures_Moves[i], board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, HARD);

        // recursive call to funciton that take care of the successive captures
        evaluation = - Nega_Max_Alpha_Beta_Search_Captures_Hard(-beta, -alpha, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
        
        // Undo the last Move made
        Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
        
        // making the pruning of the tree
        if (evaluation >= beta){
            return beta;
        }
        if (evaluation > alpha){
            alpha = evaluation;
        }
    }
    return alpha;
}


void Order_Moves_Hard(Move** moves, int number_of_moves, Piece*** board, State_Of_Rock_and_Check* state_of_rock_and_check, Move_Log_array* Move_Log, Board_Log_array* Board_Log, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){
    
    // moves are supposed to only be the one that can capture a piece
    int* moves_score_guess = (int*)malloc(number_of_moves * sizeof(int));
    // looking for malloc error
    if (moves_score_guess == NULL){
        printf("Error : malloc failed in Order_Moves_Hard\n");
        exit(1);
    }
    for (int i=0; i<number_of_moves; i++){
        moves_score_guess[i] = 0;
        int moved_piece_type = board[moves[i]->previous_row][moves[i]->previous_col]->value;
        int captured_piece_type = board[moves[i]->destination_row][moves[i]->destination_col]->value;

        // capturing a piece is a good move, but it's better to capture a piece that is worth more than the piece that is moving
        if (captured_piece_type != 0){
            moves_score_guess[i] += captured_piece_type * 100 - moved_piece_type * 10;
        }
        // promoting a pawn is a good move
        if (Is_Pawn_Promotion_Possible(moves[i], board) == true){
            moves_score_guess[i] += QUEEN * 100;
        }
        // rock is a good move
        if (Is_Rock_Possible(moves[i], state_of_rock_and_check, board) == true){
            moves_score_guess[i] += ROOK * 100;
        }
        // moving our piece is a square by a adversary piece is a not so good move
        // if the player playing is white
        if (players->color_player_that_is_playing == WHITE){
            // looking left 
            if (moves[i]->destination_row-1 >= 0 && moves[i]->destination_col-1 >= 0){
                if (board[moves[i]->destination_row-1][moves[i]->destination_col-1]->type == PAWN && board[moves[i]->destination_row-1][moves[i]->destination_col-1]->color == BLACK){
                    moves_score_guess[i] -= moved_piece_type * 10;
                }
            }
            // looking right
            if (moves[i]->destination_row-1 >= 0 && moves[i]->destination_col+1 < BOARD_SIZE){
                if (board[moves[i]->destination_row-1][moves[i]->destination_col+1]->type == PAWN && board[moves[i]->destination_row-1][moves[i]->destination_col+1]->color == BLACK){
                    moves_score_guess[i] -= moved_piece_type * 10;
                }
            }
        }
        // if the player playing is black
        else if (players->color_player_that_is_playing == BLACK){
            
            if (moves[i]->destination_row+1 < BOARD_SIZE  && moves[i]->destination_col-1 >= 0){
                if(board[moves[i]->destination_row+1][moves[i]->destination_col-1]->type == PAWN && board[moves[i]->destination_row+1][moves[i]->destination_col-1]->color == WHITE){
                    moves_score_guess[i] -= moved_piece_type * 10;
                }
            }
            
            if (moves[i]->destination_row+1 < BOARD_SIZE  && moves[i]->destination_col+1 < BOARD_SIZE){
                if (board[moves[i]->destination_row+1][moves[i]->destination_col+1]->type == PAWN && board[moves[i]->destination_row+1][moves[i]->destination_col+1]->color == WHITE){
                    moves_score_guess[i] -= moved_piece_type * 10;
                }
            }
        }
        
    }
    // sorting the moves by their score
    for (int i=0; i<number_of_moves; i++){
        for (int j=i+1; j<number_of_moves; j++){
            if (moves_score_guess[i] < moves_score_guess[j]){
                int temp = moves_score_guess[i];
                moves_score_guess[i] = moves_score_guess[j];
                moves_score_guess[j] = temp;

                Move* temp_move = Create_Move(moves[i]->previous_row, moves[i]->previous_col, moves[i]->destination_row, moves[i]->destination_col);
                Change_Move(moves[i], moves[j]->previous_row, moves[j]->previous_col, moves[j]->destination_row, moves[j]->destination_col);
                Change_Move(moves[j], temp_move->previous_row, temp_move->previous_col, temp_move->destination_row, temp_move->destination_col);
                Destroy_Move(temp_move);
            }
        }
    }
    free(moves_score_guess);
}


int Nega_Max_Alpha_Beta_Search_Hard(int depth, int alpha, int beta, Move* move, Piece*** board, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){
   
    if (depth == 0){
        return Nega_Max_Alpha_Beta_Search_Captures_Hard(alpha, beta, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
    }

    // getting the next valid moves
    int number_of_valid_moves = 0;
    Move** Valid_Moves = Get_Valid_Moves(&number_of_valid_moves, players->color_player_that_is_playing, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);
    // if there are no valid moves
    if (number_of_valid_moves == 0){
        // if the player is in check 
        if (Is_Check(players->color_player_that_is_playing, board) == true){
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }
            return -CHECKMATE;
        }
        // free the memory of the valid moves
        if (Valid_Moves != NULL){
            for (int i=0; i<8*8*8*8; i++){
                Destroy_Move(Valid_Moves[i]);
            }
            free(Valid_Moves);
        }
        return STALEMATE;
    }

    // ordering the moves 
    Order_Moves_Hard(Valid_Moves, number_of_valid_moves, board, state_of_rock_and_check, Move_Log, Board_Log, Pawn_Move_State, Captured_Pieces_and_Score, players);

    // going through all the valid moves
    for (int i=0; i<number_of_valid_moves; i++){
        
        // make the move on the board
        Make_IA_Global_Move_and_Udpate_structures(Valid_Moves[i], board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, HARD);
        
        // recursive call to the function
        int score = - Nega_Max_Alpha_Beta_Search_Hard(depth - 1, -beta, -alpha, move, board, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
        // Undo the last Move made 
        Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);

        // making the pruning of the tree
        if (score >= beta){
            // free the memory of the valid moves
            if (Valid_Moves != NULL){
                for (int i=0; i<8*8*8*8; i++){
                    Destroy_Move(Valid_Moves[i]);
                }
                free(Valid_Moves);
            }
            return beta;
        }
        if (score > alpha){
            alpha = score;
            if (depth == DEPTH_HARD){
                move->previous_row = Valid_Moves[i]->previous_row;
                move->previous_col = Valid_Moves[i]->previous_col;
                move->destination_row = Valid_Moves[i]->destination_row;
                move->destination_col = Valid_Moves[i]->destination_col;
            }
        }
    }

    // free the memory of the valid moves
    if (Valid_Moves != NULL){
        for (int i=0; i<8*8*8*8; i++){
            Destroy_Move(Valid_Moves[i]);
        }
        free(Valid_Moves);
    }
    return alpha;
}


void IA_Play(Move* move, Piece*** board, int level, int IA_color, Move_Log_array* Move_Log, Board_Log_array* Board_Log, State_Of_Rock_and_Check* state_of_rock_and_check, Tiles_Pawn* Pawn_Move_State, Captured_Piece_and_Score* Captured_Pieces_and_Score, Players* players){
    
    Piece*** board_copy = Create_Copy_Board(board);
    State_Of_Rock_and_Check* State_Of_Rock_and_Check_copy= Copy_State_Of_Rock_and_Check(state_of_rock_and_check);
    Move_Log_array* Move_Log_copy = Copy_Move_Log_array(Move_Log);
    Board_Log_array* Board_Log_copy = Create_Copy_Board_Log(Board_Log);
    Tiles_Pawn* Pawn_Move_State_copy = Copy_Tiles_Pawn(Pawn_Move_State);
    Captured_Piece_and_Score* Captured_Pieces_and_Score_copy = Copy_Captured_Piece_and_Score(Captured_Pieces_and_Score);
    Players* players_copy = Copy_Players(players);

    // a level EASY IA will play a random move, but will try to capture a piece if it can (and don't make it self in check)
    if (level == EASY){
        bool is_move_correct = false;  
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
                            // here : a white piece of the IA color can capture a black piece
                            if (IA_color == WHITE && board[k][l]->color == BLACK && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // the move need not to put the king in check
                                Make_IA_Global_Move_and_Udpate_structures(move_temp, board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, MEDIUM);
                                // if after the move made by the IA, it's in check, we need to undo the move and make another one
                                int color_we_are_checking_IA = NO_COLOR;
                                if (players->color_player_that_is_playing == WHITE){
                                    color_we_are_checking_IA = BLACK;
                                }
                                else if (players->color_player_that_is_playing == BLACK){
                                    color_we_are_checking_IA = WHITE;
                                }
                                // get the check state of the player that was playing the last move
                                bool check_state = Is_Check(color_we_are_checking_IA, board);
                                // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
                                if (check_state == false){

                                    // we check if the value of the piece captured is higher than the one we already have
                                    if (value_of_piece_captured < board[k][l]->value){
                                        move->previous_row = i;
                                        move->previous_col = j;
                                        move->destination_row = k;
                                        move->destination_col = l;
                                        value_of_piece_captured = board[k][l]->value;
                                    }

                                }
                                Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
                                   
                            }
                            // here : a black piece of the IA color can capture a white piece
                            else if (IA_color == BLACK && board[k][l]->color == WHITE && Is_Move_Valid(move_temp, board, state_of_rock_and_check, Pawn_Move_State) == true){
                                // the move need not to put the king in check
                                Make_IA_Global_Move_and_Udpate_structures(move_temp, board, players, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players->color_player_that_is_playing, MEDIUM);
                                // if after the move made by the IA, it's in check, we need to undo the move and make another one
                                int color_we_are_checking_IA = NO_COLOR;
                                if (players->color_player_that_is_playing == WHITE){
                                    color_we_are_checking_IA = BLACK;
                                }
                                else if (players->color_player_that_is_playing == BLACK){
                                    color_we_are_checking_IA = WHITE;
                                }
                                // get the check state of the player that was playing the last move
                                bool check_state = Is_Check(color_we_are_checking_IA, board);
                                // if the king of the color is in check after making a move, we need to remove the move, since it cannot be check after playing
                                if (check_state == false){

                                    // we check if the value of the piece captured is higher than the one we already have
                                    if (value_of_piece_captured < board[k][l]->value){
                                        move->previous_row = i;
                                        move->previous_col = j;
                                        move->destination_row = k;
                                        move->destination_col = l;
                                        value_of_piece_captured = board[k][l]->value;
                                    }

                                }
                                Undo_Last_Move(board, Move_Log, Board_Log, Captured_Pieces_and_Score, state_of_rock_and_check, players, Pawn_Move_State);
                                   
                            }
                        }
                    }
                }
            }
        }
        // Destroying the temporary move
        Destroy_Move(move_temp);
    }

    // a level HARD IA will play depending on a first version of the Alpha-Beta algorithm
    if (level == MEDIUM){
        
        // getting the best move possible for the IA given our functions 
        Move* best_move = Create_Move(-1, -1, -1, -1);

        // find the best move according to the Alpha-Beta algorithm
        int score = Nega_Max_Alpha_Beta_Search_Medium(DEPTH_MEDIUM, -CHECKMATE, CHECKMATE, best_move, board_copy, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
        printf("Score of the move (%d,%d) --> (%d,%d) : %d\n", best_move->previous_row, best_move->previous_col, best_move->destination_row, best_move->destination_col, score);

        move->previous_row = best_move->previous_row;
        move->previous_col = best_move->previous_col;
        move->destination_row = best_move->destination_row;
        move->destination_col = best_move->destination_col;

        Destroy_Move(best_move);
    }

    // a level HARD IA will play depending on a second version of the Alpha-Beta algorithm with moves suggestions concerning captures and rock moves, pawn promotion
    // it will order moves bases on preferences
    // it will also upgrade the evaluation function by adding some additional scores concerning pawn protection, king protection, ……
    if (level == HARD){
        // getting the best move possible for the IA given our functions 
        Move* best_move = Create_Move(-1, -1, -1, -1);

        // find the best move according to the Alpha-Beta algorithm
        int score = Nega_Max_Alpha_Beta_Search_Hard(DEPTH_HARD, -CHECKMATE, CHECKMATE, best_move, board_copy, Move_Log, Board_Log, state_of_rock_and_check, Pawn_Move_State, Captured_Pieces_and_Score, players);
        printf("Score of the move (%d,%d) --> (%d,%d) : %d\n", best_move->previous_row, best_move->previous_col, best_move->destination_row, best_move->destination_col, score);
    
        move->previous_row = best_move->previous_row;
        move->previous_col = best_move->previous_col;
        move->destination_row = best_move->destination_row;
        move->destination_col = best_move->destination_col;
       
        Destroy_Move(best_move);

    }

    // a level MASTER IA will play depending on a second version of the Alpha-Beta algorithm, with iterative deepening to manage the time of play of the IA 
    if (level == MASTER){
        
    }

    // a level GRANDMASTER IA will play depending on a third version of the Alpha-Beta algorithm, with iterative deepening, but also a log of the most famous openings, how to make checkmate fast, ……
    if (level == GRANDMASTER){
        
    }

    // free the memory
    Clear_Board(board_copy);
    Destroy_State_Of_Rock_and_Check(State_Of_Rock_and_Check_copy);
    Destroy_Move_Log_array(Move_Log_copy);
    Destroy_Board_Log(Board_Log_copy);
    Destroy_Tiles_Pawn(Pawn_Move_State_copy);
    Destroy_Captured_Piece_and_Score(Captured_Pieces_and_Score_copy, Captured_Pieces_and_Score_copy->max_number_of_pieces);
    Destroy_Players(players_copy);

}