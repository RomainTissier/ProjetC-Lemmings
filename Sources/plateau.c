#include "plateau.h"
#include "detectioncollision.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	plateau->fond=IMG_LoadTexture(plateau->rendu, "img/fond.jpg");
	plateau->vitesse=1;
	
	/*On charge les pinguins TODO: plusieurs pinguins*/
	plateau->nombrePinguins=1;
	plateau->pinguins=malloc(plateau->nombrePinguins*sizeof(Pinguin*));
	plateau->pinguins[0]=pinguin_create(rendu);
	plateau->pinguins[0]->position.x=50;
	
	/*On charge les éléments graphiques*/
	FILE *f=fopen(niveau, "r");	
	if (f!=NULL){
		plateau->nombreElementGraphique=0;
		char chaine[100];
		while(fgets(chaine,100,f)!=NULL){
			char nom[15];
			int type,nb1,nb2,nb3,nb4;
			sscanf(chaine, "%s %d %d %d %d", nom, &nb1, &nb2, &nb3 , &nb4);
			plateau->elementGraphiques=realloc(plateau->elementGraphiques,(plateau->nombreElementGraphique+1)*sizeof(ElementGraphique*));
			if(!strcmp(nom,"PIC_GLACE"))
				type=PIC_GLACE;
			else if(!strcmp(nom, "SOL"))
				type=SOL;
			plateau->elementGraphiques[plateau->nombreElementGraphique]=elementgraphique_create(rendu, type, nb1, nb2, nb3, nb4);
			plateau->nombreElementGraphique++;
		}
		fclose(f);
	}else return NULL;
	return plateau;
}

/*Fonction permettant de libérer la mémoire*/
void plateau_detruire(Plateau * plateau){
	int i;
	for(i=0;i<plateau->nombrePinguins;i++)
		pinguin_detruire(plateau->pinguins[i]);
	for(i=0;i<plateau->nombreElementGraphique;i++)
		elementgraphique_detruire(plateau->elementGraphiques[i]);
	free(plateau->pinguins);
	free(plateau->elementGraphiques);
	free(plateau);
}

/*Fonction permettant de rafraichier l'affichage du plateau. TODO: optimiser en ne rafraichissant qu'une partie du rendu*/
void plateau_rafraichir(Plateau *plateau){
	SDL_RenderCopy(plateau->rendu,plateau->fond,NULL,NULL);
	int i;
	for(i=0;i<plateau->nombreElementGraphique;i++)
		SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[i]->texture, NULL,&(plateau->elementGraphiques[i]->position));
	for(i=0;i<plateau->nombrePinguins;i++)
		SDL_RenderCopy(plateau->rendu,plateau->pinguins[i]->texture, &(plateau->pinguins[i]->spriteCourant), &(plateau->pinguins[i]->position));
}

/*Fonction permettant d'actualiser les éléments du plateau*/
void plateau_actualiser(Plateau *plateau){
	int i;
	for(i=0;i<plateau->nombrePinguins;i++)
		pinguin_actualiser(plateau->pinguins[i]);
}

/*Fonction permettant de gérer les collision*/
void plateau_gererCollision(Plateau *plateau){
	int elt,pin;	
	for(pin=0;pin<plateau->nombrePinguins;pin++){
		int testChute=1;
		for(elt=0;elt<plateau->nombreElementGraphique;elt++){
			switch(detecterCollisionRectRect(plateau->elementGraphiques[elt]->position,plateau->pinguins[pin]->position)){
				case GAUCHEDROITE : pinguin_changerSens(plateau->pinguins[pin]); break;
				case HAUTBAS : testChute=0; break;
			}
		}
		plateau->pinguins[pin]->etat=(testChute)?CHUTE:MARCHE;
	}
}
