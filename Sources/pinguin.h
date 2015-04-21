#ifndef PINGUIN_H
#define PINGUIN_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*Structure définissant un pinguin*/
typedef struct pinguin{
	SDL_Renderer *rendu;
	SDL_Texture *texture;
	SDL_Rect spriteCourant;
	SDL_Rect position;
	unsigned char sens;
	unsigned char chute;
} Pinguin;

/*Fonction permettant de créer un pinguin*/
Pinguin* pinguin_create(SDL_Renderer *rendu);

/*Fonction permettant d'actualiser l'affichage d'un pinguin*/
void pinguin_actualiser(Pinguin *pinguin);

/*Fonction permettant de faire changer de sens au pinguin*/
void pinguin_changerSens(Pinguin *pinguin);

#endif
