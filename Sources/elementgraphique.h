#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
typedef enum{
	TERRE,
	EAU,
	PIC_GLACE
}TypeElement;

typedef struct elementgraphique{
	SDL_Renderer *rendu;
	SDL_Rect position;
	SDL_Rect sprite;
	SDL_Texture *texture;
	int demolissable;
	TypeElement type;
}ElementGraphique;

static ElementGraphique* creerPicGlace(SDL_Renderer* rendu,int x,int y,int w, int h);

ElementGraphique* elementgraphique_create(SDL_Renderer* rendu, TypeElement type, int x, int y, int w, int h);
