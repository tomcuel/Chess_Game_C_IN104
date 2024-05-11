Here is a project to be carried out in pairs during a computer science course.
Our job is to code a chess game in C using the SDL library.


Here's the website to find out more about this library (which allows us to make graphics and play on them, for example): 
- https://www.libsdl.org / https://wiki.libsdl.org/SDL2/FrontPage for everything, with installation setup or link to the code of the SDL 
- the wiki_lib is very useful to be able to easily search function, things that can be done and how to implement, it's making us gain time
- --> one way to do it is by searching from the type of category of functions that act on differents parts : https://wiki.libsdl.org/SDL2/APIByCategory
- --> the other way is by searching the name, but it requires to know well the library and what it can do : https://wiki.libsdl.org/SDL2/CategoryAPI


We will have various tasks to complete as part of this project: 
- reproduce the game of chess and its many rules 
- create a graphical interface that is fun to play on (with some tests to try, know how to use it)
- code an AI to play against, with different levels 


Concerning the tests : 
- tests of the structure will be done separetely in specific folders, but things such as checking if a piece can move will done in the different versions of the game 


To run this project : 
- do the command "make" to create all the .o and .x file to run them 
- do the command "make realclean" to clean all the .x and .o file everywhere in the project
- go to the directory you want and do the command "make" to create the .o and the .x file, to run your code
- because most of the directories will just be there for testing, to make it more practical to get used to the differents parts of the code


To play the game : 
- click on buttons, depeding on the button you will need to do it twice to make sure that it was really what was attended
- some parameters to choose how to play the game will be chosen through differents menus
- to start the timer in the game, you will need to press only once the button start
- then you can play the game, but also quitting it or doing a lot of different things
- a victory menu suggests you some ways you would like to continue the game into 


Structure of the code : 

- .h file : 
- - will have the explications concerning the description of the function and what I will used for 
- - will also give the parameters the function is taking 
- - code structure : 

#ifndef __FILENAME_H__
#define __FILENAME_H__


/////////////////////////////////////////////////////////////////////////////////////
// Filename Summary : 
/**
 *
 * 
 … 
 Resume of the different functions we can find on this file
 …
 *
**/
/////////////////////////////////////////////////////////////////////////////////////


#include <…>

…
…

#include <…>


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2

 * …
 * …

 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


…
make other function
…


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2

 * …
 * …

 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


#endif /* __FILENAME_H__ */


- .c file  : 
- - will not include the header, but it will be commented to know what are the things done inside the function
- - code structure : (spacing the code to make it easy to copy and to understand)

#include "filename.h"


function_1


function_2


…
…



function_n