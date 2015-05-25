/**
 * mainmenu.h :
 *		Creation and management of the main menu
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

/*Main menu structure*/
typedef struct {
	SDL_Texture *background;
	Button *startButton;
	Button *quitButton;
} MainMenu;

/*Function creating the main menu*/
MainMenu *mainmenu_create(SDL_Renderer *render);

/*Function managing the buttons pressing*/
ButtonType mainmenu_execute(MainMenu *menu);

/*Function freeing the main menu*/
void mainmenu_destroy(MainMenu *menu);

#endif
