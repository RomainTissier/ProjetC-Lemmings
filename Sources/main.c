#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "render.h"
#include "menu.h"

int main(){
	/*Try to init SDL*/
	if (SDL_Init(SDL_INIT_VIDEO)==0){
		/*Create the main window*/
        	SDL_Window *window=SDL_CreateWindow("Pinguins", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
       		/*Try the window and start the game*/
		if(window!=NULL){
			/*Initialising the render*/
			SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			/*Start the game*/
			Menu *menu=menu_create(render, STARTMENU);
			SDL_Delay(1000);
			SDL_Event event;
			int x,y;
			SDL_WaitEvent(&event);
			switch(event.type)
			{
				case SDL_QUIT :
					return 0;
				break;
				case SDL_MOUSEBUTTONUP:
					SDL_GetMouseState(&x,&y);
				break;
				default:
					SDL_Delay(3000);
			}
			//free(menu);
			/*Load the board*/
			Board *board=board_create(render,"levels/level-1");
			/*Start the game loop*/
			renderLoop(board);
			/*Free memory*/
			board_destroy(board);
    			SDL_DestroyRenderer(render);
        		SDL_DestroyWindow(window);
			/*Close SDL*/
 		   	SDL_Quit();
    			return EXIT_SUCCESS;
		}
	}
	/*If error, display it and quit*/
	printf("SDL error: %s\n", SDL_GetError());
	return EXIT_FAILURE;
}
