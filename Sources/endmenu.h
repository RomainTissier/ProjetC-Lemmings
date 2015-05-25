#ifndef ENDMENU_H
#define ENDMENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

typedef enum{
	WIN,
	LOOSE
}EndType;

typedef struct{
	SDL_Texture *background;
	Button *continueButton;
	Button *cancelButton;
}EndMenu;

EndMenu *endmenu_create(SDL_Renderer *render, EndType type);

ButtonType endmenu_execute(EndMenu *menu);

void endmenu_destroy(EndMenu *menu);

#endif
