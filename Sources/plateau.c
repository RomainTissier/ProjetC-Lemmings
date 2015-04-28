#include "plateau.h"
#include "detectioncollision.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	plateau->pinguin=pinguin_create(rendu);
	plateau->pinguin->position.x=50;
	plateau->elementGraphiques=malloc(3*sizeof(ElementGraphique*));
	plateau->elementGraphiques[0]=elementgraphique_create(rendu, SOL,0, 300, 100, 32);
	plateau->elementGraphiques[1]=elementgraphique_create(rendu, PIC_GLACE,100,0,10,32);
	plateau->elementGraphiques[2]=elementgraphique_create(rendu, SOL, 32,50,100,10);
	return plateau;
}
//TODO: boucle de destruction pinguin par pinguin
void plateau_detruire(Plateau * plateau){
	free(plateau->pinguins);
	free(plateau->elementGraphiques);
	free(plateau);
}


/*Fonction permettant de rafraichier l'affichage du plateau*/
//TODO: faire un système automatique qui parcours les tableaux
void plateau_rafraichir(Plateau *plateau){
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[0]->texture, NULL,&(plateau->elementGraphiques[0]->position));
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[1]->texture, NULL,&(plateau->elementGraphiques[1]->position));
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[2]->texture, NULL,&(plateau->elementGraphiques[2]->position));
	SDL_RenderCopy(plateau->rendu, plateau->pinguin->texture, &(plateau->pinguin->spriteCourant), &(plateau->pinguin->position));
}

/*Fonction permettant de gérer les collision*/
void plateau_gererCollision(Plateau *plateau){
	pinguin_actualiser(plateau->pinguin);
	int test=0;
	int changementSens=0;
	int i=0;
	plateau->pinguin->chute=1;
	for(i;i<3;i++){
		if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguin->position)==GAUCHEDROITE){
			pinguin_changerSens(plateau->pinguin);
		}
		else if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguin->position)==HAUTBAS){
			printf("Sol détecté\n");
			plateau->pinguin->chute=0;
		}
	}
}
