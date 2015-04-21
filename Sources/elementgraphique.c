#include "elementgraphique.h"

ElementGraphique* elementgraphique_create(SDL_Renderer* rendu, TypeElement type, int x, int y, int w, int h){
	if(type==PIC_GLACE){
		return creerPicGlace(rendu, x, y, w, h);
	}
	return NULL;
}

static ElementGraphique* creerPicGlace(SDL_Renderer* rendu, int x,int y,int w,int h){
	ElementGraphique *picGlace= malloc(sizeof(ElementGraphique));	
	picGlace->rendu=rendu;
	picGlace->type=PIC_GLACE;
	picGlace->texture=IMG_LoadTexture(rendu, "img/ice3.png");
	picGlace->position.x=x;
	picGlace->position.y=y;
	picGlace->position.w=w;
	picGlace->position.h=h;
	return picGlace;
}
