#include "plateau.h"
#include "detectioncollision.h"

/*Fonction créant un plateau*/
/*Fonction créant un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]){
	Plateau *plateau=malloc(sizeof(Plateau));
	plateau->rendu=rendu;
	plateau->pinguin=pinguin_create(rendu);
	plateau->pinguin->position.x=50;
	int nb_lignes=0;
	int i=0;
	char nom[15];
	int nb1;
	int nb2;
	int nb3;
	int nb4;
	char char1[40];
	char niv[30];
	strcat(niv,"niveaux/");
	strcat(niv,niveau);
	FILE *f;
	f=fopen(niv, "r");
	if (f==NULL){
	}else{
		while(fgets(char1,100,f)!=NULL){
			nb_lignes++;
		}
		fclose(f);
	}
	plateau->elementGraphiques=malloc(nb_lignes*sizeof(ElementGraphique*));
	f=fopen("niveaux/niveau1", "r");	
	if (f==NULL){
		printf("erreur\n");
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
	SDL_RenderCopy(plateau->rendu, plateau->pinguin->texture, &(plateau->pinguin->spriteCourant), &(plateau->pinguin->position));
}

/*Fonction permettant de gérer les collision*/
void plateau_gererCollision(Plateau *plateau){
	pinguin_actualiser(plateau->pinguin);
	int i=0;
	int testChute=1;
	for(i;i<3;i++){
		if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguin->position)==GAUCHEDROITE){
			pinguin_changerSens(plateau->pinguin);
		}
		else if(detecterCollisionRectRect(plateau->elementGraphiques[i]->position,plateau->pinguin->position)==HAUTBAS){
			printf("Sol détecté\n");
			testChute=0;
		}
	}
	if(testChute){
		plateau->pinguin->etat=CHUTE;
	}else{
		plateau->pinguin->etat=MARCHE;
	}
}
