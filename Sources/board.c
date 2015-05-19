#include "board.h"
#include "collisiondetection.h"
#include "render.h"

#define NBBTN 9

//static const int nbBtn=2;


/*Function creating a board*/
Board* board_create(SDL_Renderer *render, char level[]){
	Board *board=malloc(sizeof(Board));
	board->render=render;
	board->background=IMG_LoadTexture(board->render, "img/background.jpg");
	board->speed=1;
	board->moment=10;	
	board_createPanel(board);	
	board->idS=-1;

	/*Loading graphic component from a configuration file*/
	FILE *file=fopen(level, "r");	
	if (file!=NULL){
		board->nbGraphics=0;
		char string[100];
		char typeName[15];
		fgets(string,100,file);
		sscanf(string, "%s %d",typeName, &(board->nbPinguins));
		board->nbPinguinsAlive=board->nbPinguins;
		while(fgets(string,100,file)!=NULL){
			int type,arg1,arg2,arg3,arg4;
			sscanf(string, "%s %d %d %d %d", typeName, &arg1, &arg2, &arg3 , &arg4);
			board->graphics=realloc(board->graphics,(board->nbGraphics+1)*sizeof(GraphicComponent*));
			if(!strcmp(typeName,"ICE_PEAK"))
				type=ICE_PEAK;
			else if(!strcmp(typeName, "STONE_FLOOR"))
				type=STONE_FLOOR;
			else if(!strcmp(typeName, "STONE_WALL"))
				type=STONE_WALL;
			else if(!strcmp(typeName, "FLOOR"))
				type=FLOOR;
			else if(!strcmp(typeName, "WALL"))
				type=WALL;
			else if(!strcmp(typeName, "WATER"))
				type=WATER;
			else if(!strcmp(typeName, "DECO"))
				type=DECO;
			else if(!strcmp(typeName, "ENTRY"))
				type=ENTRY;
			else if(!strcmp(typeName, "EXIT"))
				type=EXIT;
			board->graphics[board->nbGraphics]=graphicComponent_create(render, type, arg1, arg2, arg3, arg4);
			board->nbGraphics++;
		}
		fclose(file);
	}else return NULL;

/*Loading pinguins  TODO: several pinguins*/
	//board->nbPinguins=1;
	board->pinguins=malloc(board->nbPinguins*sizeof(Pinguin*));

	int i;
	for(i=0;i<board->nbPinguins;i++){
		board->pinguins[i]=pinguin_create(render);
		board->pinguins[i]->position.x=board->graphics[0]->position.x+10;
		board->pinguins[i]->position.y=board->graphics[0]->position.y+10;
	}
	return board;
}

void board_addRect(Board *board, SDL_Rect r){
	board->graphics=realloc(board->graphics,(board->nbGraphics+1)*sizeof(GraphicComponent*));	
	board->graphics[board->nbGraphics]=graphicComponent_create(board->render, TRANS, r.x-2, r.y-2, r.w+2, r.h+2);
	board->nbGraphics++;
}

/*Function freeing memory*/
void board_destroy(Board * board){
	int i;
	for(i=0;i<board->nbPinguins;i++)
		pinguin_destroy(board->pinguins[i]);
	for(i=0;i<board->nbGraphics;i++)
		graphicComponent_destroy(board->graphics[i]);
	free(board->pinguins);
	free(board->graphics);
	free(board);
}

/*Function refreshing board's display. TODO: rendering using part of display*/
void board_refresh(Board *board){
	SDL_RenderCopy(board->render,board->background,NULL,NULL);
	int i;
	for(i=0;i<board->nbGraphics;i++)
		SDL_RenderCopy(board->render, board->graphics[i]->texture, NULL,&(board->graphics[i]->position));
	for(i=0;i<board->nbPinguins && (i<board->moment/20);i++)
		SDL_RenderCopy(board->render,board->pinguins[i]->texture, &(board->pinguins[i]->sprite), &(board->pinguins[i]->position));
	for(i=0;i<NBBTN;i++)
		SDL_RenderCopy(board->render, board->panel[i]->background, NULL,&(board->panel[i]->position));
}

/*Function computing component's position*/
void board_computePosition(Board *board){
	int i;
	for(i=0; i<board->nbPinguins && (i< board->moment/20);i++)
		pinguin_computePosition(board->pinguins[i]);	
	if(board->moment/20<board->nbPinguins)
	board->moment++;
	int nbS=0,nbM=0;
	for(i=0;i<board->nbPinguins;i++){
		if(board->pinguins[i]->state==SAVE)
			nbS++;
		else if (board->pinguins[i]->state==DEAD)
			nbM++;
	}
	if(nbS+nbM==board->nbPinguins ){
		quit=1;
	}
}

