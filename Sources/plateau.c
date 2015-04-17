#include "plateau.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	//test allocation
	//plateau->pinguins=malloc(sizeof(void*));
	//plateau->pinguins[0]=pinguin_create(rendu);
	plateau->pinguin=pinguin_create(rendu);
	plateau->elementGraphiques=malloc(2*sizeof(ElementGraphique*));
	plateau->elementGraphiques[0]=elementgraphique_create(rendu, PIC_GLACE,0, 0, 10, 32);
	plateau->elementGraphiques[1]=elementgraphique_create(rendu, PIC_GLACE,100,0,10,32);
	return plateau;
}

void plateau_rafraichir(Plateau *plateau){
	pinguin_actualiser(plateau->pinguin);
	//plateau_detecterColision(plateau);
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[0]->texture, NULL,&(plateau->elementGraphiques[0]->position));
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[1]->texture, NULL,&(plateau->elementGraphiques[1]->position));
	SDL_RenderCopy(plateau->rendu, plateau->pinguin->texture, &(plateau->pinguin->spriteCourant), &(plateau->pinguin->position));
}
static void plateau_detecterColision(Plateau *plateau){
	//Detection Verticale 
		//colision droite
		//if(plateau->pinguin->position.x+plateau->pinguin->position.w >= plateau->picGlace->position.x 
		//	&& plateau->pinguin->position.x+plateau->pinguin->position.w < plateau->picGlace->position.x+plateau->picGlace->position.w)
		//	pinguin_changerSens(plateau->pinguin);
		//colision gauche
	//Detection horizontale
}
