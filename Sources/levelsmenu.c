#include "levelsmenu.h"
//TODO: A commenter !
LevelsMenu *levelsmenu_create(SDL_Renderer *render) {
	LevelsMenu *menu =malloc(sizeof(LevelsMenu));
	menu->background=IMG_LoadTexture(render,"img/background_levels.jpg");
	menu->levelsButtons=malloc(sizeof(Button*)*NBLEVELS);
	menu->levelsButtons[0]=button_create(render, LEVEL1,170, 270, 60, 68);
	menu->levelsButtons[1]=button_create(render, LEVEL2,370, 270, 60, 68);
	menu->levelsButtons[2]=button_create(render, LEVEL3,570, 270, 60, 68);
	menu->levelsButtons[3]=button_create(render, LEVEL4,170, 400, 60, 68);
	menu->levelsButtons[4]=button_create(render, LEVEL5,370, 400, 60, 68);
	menu->levelsButtons[5]=button_create(render, LEVEL6,570, 400, 60, 68);
	SDL_RenderCopy(render, menu->background, NULL, NULL);
	int i;
	for(i=0;i<NBLEVELS;i++)
		SDL_RenderCopy(render, menu->levelsButtons[i]->background, NULL,&(menu->levelsButtons[i]->position));
	SDL_RenderPresent(render);
	return menu;
}

int levelsmenu_execute(LevelsMenu *menu) {
	SDL_Event event;
	int x, y,i;
	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return -1;
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_GetMouseState(&x, &y);
			for(i=0;i<NBLEVELS;i++ ){
				if(collisionDetectionCursorRect(x, y, menu->levelsButtons[i]->position)==POINT)
					return menu->levelsButtons[i]->type-LEVEL1+1;
			}
			break;
		}
	}
	return -1;
}

void levelsmenu_destroy(LevelsMenu *m) {
	SDL_DestroyTexture(m->background);
	int i;
	for(i=0;i<NBLEVELS;i++)
		button_destroy(m->levelsButtons[i]);
	free(m->levelsButtons);
	free(m);
}

