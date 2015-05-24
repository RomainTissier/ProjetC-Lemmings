#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "render.h"

int main(){
	/*Try to init SDL*/
	if (SDL_Init(SDL_INIT_VIDEO)==0){
		/*Create the main window*/
        	SDL_Window *window=SDL_CreateWindow("Pinguins", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
       		/*Try the window and start the game*/ 
		printf("On tente la sdl\n");
        if(window!=NULL){
        	printf("La sdl marche\n");
			/*Initialising the render*/
			SDL_Renderer *render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			/*Start the game*/
			Menu *menu=menu_create(render, STARTMENU);
			SDL_Event event;
						int x,y;
						int test=1;
						while(SDL_WaitEvent(&event) && test && (menu_detection(menu,x,y)!=DEBUT || menu_detection(menu,x,y)!=ARRET)){
							switch(event.type)
							{
								case SDL_QUIT :
									return 0;
								break;
								case SDL_MOUSEBUTTONUP:
									SDL_GetMouseState(&x,&y);
									test=0;
								break;
							}
						}
						SDL_RenderClear(render);
									if(menu_detection(menu,x,y)==DEBUT) {
										printf("debut");
										free(menu);
										/*Load the board*/
										SDL_RenderPresent(render);
										Board *board=board_create(render,"levels/level-2");
										/*Start the game loop*/
										renderLoop(board);
										board_destroy(board);
									}else if(menu_detection(menu,x,y)==ARRET) {
										printf("arret");
										/*Free memory*/
										free(menu);
									}
				//TODO display menu;
			//SDL_Texture *backg=IMG_LoadTexture(render,"img/background.jpg");
			//SDL_RenderCopy(render,backg,NULL,NULL);
			//SDL_RenderPresent(render);
			//SDL_Delay(3000);
			//SDL_RenderClear(render);
			/*Load the board*/
			//##Board *board=board_create(render,"levels/level-1");
			/*Start the game loop*/
			//##renderLoop(board);
			/*Free memory*/
			//##board_destroy(board);
    			SDL_DestroyRenderer(render);
        		SDL_DestroyWindow(window);
			/*Close SDL*/
 		   	SDL_Quit();
    			return EXIT_SUCCESS;
		}printf("SDL error:\n");
	}
	/*If error, display it and quit*/
	printf("SDL error:\n");
	return EXIT_FAILURE;
}
