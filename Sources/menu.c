#include "menu.h"

Menu *menu_create(SDL_Renderer *render, TypeMenu type) {
	Menu *menu=malloc(sizeof(menu));
	menu->background=IMG_LoadTexture(render,"img/background.jpg");
	SDL_RenderClear(render);
	switch(type){
		case STARTMENU:
			menu->button=malloc(sizeof(menu->button)*2);
			menu->button[0]=button_create(render, LEVELS,0, 0, 100, 100);
			menu->button[1]=button_create(render, QUIT,0, 100, 100, 100);
			SDL_RenderCopy(render, menu->background, NULL, NULL);
			SDL_RenderCopy(render, menu->button[0]->background, NULL,&(menu->button[0]->position));
			SDL_RenderCopy(render, menu->button[1]->background, NULL,&(menu->button[1]->position));

		break;
		case PAUSEMENU:
			menu->button=malloc(sizeof(menu->button));
			menu->button[0]=button_create(render, PAUSE,0, 0, 100, 20);
			SDL_RenderCopy(render, menu->background, NULL, NULL);
			SDL_RenderCopy(render, menu->button[0]->background, NULL,&(menu->button[0]->position));
		break;
	}
	SDL_RenderPresent(render);
	return menu;
}

MenuDetection menu_detection(Menu *menu, int x, int y) {
	if (collisionDetectionCursorRect(x, y, menu->button[0]->position)==POINT) {
		return DEBUT;
	} else if (collisionDetectionCursorRect(x, y, menu->button[1]->position)==POINT) {
		return ARRET;
	}
}
