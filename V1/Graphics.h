#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include <SDL2/SDL.h>


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu rendering (clearing it and showing it)
/**
 * @param renderer : the renderer to show the menu
 * @param menu : the menu_type to show
 * @param number_of_menu : the number of menu to show
 * @param selected_menu : the selected menu
**/
/////////////////////////////////////////////////////////////////////////////////////
void Show_Menu(SDL_Renderer* renderer, int menu, int number_of_menu, int selected_menu);








#endif /* __GRAPHICS_H__ */