/**
 * endmenu.c :
 *		Creation and management of the win and lose menu
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#include "endmenu.h"

/*Function creating the end menu*/
EndMenu *endmenu_create(SDL_Renderer *render, EndType type) {
	EndMenu *menu = malloc(sizeof(EndMenu));
	if (type == WIN) {
		menu->background = IMG_LoadTexture(render, "img/victory.jpg");
		menu->continueButton = button_create(render, CONTINUE, 300, 270, 200,
				68);
	} else {
		menu->background = IMG_LoadTexture(render, "img/gameover.jpg");
		menu->continueButton = button_create(render, RETRY, 300, 270, 200, 68);
	}
	menu->cancelButton = button_create(render, RETURN, 300, 400, 200, 68);
	SDL_RenderCopy(render, menu->background, NULL, NULL);
	SDL_RenderCopy(render, menu->continueButton->background, NULL,
			&(menu->continueButton->position));
	SDL_RenderCopy(render, menu->cancelButton->background, NULL,
			&(menu->cancelButton->position));
	SDL_RenderPresent(render);
	return menu;
}

/*Function managing the buttons pressing*/
ButtonType endmenu_execute(EndMenu *menu) {
	SDL_Event event;
	int x, y;
	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return QUIT;
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_GetMouseState(&x, &y);
			if (collisionDetectionCursorRect(x, y,
					menu->continueButton->position) == POINT)
				return menu->continueButton->type;
			else if (collisionDetectionCursorRect(x, y,
					menu->cancelButton->position) == POINT)
				return QUIT;
			break;
		}
	}
	return QUIT;
}

/*Function freeing the end menu*/
void endmenu_destroy(EndMenu *m) {
	SDL_DestroyTexture(m->background);
	button_destroy(m->continueButton);
	button_destroy(m->cancelButton);
}

