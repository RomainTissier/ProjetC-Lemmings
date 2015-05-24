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
		case WALL:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render,"img/gpiece1.png");
			break;
		case STONE_FLOOR:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/piece10.png");
			break;
		case STONE_WALL:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/piece9.png");
			break;
		case STOPP:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/stopp.png");
			break;
		case WATER:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/water.png");
			break;
		case BRIDGEPART:
					newComp->destructible=0;
					newComp->collision=1;
					newComp->texture=IMG_LoadTexture(render, "img/bridgepart.png");
					break;
		case DECO:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->texture=IMG_LoadTexture(render, "img/pingu.png");
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
		case TRANS:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/select.png");
			break;
		case ORANGE:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/selectorange.png");
			break;
	}
	return newComp;
}

/*Function freeing memory*/
void graphicComponent_destroy(GraphicComponent *comp){
	SDL_DestroyTexture(comp->texture);
	free(comp);
}
