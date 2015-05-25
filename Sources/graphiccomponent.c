#include "graphiccomponent.h"

//TODO: rename propre des images
//TODO: enlever les couleurs de fond des testeurs

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
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/icepeak.png");
			break;
		case FLOOR:
			newComp->destructible=1;
			newComp->collision=1;
<<<<<<< HEAD
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/piece2.png");
=======
			newComp->texture=IMG_LoadTexture(render,"img/floor.png");
>>>>>>> c221bef695ac675be73e46630f5ed0eca9584146
			break;
		case WALL:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/gpiece1.png");
			break;
		case STONE_FLOOR:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/piece10.png");
			break;
		case STONE_WALL:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/piece9.png");
			break;
		//TODO: le repasser dans penguins
		case STOPP:
			newComp->destructible=1;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/stopp.png");
			break;
		case WATER:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->drown=1;
			newComp->texture=IMG_LoadTexture(render, "img/water.png");
			break;
		case BRIDGEPART:
<<<<<<< HEAD
			newComp->destructible=0;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/bridgepart.png");
			break;
=======
				newComp->destructible=1;
				newComp->collision=1;
				newComp->texture=IMG_LoadTexture(render, "img/bridgepart.png");
				break;
>>>>>>> c221bef695ac675be73e46630f5ed0eca9584146
		case DECO:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/pingu.png");
			break;
		case ENTRY:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render,"img/entry.png");
			break;
		case EXIT:
			newComp->destructible=0;
			newComp->collision=0;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/exit.png");
			break;
			//TODO:assembler ses deux derniers blocks
		case DIGGEDBLOCK:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->drown=0;
			newComp->texture=IMG_LoadTexture(render, "img/select.png");
			break;
		case BASHEDBLOCK:
			newComp->destructible=0;
			newComp->collision=1;
			newComp->drown=0;
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
