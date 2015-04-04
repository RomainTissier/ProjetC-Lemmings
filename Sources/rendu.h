#ifndef RENDU_H
#define RENDU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "pinguin.h"

/*Fonction gérant les événements*/
static int gererEvenement(SDL_Event *event);

/*Fonction permettant de rafraichir l'affichage de la fentre*/
static void rafraichirAffichage(SDL_Renderer *rendu, Pinguin *pinguin);

/*Fonction exécutant la boucle de rendu*/
void boucleRendu(SDL_Renderer* rendu);

#endif
