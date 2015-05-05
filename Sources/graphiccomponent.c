#include "graphiccomponent.h"

/* Function creating a graphic component */
GraphicComponent* graphicComponent_create(SDL_Renderer* render, Type type, int x, int y, int w, int h){
	GraphicComponent *newComp= malloc(sizeof(GraphicComponent));
	newComp->render=render;
	newComp->position.x=x;
	newComp->position.y=y;
	newComp->position.w=w;
	newComp->position.h=h;
	newComp->type=type;
	switch(type){
		case ICE_PEAK:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render,"img/icepeak.png");
			break;
		case FLOOR:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render,"img/floor.png");
			break;
		case ENTRY:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->texture=IMG_LoadTexture(render,"img/entry.png");
			break;
		case EXIT:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->texture=IMG_LoadTexture(render, "img/exit.png");
			break;
	}
	return newComp;
}

/*Function freeing memory*/
void graphicComponent_destroy(GraphicComponent *comp){
	SDL_DestroyTexture(comp->texture);
	free(comp);
}
