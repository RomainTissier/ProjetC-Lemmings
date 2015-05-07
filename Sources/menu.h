#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "button.h"
#include "collisiondetection.h"

typedef enum{
	STARTMENU,
	PAUSEMENU
}TypeMenu;

typedef enum{
	DEBUT,
	ARRET
}MenuDetection;

typedef struct{
	SDL_Texture *background;
	Button **button;
}Menu;

Menu *menu_create(SDL_Renderer *render, TypeMenu type);

MenuDetection menu_detection(Menu *menu, int x, int y);



#endif