/*Function managing board's collision*/
void board_manageCollision(Board *board){
	int ig,ip;
	State nouvelEtat;
	for(ip=0;ip<board->nbPinguins;ip++){


		if(board->pinguins[ip]->state!=EXITING && board->pinguins[ip]->state!=SAVE && board->pinguins[ip]->state!=DEAD && board->pinguins[ip]->state!=KILLING){
		nouvelEtat=FALLING;
		for(ig=0;ig<board->nbGraphics;ig++){
			unsigned char breakTest=0;
			if(board->graphics[ig]->collision){
				switch(collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position)){
					case LEFTRIGHT : 
					if(ip==0) printf("colisionLEFRIGHT\n");
					if(board->graphics[ig]->type!=TRANS && board->pinguins[ip]->state==WALKING){
					printf("retournepinguin\n");
					pinguin_switchDirection(board->pinguins[ip]);
					}else nouvelEtat=board->pinguins[ip]->previousState;
					break;
					case UPDOWN : 
					if(ip==0) printf("colisionUPDOWN\n");
					if(board->graphics[ig]->type!=TRANS)nouvelEtat=WALKING; break;
					case INCLUT :
				//TODO: si on est INCLUT MAIS QUE L'on est pas inclu dans un vert	
					if(board->pinguins[ip]->previousState==DIGGING && board->graphics[ig]->type!=TRANS) 
					printf("Inclusion détectée\n");
					if(board->graphics[ig]->type==TRANS && board->pinguins[ip]->state!=DIGGING){nouvelEtat=FALLING; breakTest=1;} else if(board->pinguins[ip]->state==DIGGING && board->graphics[ig]->type!=TRANS ){
					printf("On valide la condiftion\n");
					nouvelEtat=DIGGING; 
					breakTest=1;
					} else nouvelEtat=board->pinguins[ip]->previousState;
					break;
				}
			}		
			if(breakTest)
				break;

		}
		if(board->pinguins[ip]->state==DIGGING){
			if(nouvelEtat==FALLING)
			{
			printf("On passe en chute libre\n");
				board->pinguins[ip]->state=FALLING;
			}
			else
				board_addRect(board,board->pinguins[ip]->position);	
		}else if(board->pinguins[ip]->state==FLOATING && nouvelEtat==WALKING){
			board->pinguins[ip]->state=WALKING;
		}else if(board->pinguins[ip]->state!=FLOATING){
			board->pinguins[ip]->state=nouvelEtat;	
		}
		if(collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2-10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT && collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2+10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT){

			board->pinguins[ip]->state=EXITING;
		}
		}
	}
/*
	int ig,ip;
	for(ip=0;ip<board->nbPinguins;ip++){
		if(board->pinguins[ip]->state!=EXITING && board->pinguins[ip]->state!=SAVE && board->pinguins[ip]->state!=DEAD && board->pinguins[ip]->state!=KILLING){
		int fallingTest=1;
		int fallingRectTest=0;
		int inclutest=0;
		for(ig=0;ig<board->nbGraphics;ig++){
			if(board->graphics[ig]->collision){
				switch(collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position)){
					case LEFTRIGHT : pinguin_switchDirection(board->pinguins[ip]); break;
					case UPDOWN : fallingTest=0; break;
					case INCLUT : fallingTest=0; inclutest=1;board->pinguins[ip]->state=DIGGING;
					break;
				}
			}
			if(board->graphics[ig]->type==TRANS){
				printf("On rentre dans la trans\n");
				if(collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position)==INCLUT && board->pinguins[ip]->previousState!=DIGGING ){
					fallingRectTest=1;
				}
			}
			
		}

		if(board->pinguins[ip]->state!=FLOATING && board->pinguins[ip]->state!=DIGGING && fallingRectTest==0 &&inclutest==0){
			board->pinguins[ip]->state=(fallingTest)?FALLING:WALKING;	
		}else if(board->pinguins[ip]->state!=FLOATING && board->pinguins[ip]->state!=DIGGING && fallingRectTest==1){
			board->pinguins[ip]->state=FALLING;
		}
		else if(fallingTest==0 && board->pinguins[ip]->state!=DIGGING) board->pinguins[ip]->state=WALKING;
		else if(board->pinguins[ip]->state==DIGGING && fallingTest==1)
			board->pinguins[ip]->state=FALLING;
		else {
			board_addRect(board,board->pinguins[ip]->position);
		}
		if(collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2-10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT && collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2+10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT){

			board->pinguins[ip]->state=EXITING;
		}
		}
	}*/
}
static void board_createPanel(Board *board){
	board->panel=malloc(sizeof(Button*)*NBBTN);
	board->panel[0]=button_create(board->render,PAUSE,10,520,50,70);
	board->panel[1]=button_create(board->render,FLOATER,60,520,50,70);
	board->panel[2]=button_create(board->render,MINER,110,520,50,70);
	board->panel[3]=button_create(board->render,BASHER,160,520,50,70);
	board->panel[4]=button_create(board->render,BLOCKER,210,520,50,70);
	board->panel[5]=button_create(board->render,BOMBER,260,520,50,70);
	board->panel[6]=button_create(board->render,BRIDGER,310,520,50,70);
	board->panel[7]=button_create(board->render,CLIMBER,360,520,50,70);
	board->panel[8]=button_create(board->render,DIGGER,410,520,50,70);
}

void board_manageEvent(Board *board,int x, int y){
	if(collisionDetectionCursorRect(x,y,board->panel[0]->position)==POINT){
		board->pause=!board->pause;
	}else if(collisionDetectionCursorRect(x,y,board->panel[1]->position)==POINT){
		board->idS=FLOATER;
	}else if(collisionDetectionCursorRect(x,y,board->panel[8]->position)==POINT){
		board->idS=DIGGER;
	}else if(board->idS!=-1){
		int test=0,i;
		for(i=0;i<board->nbPinguins;i++){
			if(board->pinguins[i]->state==FALLING && collisionDetectionCursorRect(x,y,board->pinguins[i]->position)==POINT)
			{ board->pinguins[i]->state=FLOATING;}
if(collisionDetectionCursorRect(x,y,board->pinguins[i]->position)==POINT && board->idS==DIGGER)
			{board->pinguins[i]->state=DIGGING;}
		}
	}
}
