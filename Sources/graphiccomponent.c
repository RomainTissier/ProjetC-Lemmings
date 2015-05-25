#include "graphiccomponent.h"

//TODO: enlever les couleurs de fond des testeurs

/* Function creating a graphic component */
GraphicComponent* graphicComponent_create(SDL_Renderer* render, GraphicType type, int x, int y, int w, int h){
	GraphicComponent *newComp= malloc(sizeof(GraphicComponent));
	newComp->render=render;
	newComp->position.x=x;
	newComp->position.y=y;
	newComp->position.w=w;
	newComp->position.h=h;
	newComp->type=type;
	switch(type){
		case ICE_PEAK:
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/icepeak.png");
			break;
		case FLOOR:
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render,"img/piece2.png");
			break;
		case WALL:
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/gpiece1.png");
			break;
		case STONE_FLOOR:
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/piece10.png");
			break;
		case STONE_WALL:
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/piece9.png");
			break;
		//TODO: le repasser dans penguins
		case STOPP:
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/stopp.png");
			break;
		case WATER:
			newComp->collision=0;
			newComp->texture=IMG_LoadTexture(render, "img/water.png");
			break;
		case BRIDGEPART:
				newComp->collision=1;
				newComp->texture=IMG_LoadTexture(render, "img/bridgepart.png");
				break;
		case DECO:
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/pingu.png");
			break;
		case ENTRY:
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/entry.png");
			break;
		case EXIT:
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/exit.png");
			break;
		case DIGGEDBLOCK:
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/empty.png");
			newComp->sprite.x=x;
			newComp->sprite.y=y;
			newComp->sprite.w=w;
			newComp->sprite.h=h;
			break;
		case BASHEDBLOCK:
			newComp->collision=1;
			newComp->texture=IMG_LoadTexture(render, "img/empty.png");
			newComp->sprite.x=x;
			newComp->sprite.y=y;
			newComp->sprite.w=w;
			newComp->sprite.h=h;
			break;
	}
	return newComp;
}

/*Function freeing memory*/
void graphicComponent_destroy(GraphicComponent *comp){
	SDL_DestroyTexture(comp->texture);
	free(comp);
}
