#ifndef MAINMENU_H
#define MAINMENU_H
//TODO: commenter
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

typedef struct{
	SDL_Texture *background;
	Button *startButton;
	Button *quitButton;
}MainMenu;

MainMenu *mainmenu_create(SDL_Renderer *render);

ButtonType mainmenu_execute(MainMenu *menu);

void mainmenu_destroy(MainMenu *menu);

#endif
