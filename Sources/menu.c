#include "menu.h"

Menu *menu_create(SDL_Renderer *render, TypeMenu type) {
	Menu *menu=malloc(sizeof(menu));
	SDL_RenderClear(render);
	switch(type){
		case STARTMENU:
			menu->background=IMG_LoadTexture(render,"img/background_menu.jpg");
			menu->button=malloc(sizeof(menu->button)*2);
			menu->button[0]=button_create(render, LEVELS,300, 270, 200, 68);
			menu->button[1]=button_create(render, QUIT,300, 400, 200, 68);
			SDL_RenderCopy(render, menu->background, NULL, NULL);
			SDL_RenderCopy(render, menu->button[0]->background, NULL,&(menu->button[0]->position));
			SDL_RenderCopy(render, menu->button[1]->background, NULL,&(menu->button[1]->position));

		break;
		case LEVELSMENU:
		menu->background=IMG_LoadTexture(render,"img/background_levels.jpg");
		menu->button=malloc(sizeof(menu->button)*6);
		menu->button[0]=button_create(render, LEVEL1,170, 270, 60, 68);
		menu->button[1]=button_create(render, LEVEL2,370, 270, 60, 68);
		menu->button[2]=button_create(render, LEVEL3,570, 270, 60, 68);
		menu->button[3]=button_create(render, LEVEL4,170, 400, 60, 68);
		menu->button[4]=button_create(render, LEVEL5,370, 400, 60, 68);
		menu->button[5]=button_create(render, LEVEL6,570, 400, 60, 68);
		SDL_RenderCopy(render, menu->background, NULL, NULL);
		SDL_RenderCopy(render, menu->button[0]->background, NULL,&(menu->button[0]->position));
		SDL_RenderCopy(render, menu->button[1]->background, NULL,&(menu->button[1]->position));
		SDL_RenderCopy(render, menu->button[2]->background, NULL,&(menu->button[2]->position));
		SDL_RenderCopy(render, menu->button[3]->background, NULL,&(menu->button[3]->position));
		SDL_RenderCopy(render, menu->button[4]->background, NULL,&(menu->button[4]->position));
		SDL_RenderCopy(render, menu->button[5]->background, NULL,&(menu->button[5]->position));

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
	return NO;
}
