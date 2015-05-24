//TODO: Sens des briques pour BRIDGER
//TODO: ajouter menu GAMEOVER/WINNER copyright TISSIER TODO-WRITTING
//TODO: colision avec les bords == meurt!
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mainmenu.h"
#include "levelsmenu.h"
#include "render.h"

#define WIDTH 800
#define HEIGHT 600

/*Entry point of the program*/
int main() {
	/*Try to init SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		/*Create the main window*/
		SDL_Window *window = SDL_CreateWindow("Penguins",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
				SDL_WINDOW_SHOWN);
		/*Try the window and start the game*/
		if (window != NULL) {
			/*Initializing the render*/
			SDL_Renderer *render = SDL_CreateRenderer(window, -1,
					SDL_RENDERER_ACCELERATED);
			/*Display the menu*/
			ButtonType menuEvent;
			do {
				MainMenu *menu = mainmenu_create(render);
				menuEvent = mainmenu_execute(menu);
				SDL_RenderClear(render);
				mainmenu_destroy(menu);
				if (menuEvent == LEVELS) {
					/*Display the levels menu*/
					int level=-1;
					do{
						LevelsMenu *levelsmenu=levelsmenu_create(render);
						level= levelsmenu_execute(levelsmenu);
						levelsmenu_destroy(levelsmenu);
					}while(level==-1);
					/*Load the board*/
					char levelstr[15]="levels/level-";
					levelstr[13]=level+'0';
					levelstr[14]='\0';
					/*Start the game loop*/
					Board *board = board_create(render, levelstr);
					SDL_RenderClear(render);
					renderLoop(board);
					board_destroy(board);
				}
			} while (menuEvent!=-1 && menuEvent!=QUIT);
			/*Freeing memory*/
			SDL_DestroyRenderer(render);
			SDL_DestroyWindow(window);
			/*Close SDL*/
			SDL_Quit();
			return EXIT_SUCCESS;
		}else
		printf("SDL error! Couldn'nt initialize main window\n");
	}
	/*If error, display it and quit*/
	printf("SDL error! Can't get the driver\n");
	return EXIT_FAILURE;
}
