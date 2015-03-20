#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char argv[]){
	// On initialise la SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){
      		printf("Erreur SDL: %s", SDL_GetError() );
       	 	return -1;
    	}
	// Création d'une fenêtre
        SDL_Window* fenetre;
        fenetre = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);

        if( fenetre )
        {
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_DestroyWindow(fenetre);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    

    SDL_Quit();

    return 0;}
