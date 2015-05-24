#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef enum {
	FLOATER,
	MINER,
	BASHER,
	BLOCKER,
	BOMBER,
	BRIDGER,
	CLIMBER,
	DIGGER,
	PAUSE,
	LEVELS,
	QUIT,
	REESSAYER,
	CONTINUER,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	NOBUTTON
} ButtonType;

typedef struct {
	SDL_Rect position;
	SDL_Texture *background;
	ButtonType type;
	unsigned char STATE;
} Button;

Button * button_create(SDL_Renderer *render, ButtonType type, int x, int y,
		int w, int h);

Button * button_updateState(Button button);

void button_destroy(Button *b);
#endif
