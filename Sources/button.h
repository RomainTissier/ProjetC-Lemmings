#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//TODO: supprimmer image inutilisée dans IMG et renommer correctement les autres
//TODO: commenter !
typedef enum {
	FLOATER,
	BASHER,
	BLOCKER,
	BOMBER,
	BRIDGER,
	DIGGER,
	PAUSE,
	LEVELS,
	CONTINUE,
	RETURN,
	RETURNLEVEL,
	RETRY,
	QUIT,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6
} ButtonType;

typedef struct {
	SDL_Rect position;
	SDL_Texture *background;
	ButtonType type;
} Button;

Button * button_create(SDL_Renderer *render, ButtonType type, int x, int y,
		int w, int h);

Button * button_updateState(Button button);

void button_destroy(Button *b);

#endif
