#include "button.h"

Button * button_create(SDL_Renderer *render,TypeButton type, int x, int y, int w, int h){
	Button *button=malloc(sizeof(button));
	button->position.x=x;
	button->position.y=y;
	button->position.w=w;
	button->position.h=h;
	switch(type){
		case FLOATER:
			button->background=IMG_LoadTexture(render,"img/floater_button.png");
		case MINER:
			button->background=IMG_LoadTexture(render,"img/miner_button.png");
		case BASHER:
			button->background=IMG_LoadTexture(render,"img/basher_button.png");
		case PAUSE:
			button->background=IMG_LoadTexture(render,"img/pause.png");
		break;
	}
}
