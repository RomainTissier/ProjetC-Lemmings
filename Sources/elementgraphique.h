#include<SDL2/SDL.h>

typedef struct elementgraphique{
	SDL_Renderer *rendu;
	SDL_Rect *position;
	SDL_Rect *sprite;
	SDL_Texture *texture;
	int demolissable;
}ElementGraphique;
