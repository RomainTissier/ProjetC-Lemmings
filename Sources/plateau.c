#include "plateau.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	plateau->pinguin=pinguin_create(rendu);
	plateau->picGlace=elementgraphique_create(rendu, PIC_GLACE);
	return plateau;
}
void plateau_rafraichir(Plateau *plateau){
	pinguin_actualiser(plateau->pinguin);
	plateau_detecterColision(plateau);
	SDL_RenderCopy(plateau->rendu, plateau->picGlace->texture, NULL,&(plateau->picGlace->position));
	SDL_RenderCopy(plateau->rendu, plateau->pinguin->texture, &(plateau->pinguin->spriteCourant), &(plateau->pinguin->position));
}
static void plateau_detecterColision(Plateau *plateau){
	//Detection Verticale 
		//colision droite
		if(plateau->pinguin->position.x+plateau->pinguin->position.w >= plateau->picGlace->position.x 
			&& plateau->pinguin->position.x+plateau->pinguin->position.w < plateau->picGlace->position.x+plateau->picGlace->position.w)
			pinguin_changerSens(plateau->pinguin);
		//colision gauche
	//Detection horizontale
}
