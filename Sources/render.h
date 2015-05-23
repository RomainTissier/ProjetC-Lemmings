#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.h"

/*Function wich manage event*/

/*Function executing the render loop*/
void renderLoop(Board *board);
int manageEvent(SDL_Event *event, Board *board);

int quit;

#endif
