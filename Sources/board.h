#ifndef BOARD_H
#define BOARD_H
#include <SDL2/SDL.h>
#include "pinguin.h"
#include "graphiccomponent.h"
#include "button.h"

/*Game board structure*/
typedef struct board{
	SDL_Renderer *render;
	SDL_Texture *background;
	Pinguin **pinguins;
	int nbPinguins;
	int nbPinguinsAlive;
	//TODO : tout repasser en un seul tableau
	GraphicComponent **graphics;
	GraphicComponent **green;
	GraphicComponent **orange;
	int nbGreen;
	int nbOrange;
	Button **panel;
	int nbGraphics;
	unsigned char speed;
	unsigned char pause;
	int moment;
	char idS;
}Board;

void board_createPanel(Board *board, TypeButton type_button);

/*Function creating a board*/
Board* board_create(SDL_Renderer *rendu, char niveau[]);

/*Function computing the board's component position*/
void board_computePosition(Board *board);

/*Function freeing memory*/
void board_destroy(Board *board);

/*Function refreshing a board*/
void board_refresh(Board *board);

/*Function managing collision on a board*/
void board_manageCollision(Board *board);

void board_manageEvent(Board *board,int x,int y);

#endif
