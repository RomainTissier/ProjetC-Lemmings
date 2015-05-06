#include "render.h"

/*Function executing the render loop*/
void renderLoop(Board *board){
	int quit=0;
	SDL_Event event;
	while (!quit){
		/*Manage events*/
		quit=manageEvent(&event);
		/*Refresh display*/
		SDL_RenderClear(board->render);
		board_computePosition(board);
		board_manageCollision(board);
		board_refresh(board);
		SDL_RenderPresent(board->render);
		SDL_Delay(50*board->speed);
	}	
}

/*Function managing events*/
static int manageEvent(SDL_Event *event){
	int x,y;
	while(SDL_PollEvent(event)){
		switch(event->type){
            		case SDL_QUIT:
               			return 1;
               		break;
			case SDL_MOUSEBUTTONUP:
				SDL_GetMouseState(&x,&y);
				printf("x:%d\ny:%d\n",x,y);
				// Vérifier colision bouton
				// Vérifier colision pinguin
			break;
				
       		}
	}
	return 0;
}
