#include "detectioncollision.h"

/*Structure de la boite qui est quasiment identique à SDL_Rect*/
struct AABB{
  int x;
  int y;
  int w;
  int h;
};

/*Gestion de la collision entre une boite et un curseur*/
int Collision(int curseur_x,int curseur_y,AABB box)
{
   if (curseur_x >= box.x
    && curseur_x < box.x + box.w
    && curseur_y >= box.y
    && curseur_y < box.y + box.h)
       return 1; //Collision
   else
       return 0; //Pas collision
}

/*Gestion de la collision entre deux boites*/
int Collision(AABB box1,AABB box2)
{
   if((box2.x >= box1.x + box1.w)   // trop à droite
    || (box2.x + box2.w <= box1.x)  // trop à gauche
    || (box2.y >= box1.y + box1.h)  // trop en bas
    || (box2.y + box2.h <= box1.y)) // trop en haut
        return -1; //Pas de collision
   else
        if((box2.x < box1.x + box1.w)
          && (box2.x + box2.w > box1.x)
          && ((box2.y = box1.y + box1.h -1) || (box2.y + box2.h = box1.y +1)))
            return 0; //Collision horizontale
        else if((box2.y < box1.y + box1.h)
          && (box2.y + box2.h > box1.y)
          && (box2.x = box1.x + box1.w -1) || (box2.x + box2.w = box1.x +1))
            return 1; //Collision verticale
}
