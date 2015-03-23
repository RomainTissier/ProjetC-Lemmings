#include <SDL2/SDL.h>

int main(int argc, char argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){	// Initialisation/Test de la SDL
   		printf("Erreur SDL: %si\n", SDL_GetError() );
       	 	return -1;
    	}
        SDL_Window* fenetre = SDL_CreateWindow(	// Création d'une fenêtre
		"Les Lemmings", 		// Titre de la fenêtre
		SDL_WINDOWPOS_UNDEFINED, 	
        	SDL_WINDOWPOS_UNDEFINED,
		640,				// Largeur de la fenêtre
                480,				// Hauteur de la fenêtre
                SDL_WINDOW_SHOWN
	);
        if(fenetre){				// On vérifie que la fenêtre s'instancie bien
        	SDL_Delay(3000);  
        	SDL_DestroyWindow(fenetre);
        }else
            printf("Erreur SDL: %s\n",SDL_GetError());
    	SDL_Quit();
    	return EXIT_SUCCESS;
}
