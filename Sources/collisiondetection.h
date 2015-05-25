/**
 * collisiondetection.h :
 *		Management of the collision between the cursor and a box or two boxes
 * Authors :
 * 		Delpech Marc
 * 		Levy Yoni
 * 		Rousselle Matthieu
 * 		Tissier Romain
 */

#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include "graphiccomponent.h"

/* Collision direction enumeration*/
typedef enum {
	NONE, POINT, UPDOWN, LEFTRIGHT, INCLUT
} CollisionDirection;

/* Function detecting collision between a cursor and a box */
CollisionDirection collisionDetectionCursorRect(int cursor_x, int cursor_y,
		SDL_Rect zone);

/* Function detecting collision between two boxes*/
CollisionDirection collisionDetectionRectRect(SDL_Rect zone1, SDL_Rect zone2);

/*Function detecting if a penguin is inside a box*/
CollisionDirection collisionInside(SDL_Rect zone1, SDL_Rect zone2);

#endif
