/**
 * board.h :
 *		Modelize the board of the game
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef BOARD_H
#define BOARD_H

#include <SDL2/SDL.h>
#include "graphiccomponent.h"
#include "button.h"
#include "penguin.h"

/*Game board structure*/
typedef struct board {
	SDL_Renderer *render;
	SDL_Texture *background;
	Penguin **penguins;
	int nbPinguins;
	GraphicComponent **graphics;
	GraphicComponent **diggedBlocks;
	GraphicComponent **bashedBlocks;
	Button *goalButton;
	Button *goalNumber;
	int nbDiggedBlocks;
	int nbBashedBlocks;
	int nbSavedPenguins;
	int goal;
	Button **panel;
	int nbPanelButton;
	int nbGraphics;
	unsigned char pause;
	int moment;
	char lastSelection;
} Board;

/*Function creating a board*/
Board* board_create(SDL_Renderer *rendu, char niveau[]);

/*Function freeing memory*/
void board_destroy(Board *board);

/*Function refreshing board's display.*/
void board_refresh(Board *board);

/*Function computing component's position*/
int board_computePosition(Board *board);

/*Function managing collision on a board*/
void board_manageCollision(Board *board);

/*Function managing events on a board*/
void board_manageEvent(Board *board, int x, int y);

#endif
