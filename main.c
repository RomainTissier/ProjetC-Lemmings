#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

void attendre();

/**
 * Fonction main principale, qui instancie l'interface graphique
 */
int main(int argc, char *argv[]){
	// On initialise l'affichage graphique
    	SDL_Init(SDL_INIT_VIDEO);
    	SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	// On démarre la gestion des événements
	attendre();
	// On ferme l'affichage
    	SDL_Quit();
   	return EXIT_SUCCESS; 
}

/**
 * Fonction attendre() qui gère les événements de l'interface graphique
 */
void attendre(){
	int test = 1;
	// On créer un élément de type événement
	SDL_Event event;
	// Boucle de traitement des événements
    	while (test){
        	SDL_WaitEvent(&event);
        	switch(event.type){
            		case SDL_QUIT: test = 0;
        	}
    	}
}
