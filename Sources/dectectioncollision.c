#include "detectioncollision.h"

/*Structure de la boite qui est quasiment identique à SDL_Rect*/
struct AABB{
  int x;
  int y;
  int w;
  int h;
};

typedef int bool;
#define true 1
#define false 0

/*Gestion de la collision entre une boite est un curseur*/
bool Collision(int curseur_x,int curseur_y,AABB box)
{
   if (curseur_x >= box.x
    && curseur_x < box.x + box.w
    && curseur_y >= box.y
    && curseur_y < box.y + box.h)
       return true;
   else
       return false;
}

/*Gestion de la collision entre deux boites*/
bool Collision(AABB box1,AABB box2)
{
   if((box2.x >= box1.x + box1.w)   // trop à droite
    || (box2.x + box2.w <= box1.x)  // trop à gauche
    || (box2.y >= box1.y + box1.h)  // trop en bas
    || (box2.y + box2.h <= box1.y)) // trop en haut
          return false;
   else
          return true;
}
