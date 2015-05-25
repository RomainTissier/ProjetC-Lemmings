/**
 * penguin.h :
 *		Creation of a penguin and management of his state
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef PENGUIN_H
#define PENGUIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "collisiondetection.h"

#define SHIFT 5

/*Penguin states enumeration*/
typedef enum {
	INIT,
	WALKING,
	FALLING,
	EXITING,
	SAVED,
	FLOATING,
	KILLING,
	DEAD,
	DIGGING,
	WAITING,
	BASHING,
	BOMBING,
	BRIDGING,
	DROWNING
} PenguinState;

/*Penguin structure*/
typedef struct pinguin {
	SDL_Renderer *render;
	SDL_Texture *texture;
	SDL_Rect sprite;
	SDL_Rect position;
	PenguinState state;
	PenguinState previousState;
	CollisionDirection previousColision;
	unsigned char counter;
	unsigned char sens;
} Penguin;

/*Function creating a penguin*/
Penguin* penguin_create(SDL_Renderer *render);

/*Function computing a penguin position*/
void penguin_computePosition(Penguin *pinguin);

/*Function switching a penguin direction*/
void pinguin_switchDirection(Penguin *pinguin);

/*Function freeing memory*/
void penguin_destroy(Penguin *pinguin);

#endif
