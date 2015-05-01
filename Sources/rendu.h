#ifndef RENDU_H
#define RENDU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "plateau.h"

/*Fonction gérant les événements*/
static int gererEvenement(SDL_Event *event);

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(Plateau *plateau);

#endif
