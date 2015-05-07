#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum{
	FLOATER,
	MINER,
	BASHER,
	PAUSE,
	LEVELS,
	QUIT
}TypeButton;

typedef struct{
	SDL_Rect position;
	SDL_Texture *background;
	unsigned char STATE;
}Button; 

Button * button_create(SDL_Renderer *render,TypeButton type, int x, int y, int w, int h);

Button * button_updateState(Button button);

#endif
