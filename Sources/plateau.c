#include "plateau.h"

/*Fonction creant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->pinguin=pinguin_create(rendu);
	return plateau;
}
