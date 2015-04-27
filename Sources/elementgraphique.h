#ifndef ELEMENTGRAPHIQUE_H
#define ELEMENTGRAPHIQUE_H

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

/* Enumération déterminant les différents types d'éléments graphiques*/
typedef enum{
	SOL,
	EAU,
	PIC_GLACE
}TypeElement;

/* Structure définissant un élément graphique */
typedef struct elementgraphique{
	SDL_Renderer *rendu;
	SDL_Rect position;
	SDL_Rect sprite;
	SDL_Texture *texture;
	int demolissable;
	TypeElement type;
}ElementGraphique;

static ElementGraphique* creerSol(SDL_Renderer* rendu, int x, int y, int w, int h);

/*Fonction privée permettant de créer un pic de glace*/
static ElementGraphique* creerPicGlace(SDL_Renderer* rendu,int x,int y,int w, int h);

/* Fonction permettant de créer un élément graphique */
ElementGraphique* elementgraphique_create(SDL_Renderer* rendu, TypeElement type, int x, int y, int w, int h);

#endif
