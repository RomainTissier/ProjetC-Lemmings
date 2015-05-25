/**
 * graphiccomponent.h :
 *		Creation and management of all the graphic components
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

/* Component types enumeration*/
typedef enum {
	FLOOR,
	STONE_FLOOR,
	ICE_PEAK,
	WATER,
	WALL,
	STONE_WALL,
	DECO,
	ENTRY,
	EXIT,
	DIGGEDBLOCK,
	BASHEDBLOCK,
	STOPP,
	BRIDGEPART
} GraphicType;

/* Graphic component structure */
typedef struct {
	SDL_Renderer *render;
	SDL_Rect position;
	SDL_Texture *texture;
	SDL_Rect sprite;
	GraphicType type;
	unsigned char collision;
} GraphicComponent;

/* Function creating a graphic component */
GraphicComponent* graphicComponent_create(SDL_Renderer* render,
		GraphicType type, int x, int y, int w, int h);

/*Function freeing memory*/
void graphicComponent_destroy(GraphicComponent *comp);

#endif
