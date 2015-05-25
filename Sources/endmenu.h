/**
 * endmenu.h :
 *		Creation and management of the win and lose menu
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef ENDMENU_H
#define ENDMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

/*End menu types enumeration*/
typedef enum {
	WIN, LOOSE
} EndType;

/*End menu structure*/
typedef struct {
	SDL_Texture *background;
	Button *continueButton;
	Button *cancelButton;
} EndMenu;

/*Function creating the end menu*/
EndMenu *endmenu_create(SDL_Renderer *render, EndType type);

/*Function managing the buttons pressing*/
ButtonType endmenu_execute(EndMenu *menu);

/*Function freeing the end menu*/
void endmenu_destroy(EndMenu *menu);

#endif
