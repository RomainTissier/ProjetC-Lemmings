#include "rendu.h"

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(SDL_Renderer* rendu){
	Plateau *plateau=plateau_creer(rendu,"niveau");
	int continuer=1;
	SDL_Event event;
	while (continuer){	
		continuer=gererEvenement(&event);
 		rafraichirAffichage(rendu,plateau);
		//plateau_gererCollision(plateau);
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

/*Fonction permettant de mettre à jour l'affichage*/
static void rafraichirAffichage(SDL_Renderer *rendu, Plateau *plateau){
	SDL_RenderClear(rendu);
	plateau_rafraichir(plateau);
	plateau_gererCollision(plateau);
	SDL_RenderPresent(rendu);
	SDL_Delay(100);
}

