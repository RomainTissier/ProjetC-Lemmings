#ifndef DETECTIONCOLLISION_H
#define DETECTIONCOLLISION_H

#include "elementgraphique.h"

typedef enum{
	AUCUNE,
	POINT,
	HORIZONTALE,
	VERTICALE
}Collision;

Collision detecterCollisionCurseurRect(int curseur_x,int curseur_y,SDL_Rect zone);

Collision detecterCollisionCurseurElementGraphique(int curseur_x,int curseur_y, ElementGraphique elementGraphique);

Collision detecterCollisionRectRect(SDL_Rect *zone1,SDL_Rect * zone2);

#endif
