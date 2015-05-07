#ifndef PINGUIN_H
#define PINGUIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*Pinguin's state structure*/
typedef enum {
	INIT,
	WALKING,
	FALLING,
	EXITING,
	SAVE,
	FLOATING
}State;

/*Structure specifying a pinguin*/
typedef struct pinguin{
	SDL_Renderer *render;
	SDL_Texture *texture;
	SDL_Rect sprite;
	SDL_Rect position;
	State state;
	State previousState;
	unsigned char height;
	unsigned char sens;
} Pinguin;

/*Function creating a pinguin*/
Pinguin* pinguin_create(SDL_Renderer *render);

/*Function computing a pinguin position*/
void pinguin_computePosition(Pinguin *pinguin);

/*Function switching a pinguin direction*/
void pinguin_switchDirection(Pinguin *pinguin);

/*Function freeing memory*/
void pinguin_destroy(Pinguin *pinguin);

#endif
