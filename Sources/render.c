#include "render.h"


/*Function executing the render loop*/
void renderLoop(Board *board){
	int quit=0,fin=0;
	SDL_Event event;
	while (!quit && !fin){
		/*Manage events*/
		quit=manageEvent(&event,board);
		/*Refresh display*/
		if(board->pause==0){
			fin=board_computePosition(board);
			board_manageCollision(board);
		}
		board_refresh(board);	
		SDL_RenderPresent(board->render);
		SDL_Delay(50*board->speed);
		SDL_RenderClear(board->render);
	}	
}

/*Function managing events*/
int manageEvent(SDL_Event *event, Board *board){
	int x,y;
	while(SDL_PollEvent(event)){
		switch(event->type){
            		case SDL_QUIT:
               			return 1;
               		break;
			case SDL_MOUSEBUTTONUP:
				SDL_GetMouseState(&x,&y);
				printf("x:%d\ny:%d\n",x,y);
				board_manageEvent(board,x,y);
				// Vérifier colision bouton
				// Vérifier colision pinguin
			break;		
       		}
	}
	return 0;
}
