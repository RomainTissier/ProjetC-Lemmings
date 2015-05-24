#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "graphiccomponent.h"

/* Enumération of collision direction*/
typedef enum{
	NONE,
	POINT,
	UPDOWN,
	LEFTRIGHT,
	INCLUT,
	SEMIINCLUT
}CollisionDirection;

/* Function detecting a collision between a cursor and a box */
CollisionDirection collisionDetectionCursorRect(int cursor_x,int cursor_y, SDL_Rect zone);

/* Function detecting a collision between two box*/
CollisionDirection collisionDetectionRectRect(SDL_Rect zone1,SDL_Rect zone2);

CollisionDirection collisionInside(SDL_Rect zone1, SDL_Rect zone2);

#endif