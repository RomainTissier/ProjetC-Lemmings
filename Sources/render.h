/**
 * render.h :
 *		Refresh the board and manage clicks on the board
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.h"

/*Function executing the render loop*/
void renderLoop(Board *board);

/*Function managing event*/
int manageEvent(SDL_Event *event, Board *board);

#endif
