#include "rendu.h"

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(Plateau *plateau){
	int continuer=1;
	SDL_Event event;
	while (continuer){
		/*On gère les évenements*/
		continuer=gererEvenement(&event);
		/*On actualise l'affichage*/
		SDL_RenderClear(plateau->rendu);
		plateau_Actualiser(plateau);
		plateau_gererCollision(plateau);
		plateau_rafraichir(plateau);
		SDL_RenderPresent(plateau->rendu);
		SDL_Delay(100*plateau->vitesse);
	}	
}

/*Fonction gérant les événements*/
static int gererEvenement(SDL_Event *event){
	while(SDL_PollEvent(event)){
		switch(event->type){
            		case SDL_QUIT:
               			return 0;
               		break;
       		}
	}
	return 1;
}
