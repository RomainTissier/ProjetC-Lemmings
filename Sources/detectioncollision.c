#include "detectioncollision.h"

Collision detecterCollisionCurseurElementGraphique(int curseur_x,int curseur_y, ElementGraphique elementGraphique){
	return detecterCollisionCurseurRect(curseur_x,curseur_y,elementGraphique.position);
}

Collision detecterCollisionCurseurRect(int curseur_x,int curseur_y,SDL_Rect zone){
	if (curseur_x >= zone.x && curseur_x < zone.x + zone.w && curseur_y >= zone.y && curseur_y < zone.y + zone.h)
		return POINT;
   	else
       		return AUCUNE;
}

Collision detecterCollisionElementGraphiqueElementGraphique(ElementGraphique *e1,ElementGraphique *e2){
	return detecterCollisionRectRect(&(e1->position), &(e2->position));
}

Collision detecterCollisionRectRect(SDL_Rect *zone1,SDL_Rect *zone2){
	/* On regarde si le rectangle est trop à droite, trop à gauche, trop en bas ou trop haut pour qu'il y ait collision*/
	printf("On cherche à détecter:\n");
	printf("\tx:%d y:%d w:%d h:%d\n",zone1->x,zone1->y,zone1->w,zone1->h);
	printf("\tx:%d y:%d w:%d h:%d\n",zone2->x,zone2->y,zone2->w,zone2->h);
	if((zone2->x >= zone1->x + zone1->w)|| (zone2->x + zone2->w <= zone1->x)|| (zone2->y >= zone1->y + zone1->h)|| (zone2->y + zone2->h <= zone1->y))
        	{printf("Aucune  colision détectée!\n");return AUCUNE;}
   	else
        	if((zone2->x < zone1->x + zone1->w) && (zone2->x + zone2->w > zone1->x) && (zone2->y <= zone1->y + zone1->h -1) && (zone2->y + zone2->h >= zone1->y))
            		{printf("Colision Horizontale! détectée\n");return HORIZONTALE;}
        	else if((zone2->y < zone1->y + zone1->h) && (zone2->y + zone2->h > zone1->y) && (zone2->x <= zone1->x + zone1->w -1) && (zone2->x + zone2->w >= zone1->x))
        		{printf("Colision verticale détectée\n");return VERTICALE;}
}
