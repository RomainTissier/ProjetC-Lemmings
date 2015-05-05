#include "board.h"
#include "collisiondetection.h"

/*Function creating a board*/
Board* board_create(SDL_Renderer *render, char level[]){
	Board *board=malloc(sizeof(Board));
	board->render=render;
	board->background=IMG_LoadTexture(board->render, "img/background.jpg");
	board->speed=1;
	board->moment=10;	
	board_createPanel(board);	
	/*Loading graphic component from a configuration file*/
	FILE *file=fopen(level, "r");	
	if (file!=NULL){
		board->nbGraphics=0;
		char string[100];
		char typeName[15];
		fgets(string,100,file);
		sscanf(string, "%s %d",typeName, &(board->nbPinguins));
		while(fgets(string,100,file)!=NULL){
			int type,arg1,arg2,arg3,arg4;
			sscanf(string, "%s %d %d %d %d", typeName, &arg1, &arg2, &arg3 , &arg4);
			board->graphics=realloc(board->graphics,(board->nbGraphics+1)*sizeof(GraphicComponent*));
			if(!strcmp(typeName,"ICE_PEAK"))
				type=ICE_PEAK;
			else if(!strcmp(typeName, "FLOOR"))
				type=FLOOR;
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
	for(i=0;i<1;i++)
		SDL_RenderCopy(board->render, board->panel[i]->background, NULL,&(board->panel[i]->position));
}

/*Function computing component's position*/
void board_computePosition(Board *board){
	int i;
	for(i=0; i<board->nbPinguins && (i< board->moment/20);i++)
		pinguin_computePosition(board->pinguins[i]);	
	if(board->moment/20<board->nbPinguins)
	board->moment++;
}

/*Function managing board's collision*/
void board_manageCollision(Board *board){
	int ig,ip;	
	for(ip=0;ip<board->nbPinguins;ip++){
		if(board->pinguins[ip]->state!=EXITING && board->pinguins[ip]->state!=SAVE){
		int fallingTest=1;
		for(ig=0;ig<board->nbGraphics;ig++){
			if(board->graphics[ig]->collision){
				switch(collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position)){
					case LEFTRIGHT : pinguin_switchDirection(board->pinguins[ip]); break;
					case UPDOWN : fallingTest=0; break;
				}
			}
		}
		board->pinguins[ip]->state=(fallingTest)?FALLING:WALKING;
		if(collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2-10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT && collisionDetectionCursorRect(board->graphics[1]->position.x+board->graphics[1]->position.w/2+10,board->graphics[1]->position.y+board->graphics[1]->position.h-15, board->pinguins[ip]->position)==POINT){

			board->pinguins[ip]->state=EXITING;
		}
		}
	}
}

static void board_createPanel(Board *board){
	board->panel=malloc(sizeof(Button*)*1);
	board->panel[0]=button_create(board->render,PAUSE,100,400,100,100);
}
