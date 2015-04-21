#ifndef DETECTIONCOLLISION_H
#define DETECTIONCOLLISION_H

#include "elementgraphique.h"

/* Enumération déterminant le type de collision*/
typedef enum{
	AUCUNE,
	POINT,
	HORIZONTALE,
	VERTICALE
}Collision;

/* Fonction permettant de détecter une collision entre un curseur et un rectangle */
Collision detecterCollisionCurseurRect(int curseur_x,int curseur_y,SDL_Rect zone);

/* Fonction permettant de détecter une collision entre deux boites*/
Collision detecterCollisionRectRect(SDL_Rect zone1,SDL_Rect zone2);

#endif
