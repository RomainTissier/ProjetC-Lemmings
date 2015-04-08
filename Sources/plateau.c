#include "plateau.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->pinguin=pinguin_create(rendu);
	return plateau;
}
