#ifndef MENU_H
#define MENU_H
//TODO : ceci est le menu principal
//TODO: ajouter menu GAMEOVER/WINNER copyright TISSIER TODO-WRITTING
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

typedef enum{
	DEBUT,
	ARRET,
	NO
}MenuDetection;

typedef struct{
	SDL_Texture *background;
	Button **button;
}Menu;

Menu *menu_create(SDL_Renderer *render);

MenuDetection menu_execute(Menu *menu);

void menu_destroy(Menu *menu);

MenuDetection menu_detection(Menu *menu, int x, int y);



#endif
