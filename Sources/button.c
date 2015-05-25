/**
 * button.c :
 *		Creation and management of the game buttons
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#include "button.h"

/*Function creating a button*/
Button * button_create(SDL_Renderer *render, ButtonType type, int x, int y,
		int w, int h) {
	Button *button = malloc(sizeof(Button));
	button->position.x = x;
	button->position.y = y;
	button->position.w = w;
	button->position.h = h;
	button->type = type;
	switch (type) {
	case FLOATER:
		button->background = IMG_LoadTexture(render, "img/floater_button.png");
		break;
	case BASHER:
		button->background = IMG_LoadTexture(render, "img/basher_button.png");
		break;
	case BLOCKER:
		button->background = IMG_LoadTexture(render, "img/blocker_button.png");
		break;
	case BOMBER:
		button->background = IMG_LoadTexture(render, "img/bomber_button.png");
		break;
	case BRIDGER:
		button->background = IMG_LoadTexture(render, "img/bridger_button.png");
		break;
	case DIGGER:
		button->background = IMG_LoadTexture(render, "img/digger_button.png");
		break;
	case RETURN:
		button->background = IMG_LoadTexture(render, "img/retour_button.png");
		break;
	case PAUSE:
		button->background = IMG_LoadTexture(render, "img/pause.png");
		break;
	case LEVELS:
		button->background = IMG_LoadTexture(render, "img/start_button.png");
		break;
	case QUIT:
		button->background = IMG_LoadTexture(render, "img/quit_button.png");
		break;
	case RETRY:
		button->background = IMG_LoadTexture(render,
				"img/reessayer_button.png");
		break;
	case CONTINUE:
		button->background = IMG_LoadTexture(render,
				"img/continuer_button.png");
		break;
	case LEVEL1:
		button->background = IMG_LoadTexture(render, "img/level1_button.png");
		break;
	case LEVEL2:
		button->background = IMG_LoadTexture(render, "img/level2_button.png");
		break;
	case LEVEL3:
		button->background = IMG_LoadTexture(render, "img/level3_button.png");
		break;
	case LEVEL4:
		button->background = IMG_LoadTexture(render, "img/level4_button.png");
		break;
	case LEVEL5:
		button->background = IMG_LoadTexture(render, "img/level5_button.png");
		break;
	case LEVEL6:
		button->background = IMG_LoadTexture(render, "img/level6_button.png");
		break;
	case GOAL:
		button->background = IMG_LoadTexture(render, "img/savegoal.png");
		break;
	case GOAL1:
		button->background = IMG_LoadTexture(render, "img/goal1.png");
		break;
	case GOAL2:
		button->background = IMG_LoadTexture(render, "img/goal2.png");
		break;
	case GOAL3:
		button->background = IMG_LoadTexture(render, "img/goal3.png");
		break;
	case GOAL4:
		button->background = IMG_LoadTexture(render, "img/goal4.png");
		break;
	case GOAL5:
		button->background = IMG_LoadTexture(render, "img/goal5.png");
		break;
	case GOAL6:
		button->background = IMG_LoadTexture(render, "img/goal6.png");
		break;
	case GOAL7:
		button->background = IMG_LoadTexture(render, "img/goal7.png");
		break;
	case GOAL8:
		button->background = IMG_LoadTexture(render, "img/goal8.png");
		break;
	case GOAL9:
		button->background = IMG_LoadTexture(render, "img/goal9.png");
		break;
	case GOAL10:
		button->background = IMG_LoadTexture(render, "img/goal10.png");
		break;
	}
	return button;
}

/*Function freeing a button*/
void button_destroy(Button *b) {
	SDL_DestroyTexture(b->background);
	free(b);
}
