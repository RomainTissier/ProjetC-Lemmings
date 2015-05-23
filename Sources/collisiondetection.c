#include "collisiondetection.h"

/*Function detecting a collision between a cursor and a box */
CollisionDirection collisionDetectionCursorRect(int cursor_x,int cursor_y,SDL_Rect zone){
	if(cursor_x>=zone.x&&cursor_x<zone.x+zone.w&&cursor_y>=zone.y&&cursor_y<zone.y+zone.h)
		return POINT;
       	return NONE;
}

/*Function detecting a collision between two boxes*/
CollisionDirection collisionDetectionRectRect(SDL_Rect zone1,SDL_Rect zone2){
	if(collisionInside(zone1,zone2)==INCLUT)
		return INCLUT;
	if(zone2.y+zone2.h>=zone1.y&&zone2.y+zone2.h/2<=zone1.y){
		if((zone2.x>=zone1.x&&zone2.x<=zone1.x+zone1.w)||(zone2.x+zone2.w>=zone1.x&&zone2.x+zone2.w<=zone1.x+zone1.w)){
			return UPDOWN;
		}
	}else if(zone2.x+zone2.w>=zone1.x&&zone2.x+zone2.w<=zone1.x+zone1.w){
		if((zone2.y>=zone1.y&&zone2.y<=zone1.y+zone1.h)||(zone2.y+zone2.h>=zone1.y&&zone2.y+zone2.h<=zone1.y+zone1.h)){
			return LEFTRIGHT;
		}
	}else if(zone2.x<=zone1.x+zone1.w&&zone2.x>=zone1.x){
		if((zone2.y>=zone1.y&&zone2.y<=zone1.y+zone1.h)||(zone2.y+zone2.h>=zone1.y&&zone2.y+zone2.h<=zone1.y+zone1.h)){
			return LEFTRIGHT;
		}
	}
	return NONE;
}

CollisionDirection collisionInside(SDL_Rect zone1, SDL_Rect pin){
	if(pin.x>=zone1.x && pin.y>=zone1.y && pin.w+pin.x<=zone1.w+zone1.x && pin.y+pin.h<=zone1.h+zone1.y){
		return INCLUT;
	}
	/*
		//coin haut gauche
	if (zone2.x>zone1.x && zone2.x<zone1.x+zone1.w && zone2.y>zone1.y && zone2.y<zone1.y+zone1.h){
		return INCLUT;
	} //coin haut droit
	else if (zone2.x+zone2.w>zone1.x && zone2.x+zone2.w<zone1.x+zone1.w && zone2.y>zone1.y && zone2.y<zone1.y+zone1.h){
		return INCLUT;
	} //coin bas gauche
	else if (zone2.x>zone1.x && zone2.x<zone1.x+zone1.w && zone2.y+zone2.h>zone1.y && zone2.y+zone2.h<zone1.y+zone1.h){
		return INCLUT;
	} //coin bas droite
	else if (zone2.x+zone2.w>zone1.x && zone2.x+zone2.w<zone1.x+zone1.w && zone2.y+zone2.h>zone1.y && zone2.y+zone2.h<zone1.y+zone1.h){
		return INCLUT;
	}*/ else {
		return NONE;
	}
}
