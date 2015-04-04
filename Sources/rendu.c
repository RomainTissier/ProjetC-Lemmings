#include "rendu.h"
#include "pinguin.h"

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(SDL_Renderer* rendu){
	Pinguin *pinguin=pinguin_create(rendu);
	pinguin_changerSens(pinguin);
	int x=0;
	while(x<50){
		SDL_RenderClear(rendu);
		SDL_RenderCopy(rendu, pinguin->texture, &(pinguin->spriteCourant), &(pinguin->position));
        	SDL_RenderPresent(rendu);
		SDL_Delay(100);
		pinguin_actualiser(pinguin);
		x++;
	}
}
/*
 * Exemple de code 
 while (continuer)
    {
        SDL_PollEvent(&event); 
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30)
        {
            positionZozor.x++;
            tempsPrecedent = tempsActuel;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);
    }*/


