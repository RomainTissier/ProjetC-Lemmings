#include "pinguin.h"

/*Permet de créer et d'initialiser un pinguin*/
Pinguin* pinguin_create(SDL_Renderer* r){
	Pinguin *pinguin=malloc(sizeof(Pinguin));
	pinguin->rendu=r;
	pinguin->texture=IMG_LoadTexture(r, "img/walker.png");
	pinguin->spriteCourant.x=0;
	pinguin->spriteCourant.y=32;
	pinguin->spriteCourant.h=32;
	pinguin->spriteCourant.w=32;
	pinguin->position.x=0;
	pinguin->position.y=0;
	pinguin->position.w=32;
	pinguin->position.h=32;
	return pinguin;
}

/*Permet au sprite du pinguin de changer de sens*/
void pinguin_changerSens(Pinguin* pinguin){
	if(pinguin->spriteCourant.y==0)
		pinguin->spriteCourant.y=32;
	else
		pinguin->spriteCourant.y=0;
	pinguin->spriteCourant.x=0;
}

/*Actualise la position et le sprite du pinguin*/
void pinguin_actualiser(Pinguin* pinguin){
	pinguin->spriteCourant.x+=32;
	if(pinguin->spriteCourant.x==256)
		pinguin->spriteCourant.x=0;
	if(pinguin->spriteCourant.y==0)
		pinguin->position.x-=4;
	else
		pinguin->position.x+=4;
}
