#ifndef LEVELSMENU_H
#define LEVELSMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

#define NBLEVELS 6

/*Levels menu structure*/
typedef struct{
	SDL_Texture *background;
	Button **levelsButtons;
}LevelsMenu;

/*Function creating the levels menu*/
LevelsMenu *levelsmenu_create(SDL_Renderer *render);

/*Function managing the buttons pressing*/
int levelsmenu_execute(LevelsMenu *menu);

/*Function freeing the levels menu*/
void levelsmenu_destroy(LevelsMenu *menu);

#endif
