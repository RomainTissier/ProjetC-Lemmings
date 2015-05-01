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
	printf("On cherche à détecter:\n");
	printf("\tx:%d y:%d w:%d h:%d\n",zone1.x,zone1.y,zone1.w,zone1.h);
	printf("\tx:%d y:%d w:%d h:%d\n",zone2.x,zone2.y,zone2.w,zone2.h);

	if (zone2.y + zone2.h >= zone1.y && zone2.y + zone2.h/2 <= zone1.y)
	{
		//Collision avec le sol
		if ((zone2.x >= zone1.x && zone2.x <= zone1.x + zone1.w) || (zone2.x +zone2.w >= zone1.x && zone2.x + zone2.w <= zone1.x + zone1.w))
		{
			printf("collision en bas");
			return HAUTBAS;
		}
	} else if (zone2.x + zone2.w == zone1.x)
	{
		//Collision avec un obstacle a droite
		if ((zone2.y >= zone1.y && zone2.y <= zone1.y + zone1.h) || (zone2.y +zone2.h >= zone1.y && zone2.y + zone2.h <= zone1.y + zone1.h))
		{
			printf("collision a droite");
			return GAUCHEDROITE;
		}
	} else if (zone2.x == zone1.x + zone1.w)
	{
		//Collision avec un obstacle a gauche
		if ((zone2.y >= zone1.y && zone2.y <= zone1.y + zone1.h) || (zone2.y +zone2.h >= zone1.y && zone2.y + zone2.h <= zone1.y + zone1.h))
		{
			printf("collision a gauche");
			return HAUTBAS;
		}
	} else if (zone2.y <= zone1.y + zone1.h && zone2.y >= zone1.y + zone1.h/2)
	{
		//Collision avec le haut
		if ((zone2.x >= zone1.x && zone2.x <= zone1.x + zone1.w) || (zone2.x +zone2.w >= zone1.x && zone2.x + zone2.w <= zone1.x + zone1.w))
		{
			printf("collision en haut");
			return HAUTBAS;
		}
	} else
	{
		printf("aucune collision");
		return AUCUNE;
	}

}
