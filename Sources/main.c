#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "rendu.h"

int main(){
	/*On essaie d'initialiser la SDL*/
	if (SDL_Init(SDL_INIT_VIDEO)==0){
		/*On crée notre fenêtre principale*/
        	SDL_Window *fenetre=SDL_CreateWindow("Les pingouins", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
       		/*On teste si la fenêtre est bien instanciée et on lance le jeu*/ 
		if(fenetre!=NULL){
			/*initialise le rendu*/
			SDL_Renderer *rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
			/*on démarre le jeu*/
				//afficherMenu(rendu);
				//recuperer niveau;
			/*On charge le plateau*/
			Plateau *plateau=plateau_creer(rendu,"niveaux/niveau1");
			/*On démarre la boucle de rendu*/
			boucleRendu(plateau);
			/* On libére la mémoire*/
    			SDL_DestroyRenderer(rendu);
        		SDL_DestroyWindow(fenetre);
			/*On ferme la SDL*/
 		   	SDL_Quit();
    			return EXIT_SUCCESS;
		}
	}
	/*Si echec, on affiche l'erreur*/
	printf("Erreur SDL: %s\n", SDL_GetError());
	return EXIT_FAILURE;
}
