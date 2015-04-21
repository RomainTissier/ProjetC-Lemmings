#include "detectioncollision.h"

/* Fonction permmettant de détecter une collision entre un curseur et un rectangle */
Collision detecterCollisionCurseurRect(int curseur_x,int curseur_y,SDL_Rect zone){
	if (curseur_x >= zone.x && curseur_x < zone.x + zone.w && curseur_y >= zone.y && curseur_y < zone.y + zone.h)
		return POINT;
   	else
       		return AUCUNE;
}

/* Fonction permettant de détecter une collision entre deux boites*/
Collision detecterCollisionRectRect(SDL_Rect zone1,SDL_Rect zone2){
	/* On regarde si le rectangle est trop à droite, trop à gauche, trop en bas ou trop haut pour qu'il y ait collision*/
	if((zone2.x >= zone1.x + zone1.w)|| (zone2.x + zone2.w <= zone1.x)|| (zone2.y >= zone1.y + zone1.h)|| (zone2.y + zone2.h <= zone1.y))
        	return AUCUNE;
   	else
        	if((zone2.x < zone1.x + zone1.w) && (zone2.x + zone2.w > zone1.x) && (zone2.y <= zone1.y + zone1.h -1) && (zone2.y + zone2.h >= zone1.y))
            		return HORIZONTALE;
        	else if((zone2.y < zone1.y + zone1.h) && (zone2.y + zone2.h > zone1.y) && (zone2.x <= zone1.x + zone1.w -1) && (zone2.x + zone2.w >= zone1.x))
        		return VERTICALE;
}
