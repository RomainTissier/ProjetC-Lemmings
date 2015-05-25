/**
 * render.c :
 *		Refresh the board and manage clicks on the board
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#include "render.h"

/*Function executing the render loop*/
void renderLoop(Board *board) {
	unsigned char quit = 0;
	SDL_Event event;
	while (!quit) {
		/*Manage events*/
		quit = manageEvent(&event, board);
		/*Refresh display*/
		if (board->pause == 0) {
			quit = (board_computePosition(board) || quit);
			board_manageCollision(board);
		}
		board_refresh(board);
		SDL_RenderPresent(board->render);
		SDL_Delay(50);
		SDL_RenderClear(board->render);
	}
}

/*Function managing events*/
int manageEvent(SDL_Event *event, Board *board) {
	int x, y;
	while (SDL_PollEvent(event)) {
		switch (event->type) {
		case SDL_QUIT:
			return 1;
			break;
		case SDL_MOUSEBUTTONUP:
			SDL_GetMouseState(&x, &y);
			board_manageEvent(board, x, y);
			break;
		}
	}
	return 0;
}
