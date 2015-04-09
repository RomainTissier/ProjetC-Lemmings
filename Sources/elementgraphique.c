#include "elementgraphique.h"

ElementGraphique* elementgraphique_create(SDL_Renderer* rendu, TypeElement type){
	if(type==PIC_GLACE){
		return creerPicGlace(rendu);
	}
	return NULL;
}

static ElementGraphique* creerPicGlace(SDL_Renderer* rendu){
	ElementGraphique *picGlace= malloc(sizeof(ElementGraphique));	
	picGlace->rendu=rendu;
	picGlace->type=PIC_GLACE;
	picGlace->texture=IMG_LoadTexture(rendu, "img/ice3.png");
	picGlace->position.x=100;
	picGlace->position.y=0;
	picGlace->position.w=10;
	picGlace->position.h=32;
	return picGlace;
}
