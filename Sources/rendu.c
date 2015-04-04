#include "rendu.h"

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(SDL_Renderer* rendu){
	Pinguin *pinguin=pinguin_create(rendu);
	pinguin_changerSens(pinguin);
	int continuer=1;
	SDL_Event event;
	while (continuer){	
		continuer=gererEvenement(&event);
 		rafraichirAffichage(rendu,pinguin);
	}
}
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
static void rafraichirAffichage(SDL_Renderer *rendu,Pinguin *pinguin){
	SDL_RenderClear(rendu);
	SDL_RenderCopy(rendu, pinguin->texture, &(pinguin->spriteCourant), &(pinguin->position));
       	SDL_RenderPresent(rendu);
	pinguin_actualiser(pinguin);
	SDL_Delay(200);
}

