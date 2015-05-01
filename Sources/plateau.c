#include "plateau.h"
#include "detectioncollision.h"

/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	
	plateau->pinguins=malloc(sizeof(Pinguin*));
	plateau->pinguins[0]=pinguin_create(rendu);
	plateau->pinguins[0]->position.x=50;
	
	int nb_lignes=0;
	int i=0;
	char nom[15];
	int nb1;
	int nb2;
	int nb3;
	int nb4;
	char char1[40];
	FILE *f;
	f=fopen(niveau,"r");
	if (f==NULL){
		return NULL;
	}else{
		while(fgets(char1,100,f)!=NULL){
			nb_lignes++;
		}
		fclose(f);
	}
	plateau->elementGraphiques=malloc(nb_lignes*sizeof(ElementGraphique*));
	f=fopen(niveau, "r");	
	if (f==NULL){
		return NULL;
	}
	else{
		printf("hello2\n");
		while(fgets(char1,100,f)!=NULL){
			//printf("Cette ligne comporte %d caracteres.\n", nb_car-1);
			printf("%s\n", char1);
				//printf("picglace\n");
				sscanf(char1, "%s %d %d %d %d", nom, &nb1, &nb2, &nb3 , &nb4);
				printf("%s\n", nom);
				if(!strcmp(nom,"PIC_GLACE")){
					plateau->elementGraphiques[i]=elementgraphique_create(rendu, PIC_GLACE, nb1, nb2, nb3, nb4);
				}
				else if(!strcmp(nom, "SOL")){
					plateau->elementGraphiques[i]=elementgraphique_create(rendu, SOL, nb1, nb2, nb3, nb4);
				}
				else{
					plateau->elementGraphiques[i]=elementgraphique_create(rendu, EAU, nb1, nb2, nb3, nb4);
				}
				//plateau->elementGraphiques[i]=elementgraphique_create(rendu, PIC_GLACE, nb1, nb2, nb3, nb4);
			i++;
		}
		printf("xx\n");
		fclose(f);
	}
	plateau->nombreElementGraphique=nb_lignes;
	plateau->vitesse=1;
	//plateau->elementGraphiques[0]=elementgraphique_create(rendu, SOL,0, 300, 100, 32);
	//plateau->elementGraphiques[1]=elementgraphique_create(rendu, PIC_GLACE,100,0,10,32);
	//plateau->elementGraphiques[2]=elementgraphique_create(rendu, SOL, 32,50,100,10);
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
	SDL_Texture *texture;
	texture=IMG_LoadTexture(plateau->rendu, "img/fond.jpg");
	SDL_RenderCopy(plateau->rendu,texture,NULL,NULL);
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[0]->texture, NULL,&(plateau->elementGraphiques[0]->position));
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[1]->texture, NULL,&(plateau->elementGraphiques[1]->position));
	SDL_RenderCopy(plateau->rendu, plateau->elementGraphiques[2]->texture, NULL,&(plateau->elementGraphiques[2]->position));
	SDL_RenderCopy(plateau->rendu, plateau->pinguins[0]->texture, &(plateau->pinguins[0]->spriteCourant), &(plateau->pinguins[0]->position));

}

void plateau_Actualiser(Plateau *plateau){
	pinguin_actualiser(plateau->pinguins[0]);
}

/*Fonction permettant de gérer les collision*/
void plateau_gererCollision(Plateau *plateau){
	int i=0;
	int testChute=1;
	for(i;i<3;i++){
		if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguins[0]->position)==GAUCHEDROITE){
			pinguin_changerSens(plateau->pinguins[0]);
		}
		else if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguins[0]->position)==HAUTBAS){
			printf("Sol détecté\n");
			testChute=0;
		}
	}
	if(testChute){
		plateau->pinguins[0]->etat=CHUTE;
	}else{
		plateau->pinguins[0]->etat=MARCHE;
	}
}
