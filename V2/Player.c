#include "Player.h"


Players* Create_Players() {
    Players* players = (Players*)malloc(sizeof(Players));
    // looking for a malloc error
    if (players == NULL){
        printf("Error: malloc failed in Create_Players\n");
        return NULL;
    }

    // setting the players, to be able to be played by two humans

    players->is_player1_an_IA = HUMAN;
    players->player1_color = WHITE;
    players->player1_name = "Player1"; // for now we do that since I don't know how go ask it in game
    
    players->is_player2_an_IA = HUMAN;
    players->player2_color = BLACK;
    players->player2_name = "Player2"; // for now we do that since I don't know how go ask it in game

    // the first player to play is the player 1, the one who has the white pieces
    players->is_playing = Player1;
    players->color_player_that_is_playing = WHITE;

    // return the players
    return players;
}


void Setup_Players(Players* players, char* player1_name, char* player2_name, int player1_color, int player2_color, int is_player1_IA, int is_player2_IA){
    // we can't change the players if the players are not created
    if (players == NULL){
        printf("Error: the players are not created\n");
        return;
    }

    // changing the players caracteristics to the ones given in parameters
    players->player1_name = player1_name;
    players->player2_name = player2_name;
    players->player1_color = player1_color;
    players->player2_color = player2_color;
    players->is_player1_an_IA = is_player1_IA;
    players->is_player2_an_IA = is_player2_IA;
}


void Change_Players_that_is_Playing(Players* players){
    // we can't change the player that is playing if the players are not created
    if (players == NULL){
        printf("Error: the players are not created\n");
        return;
    }

    // changing the player that is playing by taking the opposite of the one that is playing currently, using the players structure
    
    if (players->is_playing == Player1){
        players->is_playing = Player2;
        players->color_player_that_is_playing = players->player2_color;
    } 
    else {
        players->is_playing = Player1;
        players->color_player_that_is_playing = players->player1_color;
    }
}


void Destroy_Players(Players* players){
    // if the players are not NULL, we can free them
    if (players != NULL){
        free(players);
    }
}


Move* IA_Play(Piece*** board, int level, int IA_color){
    
}