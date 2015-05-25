#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "board.h"


/*Function executing the render loop*/
void renderLoop(Board *board);

/*Function wich manage event*/
int manageEvent(SDL_Event *event, Board *board);

#endif
