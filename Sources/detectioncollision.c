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
	printf("On cherche à détecter:\n");
	printf("\tx:%d y:%d w:%d h:%d\n",zone1.x,zone1.y,zone1.w,zone1.h);
	printf("\tx:%d y:%d w:%d h:%d\n",zone2.x,zone2.y,zone2.w,zone2.h);
	if((zone2.x >= zone1.x + zone1.w)|| (zone2.x + zone2.w <= zone1.x)|| (zone2.y >= zone1.y + zone1.h)|| (zone2.y + zone2.h <= zone1.y))
        	{printf("aucune collision\n");return AUCUNE;}
   	else
		//Collision verticale droite
<<<<<<< HEAD
		if (zone2.x + zone2.w > zone1.x + zone1.w + zone1.h)
 			{printf("verticale droite\n");return VERTICALE;}
		//Collision verticale gauche
		else if (zone2.x < zone1.x)
=======
		if (zone2.x + zone2.w >= zone1.x + zone1.w + zone1.h)
 			{printf("verticale droite\n");return VERTICALE;}
		//Collision verticale gauche
		else if (zone2.x <= zone1.x)
>>>>>>> master
			{printf("verticale gauche\n");return VERTICALE;}
		//Collision horizontale bas
 		else if (zone2.y + zone2.h > zone1.y + zone1.h + zone1.w)
			{printf("horizontale bas\n");return HORIZONTALE;}
		//Collision horizontale haut
		else if (zone2.y < zone1.y)
			{printf("horizontale haut\n");return HORIZONTALE;}
<<<<<<< HEAD
}
=======
 	
	}
	

>>>>>>> master
