#ifndef PLATEAU_H
#define PLATEAU_H
#include <SDL2/SDL.h>
#include "pinguin.h"
#include "elementgraphique.h"
/*Structure définissant un plateau*/
typedef struct plateau{
	SDL_Renderer *rendu;
	Pinguin *pinguin;
	ElementGraphique *picGlace;
}Plateau;

/*Fonction permettant de créer un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu);
void plateau_rafraichir(Plateau *plateau);
static void plateau_detecterColision(Plateau *plateau);
#endif
