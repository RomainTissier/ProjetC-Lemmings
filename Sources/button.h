/**
 * button.h :
 *		Creation and management of the game buttons
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*Button type enumeration*/
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
	RETRY,
	QUIT,
	LEVEL1,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	RETURN,
	GOAL,
	GOAL1,
	GOAL2,
	GOAL3,
	GOAL4,
	GOAL5,
	GOAL6,
	GOAL7,
	GOAL8,
	GOAL9,
	GOAL10
} ButtonType;

/*Button structure*/
typedef struct {
	SDL_Rect position;
	SDL_Texture *background;
	ButtonType type;
} Button;

/*Function creating a button*/
Button * button_create(SDL_Renderer *render, ButtonType type, int x, int y,
		int w, int h);

/*Function freeing a button*/
void button_destroy(Button *b);

#endif
