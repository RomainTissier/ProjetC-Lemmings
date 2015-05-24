#include "mainmenu.h"
//TODO: commenter

MainMenu *mainmenu_create(SDL_Renderer *render) {
	MainMenu *menu = malloc(sizeof(MainMenu));
	menu->background = IMG_LoadTexture(render, "img/background_menu.jpg");
	SDL_RenderClear(render);
	menu->startButton = button_create(render, LEVELS, 300, 270, 200, 68);
	menu->quitButton = button_create(render, QUIT, 300, 400, 200, 68);
	SDL_RenderCopy(render, menu->background, NULL, NULL);
	SDL_RenderCopy(render, menu->startButton->background, NULL,
			&(menu->startButton->position));
	SDL_RenderCopy(render, menu->quitButton->background, NULL,
			&(menu->quitButton->position));
	SDL_RenderPresent(render);
	return menu;
}

ButtonType mainmenu_execute(MainMenu *menu) {
	SDL_Event event;
	int x, y;
	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return -1;
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_GetMouseState(&x, &y);
			if (collisionDetectionCursorRect(x, y, menu->startButton->position)
					== POINT)
				return LEVELS;
			else if (collisionDetectionCursorRect(x, y,
					menu->quitButton->position) == POINT)
				return QUIT;
			break;
		}
	}
	return -1;
}

void mainmenu_destroy(MainMenu *m) {
	button_destroy(m->startButton);
	button_destroy(m->quitButton);
	SDL_DestroyTexture(m->background);
	free(m);
}

