#ifndef GRAPHICCOMPONENT_H
#define GRAPHICCOMPONENT_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

/* Enumeration of the component types*/
typedef enum{
	FLOOR,
	ICE_PEAK
}Type;

/* Graphic component structure */
typedef struct GraphicComponent{
	SDL_Renderer *render;
	SDL_Rect position;
	SDL_Texture *texture;
	int destructible;
	Type type;
}GraphicComponent;

/* Function creating a graphic component */
GraphicComponent* graphicComponent_create(SDL_Renderer* render, Type type, int x, int y, int w, int h);

/*Function freeing memory*/
void graphicComponent_destroy(GraphicComponent *comp);
#endif
