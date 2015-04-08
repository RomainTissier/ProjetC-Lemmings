#ifndef PLATEAU_H
#define PLATEAU_H
#include <SDL2/SDL.h>
#include "pinguin.h"

/*Structure définissant un plateau*/
typedef struct plateau{
	Pinguin *pinguin;
}Plateau;

/*Fonction permettant de créer un plateau*/
Plateau* plateau_creer(SDL_Renderer *rendu);
#endif
