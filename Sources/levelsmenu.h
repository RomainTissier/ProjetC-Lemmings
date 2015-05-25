#ifndef LEVELSMENU_H
#define LEVELSMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

#define NBLEVELS 6
//TODO:  à commenter !
typedef struct{
	SDL_Texture *background;
	Button **levelsButtons;
}LevelsMenu;

LevelsMenu *levelsmenu_create(SDL_Renderer *render);

int levelsmenu_execute(LevelsMenu *menu);

void levelsmenu_destroy(LevelsMenu *menu);

#endif
