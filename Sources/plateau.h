#ifndef PLATEAU_H
#define PLATEAU_H
#include <SDL2/SDL.h>
#include "pinguin.h"
#include "elementgraphique.h"

/*Structure définissant un plateau*/
typedef struct plateau{
	SDL_Renderer *rendu;
	SDL_Texture *fond;
	Pinguin **pinguins;
	unsigned char nombrePinguins;
	ElementGraphique **elementGraphiques;
	unsigned char nombreElementGraphique;
	unsigned char vitesse;
}Plateau;

/*Fonction permettant de créer un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu, char niveau[]);

/*Fonction permettant d'actualiser les éléments du plateau*/
void plateau_actualiser(Plateau *plateau);

/*Fonction libérant la mémoire*/
void plateau_detruire(Plateau * plateau);

/*Fonction permettant de rafraichir l'affichage du plateau*/
void plateau_rafraichir(Plateau *plateau);

/*Fonction permettant de gérer les colisions*/
void plateau_gererCollision(Plateau *plateau);
#endif
