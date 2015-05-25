#ifndef BOARD_H
#define BOARD_H
#include <SDL2/SDL.h>
#include "graphiccomponent.h"
#include "button.h"
#include "penguin.h"

/*Game board structure*/
typedef struct board{
	SDL_Renderer *render;
	SDL_Texture *background;
	Penguin **penguins;
	int nbPinguins;
	GraphicComponent **graphics;
	GraphicComponent **diggedBlocks;
	GraphicComponent **bashedBlocks;
	int nbDiggedBlocks;
	int nbBashedBlocks;
	int nbSavedPenguins;
	Button **panel;
	int nbPanelButton;
	int nbGraphics;
	unsigned char pause;
	int moment;
	char lastSelection;
}Board;

/*Function creating a board*/
Board* board_create(SDL_Renderer *rendu, char niveau[]);

/*Function computing the board's component position*/
int board_computePosition(Board *board);

/*Function freeing memory*/
void board_destroy(Board *board);

/*Function refreshing a board*/
void board_refresh(Board *board);

/*Function managing collision on a board*/
void board_manageCollision(Board *board);

void board_manageEvent(Board *board,int x,int y);

#endif
