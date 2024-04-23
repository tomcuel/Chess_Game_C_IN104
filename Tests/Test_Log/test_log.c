#include "Move_Log.h"

#include <stdlib.h>
#include <stdio.h>


int main (){

    printf("Test of the Move structure and the Move_Log structure at the same time\n");

    printf("Test of the Element part\n");

    Move_Log_Element* element=Create_Element_Move_Log();

    Change_Move_Log_Element(element,1,2,3,4,NO_CHECK,PAWN,BLACK, NO_ROCK);


    printf("Element_original : %d %d %d %d %d %d %d %d\n",   element->move->previous_row,
                                                element->move->previous_col,
                                                element->move->destination_row,
                                                element->move->destination_col,
                                                element->check_state,
                                                element->taken_piece_color,
                                                element->taken_piece_type, 
                                                element->rock_type);

    Move_Log_Element* element2=Copy_Move_Log_Element(element);

    printf("Element_copy : %d %d %d %d %d %d %d %d\n",   element2->move->previous_row,
                                                element2->move->previous_col,
                                                element2->move->destination_row,
                                                element2->move->destination_col,
                                                element2->check_state,
                                                element2->taken_piece_color,
                                                element2->taken_piece_type,
                                                element2->rock_type);


    printf("\n");   

    printf("Test of the Log part\n");                                       
    
    int maximum_size=5;
    Move_Log_array* Log=Create_Move_Log_array(maximum_size);

    Log->Move_Log[0]->move->previous_row=1;
    Log->Move_Log[0]->move->previous_col=2;
    Log->Move_Log[0]->move->destination_row=3;
    Log->Move_Log[0]->move->destination_col=4;
    Log->Move_Log[0]->check_state=NO_CHECK;
    Log->Move_Log[0]->taken_piece_color=PAWN;
    Log->Move_Log[0]->taken_piece_type=BLACK;
    Log->Move_Log[0]->rock_type=NO_ROCK;

    Log->Move_Log[1]->move->previous_row=7;

    Log->actual_size=2;

    printf("Log part : %d %d \n", Log->actual_size, Log->max_size);

    printf("Log part : %d %d \n", Get_Move_Log_array_Size(Log), Log->max_size);

    printf("is empty ? : %d\n", Is_Move_Log_array_Empty(Log));

    printf("Log part0 : %d %d %d %d %d %d %d %d\n",   Log->Move_Log[0]->move->previous_row,
                                                Log->Move_Log[0]->move->previous_col,
                                                Log->Move_Log[0]->move->destination_row,
                                                Log->Move_Log[0]->move->destination_col,
                                                Log->Move_Log[0]->check_state,
                                                Log->Move_Log[0]->taken_piece_color,
                                                Log->Move_Log[0]->taken_piece_type, 
                                                Log->Move_Log[0]->rock_type);
   
    element=Get_Move_Log_Element_at_Index(Log,0);
    printf ("Element at index 0 : %d %d %d %d %d %d %d %d\n",   element->move->previous_row,
                                                element->move->previous_col,
                                                element->move->destination_row,
                                                element->move->destination_col,
                                                element->check_state,
                                                element->taken_piece_color,
                                                element->taken_piece_type,
                                                element->rock_type);
    
    element=Get_Move_Log_Element_at_Index(Log,1);
    printf ("Element at index 1 : %d %d %d %d %d %d %d %d\n",   element->move->previous_row,
                                                element->move->previous_col,
                                                element->move->destination_row,
                                                element->move->destination_col,
                                                element->check_state,
                                                element->taken_piece_color,
                                                element->taken_piece_type,
                                                element->rock_type);

    element=Get_First_Element_of_Move_Log_array(Log);
    printf ("Element at index 0 : %d %d %d %d %d %d %d %d\n",   element->move->previous_row,
                                                element->move->previous_col,
                                                element->move->destination_row,
                                                element->move->destination_col,
                                                element->check_state,
                                                element->taken_piece_color,
                                                element->taken_piece_type,
                                                element->rock_type);

    element=Get_Last_Element_of_Move_Log_array(Log);
    printf ("Element at index 1 : %d %d %d %d %d %d %d %d\n",   element->move->previous_row,
                                                element->move->previous_col,
                                                element->move->destination_row,
                                                element->move->destination_col,
                                                element->check_state,
                                                element->taken_piece_color,
                                                element->taken_piece_type,
                                                element->rock_type);

    // warning : we can't print the element because it's NULL when we want to get an element at an index that doesn't exist yet



    Move_Log_array* Log2=Copy_Move_Log_array(Log);

    Move_Log_array_MESSAGE_TYPE message=Add_Element_in_Move_Log_array_at_Index(Log2,element2,1);

    printf("message : %d\n", message);

    printf("Log2 part : %d %d \n", Log2->actual_size, Log2->max_size);
    printf("Log2 part0 : %d %d %d %d %d %d %d %d\n",   Log2->Move_Log[0]->move->previous_row,
                                                Log2->Move_Log[0]->move->previous_col,
                                                Log2->Move_Log[0]->move->destination_row,
                                                Log2->Move_Log[0]->move->destination_col,
                                                Log2->Move_Log[0]->check_state,
                                                Log2->Move_Log[0]->taken_piece_color,
                                                Log2->Move_Log[0]->taken_piece_type, 
                                                Log2->Move_Log[0]->rock_type);

    printf("Log2 part1 : %d %d %d %d %d %d %d %d\n",   Log2->Move_Log[1]->move->previous_row,
                                                Log2->Move_Log[1]->move->previous_col,
                                                Log2->Move_Log[1]->move->destination_row,
                                                Log2->Move_Log[1]->move->destination_col,
                                                Log2->Move_Log[1]->check_state,
                                                Log2->Move_Log[1]->taken_piece_color,
                                                Log2->Move_Log[1]->taken_piece_type, 
                                                Log2->Move_Log[1]->rock_type);


    printf("Log2 part2 : %d %d %d %d %d %d %d %d\n",   Log2->Move_Log[2]->move->previous_row,
                                                Log2->Move_Log[2]->move->previous_col,
                                                Log2->Move_Log[2]->move->destination_row,
                                                Log2->Move_Log[2]->move->destination_col,
                                                Log2->Move_Log[2]->check_state,
                                                Log2->Move_Log[2]->taken_piece_color,
                                                Log2->Move_Log[2]->taken_piece_type,
                                                Log2->Move_Log[2]->rock_type);

    Move_Log_array_MESSAGE_TYPE message2=Remove_Element_in_Move_Log_array_at_Index(Log2,1);

    printf("message : %d\n", message2);

    printf("Log2 part : %d %d \n", Log2->actual_size, Log2->max_size);
    printf("Log2 part0 : %d %d %d %d %d %d %d %d\n",   Log2->Move_Log[0]->move->previous_row,
                                                Log2->Move_Log[0]->move->previous_col,
                                                Log2->Move_Log[0]->move->destination_row,
                                                Log2->Move_Log[0]->move->destination_col,
                                                Log2->Move_Log[0]->check_state,
                                                Log2->Move_Log[0]->taken_piece_color,
                                                Log2->Move_Log[0]->taken_piece_type,
                                                Log2->Move_Log[0]->rock_type);

    printf("Log2 part1 : %d %d %d %d %d %d %d %d\n",   Log2->Move_Log[1]->move->previous_row,
                                                Log2->Move_Log[1]->move->previous_col,
                                                Log2->Move_Log[1]->move->destination_row,
                                                Log2->Move_Log[1]->move->destination_col,
                                                Log2->Move_Log[1]->check_state,
                                                Log2->Move_Log[1]->taken_piece_color,
                                                Log2->Move_Log[1]->taken_piece_type,
                                                Log2->Move_Log[1]->rock_type);


    Destroy_Move_Log_array(Log2);
    Destroy_Move_Log_array(Log);
    
    Destroy_Move_Log_Element(element);
    Destroy_Move_Log_Element(element2);

    return EXIT_SUCCESS;
}