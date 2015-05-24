//TODO: Sens des briques pour BRIDGER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "menu.h"
#include "render.h"

/*Entry point of the program*/
int main() {
	/*Try to init SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		/*Create the main window*/
		SDL_Window *window = SDL_CreateWindow("Penguins",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600,
				SDL_WINDOW_SHOWN);
		/*Try the window and start the game*/
		if (window != NULL) {
			/*Initializing the render*/
			SDL_Renderer *render = SDL_CreateRenderer(window, -1,
					SDL_RENDERER_ACCELERATED);
			/*Display the menu*/
			unsigned char boolMenu = 1;
			do {
				Menu *menu = menu_create(render);
				MenuDetection menuEvent = menu_execute(menu);
				SDL_RenderClear(render);
				menu_destroy(menu);
				if (menuEvent == DEBUT) {
					/*Load the board*/
					SDL_RenderClear(render);
					SDL_RenderPresent(render);
					Board *board = board_create(render, "levels/level-2");
					/*Start the game loop*/
					renderLoop(board);
					board_destroy(board);
				} else
					boolMenu=0;
			} while (boolMenu);
			/*Freeing memory*/
			SDL_DestroyRenderer(render);
			SDL_DestroyWindow(window);
			/*Close SDL*/
			SDL_Quit();
			return EXIT_SUCCESS;
		}else
		printf("SDL error:\n");
	}
	/*If error, display it and quit*/
	printf("SDL error:\n");
	return EXIT_FAILURE;
}
