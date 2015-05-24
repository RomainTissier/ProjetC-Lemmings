#include "board.h"
#include "collisiondetection.h"
#include "render.h"

#define NBBTN 9
#define ECART 40

//TODO: on ne peut pas changer d'action une fois qu'une action est engagée !=> sauf si elle se termine
//TODO: prendre en compte la sortie de orange ou vert pour stop falling et changement de sens
/*Function creating a board*/
Board* board_create(SDL_Renderer *render, char level[]) {
	printf("On passe par la\n");
	Board *board = malloc(sizeof(Board));
	board->render = render;
	board->background = IMG_LoadTexture(board->render, "img/background.jpg");
	board->speed = 1;
	board->pause = 0;
	board->moment = 10;
	//board->nbFallingBox=0;
	board_createPanel(board);
	board->idS = -1;
	board->nbGreen = 0;
	board->green = malloc(0);
	board->graphics = malloc(0);
	board->orange = malloc(0);
	/*Loading graphic component from a configuration file*/
	FILE *file = fopen(level, "r");
	if (file != NULL) {
		board->nbGraphics = 0;
		char string[100];
		char typeName[15];
		fgets(string, 100, file);
		sscanf(string, "%s %d", typeName, &(board->nbPinguins));
		board->nbPinguinsAlive = board->nbPinguins;
		while (fgets(string, 100, file) != NULL) {
			int type = 0, arg1, arg2, arg3, arg4;
			sscanf(string, "%s %d %d %d %d", typeName, &arg1, &arg2, &arg3,
					&arg4);
			board->graphics = realloc(board->graphics,
					(board->nbGraphics + 1) * sizeof(GraphicComponent*));
			if (!strcmp(typeName, "ICE_PEAK"))
				type = ICE_PEAK;
			else if (!strcmp(typeName, "STONE_FLOOR"))
				type = STONE_FLOOR;
			else if (!strcmp(typeName, "STONE_WALL"))
				type = STONE_WALL;
			else if (!strcmp(typeName, "FLOOR"))
				type = FLOOR;
			else if (!strcmp(typeName, "WALL"))
				type = WALL;
			else if (!strcmp(typeName, "WATER"))
				type = WATER;
			else if (!strcmp(typeName, "DECO"))
				type = DECO;
			else if (!strcmp(typeName, "ENTRY"))
				type = ENTRY;
			else if (!strcmp(typeName, "EXIT"))
				type = EXIT;
			board->graphics[board->nbGraphics] = graphicComponent_create(render,
					type, arg1, arg2, arg3, arg4);
			board->nbGraphics++;
		}
		fclose(file);
	} else
		return NULL;

	/*Loading pinguins  TODO: several pinguins*/
	//board->nbPinguins=1;
	board->pinguins = malloc(board->nbPinguins * sizeof(Pinguin*));

	int i;
	for (i = 0; i < board->nbPinguins; i++) {
		board->pinguins[i] = pinguin_create(render);
		board->pinguins[i]->position.x = board->graphics[0]->position.x + 10;
		board->pinguins[i]->position.y = board->graphics[0]->position.y + 10;
	}
	return board;
}

void board_addRect(Board *board, SDL_Rect r) {
	board->green = realloc(board->green,
			(board->nbGreen + 1) * sizeof(GraphicComponent*));
	//TODO: tester avec des coordonnées PILE POIL
	board->green[board->nbGreen] = graphicComponent_create(board->render, TRANS,
			r.x - 2, r.y - 2, r.w + 2, r.h + 2);
	board->nbGreen++;
}
//TODO: mamailler le sprite si on ne l'lannime pas
void board_addStop(Board *board, SDL_Rect r) {
	board->graphics = realloc(board->graphics,
			(board->nbGraphics + 1) * sizeof(GraphicComponent*));
	board->graphics[board->nbGraphics] = graphicComponent_create(board->render, STOPP,
			r.x-1, r.y-2, r.w+2, r.h+1);
	board->nbGraphics++;
}

//TODO: optimiser les fonctions add en une seule
void board_addBrick(Board *board, SDL_Rect r) {
	board->graphics = realloc(board->graphics,
			(board->nbGraphics + 1) * sizeof(GraphicComponent*));
	board->graphics[board->nbGraphics] = graphicComponent_create(board->render, BRIDGEPART,
			r.x+r.w/2, r.y+r.h-1, r.w/2+1, 20);
	board->nbGraphics++;
}

//TODO: ajout menu automatique
void board_addOrange(Board *board, SDL_Rect r) {
	board->orange = realloc(board->orange,
			(board->nbOrange + 1) * sizeof(GraphicComponent*));
	board->orange[board->nbOrange] = graphicComponent_create(board->render,
			ORANGE, r.x - 2, r.y - 2, r.w + 2, r.h + 2);
	board->nbOrange++;
}

/*Function freeing memory*/
void board_destroy(Board * board) {
	int i;
	for (i = 0; i < board->nbPinguins; i++)
		pinguin_destroy(board->pinguins[i]);
	for (i = 0; i < board->nbGraphics; i++)
		graphicComponent_destroy(board->graphics[i]);
	free(board->pinguins);
	free(board->graphics);
	free(board);
}

/*Function refreshing board's display. TODO: rendering using part of display*/
void board_refresh(Board *board) {
	SDL_RenderCopy(board->render, board->background, NULL, NULL);
	int i;
	for (i = 0; i < board->nbGraphics; i++)
		SDL_RenderCopy(board->render, board->graphics[i]->texture, NULL,
				&(board->graphics[i]->position));

	for (i = 0; i < board->nbOrange; i++)
		SDL_RenderCopy(board->render, board->orange[i]->texture, NULL,
				&(board->orange[i]->position));

	for (i = 0; i < board->nbGreen; i++)
		SDL_RenderCopy(board->render, board->green[i]->texture, NULL,
				&(board->green[i]->position));

	for (i = 0; i < board->nbPinguins && (i < board->moment / ECART); i++)
		SDL_RenderCopy(board->render, board->pinguins[i]->texture,
				&(board->pinguins[i]->sprite), &(board->pinguins[i]->position));
	for (i = 0; i < NBBTN; i++)
		SDL_RenderCopy(board->render, board->panel[i]->background, NULL,
				&(board->panel[i]->position));

}

//TODO : merger green et orange

/*Function computing component's position*/
int board_computePosition(Board *board) {
	int i;
	for (i = 0; i < board->nbPinguins && (i < board->moment / ECART); i++)
		pinguin_computePosition(board->pinguins[i]);
	if (board->moment / ECART < board->nbPinguins)
		board->moment++;
	int nbS = 0, nbM = 0;
	for (i = 0; i < board->nbPinguins; i++) {
		if (board->pinguins[i]->state == SAVE)
			nbS++;
		else if (board->pinguins[i]->state == DEAD)
			nbM++;
	}
	if (nbS + nbM == board->nbPinguins) {
		return 1;
	}
	return 0;
}

/*Function managing board's collision*/
void board_manageCollision(Board *board) {
	/*	int ig,ip,ifb;
	 for(ip=0;ip<board->nbPinguins;ip++){
	 if(board->pinguins[ip]->state!=EXITING && board->pinguins[ip]->state!=SAVE && board->pinguins[ip]->state!=DEAD && board->pinguins[ip]->state!=KILLING){
	 Collision graphicColision=NONE;
	 Collision fallingBoxColision=NONE;
	 for(ig=0;ig<board->nbGraphics;ig++){
	 unsigned char breakTest=0;
	 if(board->graphics[ig]->collision){
	 graphicColision=collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position);
	 if(graphicColision!=NONE)
	 breakTest=1;
	 }
	 if(breakTest)
	 break;

	 }
	 for(ifb=0;ifb<nbFallingBox;ifb++){
	 if(board->fallingBox)
	 fallingBoxColision=collisionDetectionRectRect(board->graphics[ig]->position,board->pinguins[ip]->position);
	 }
	 if(board->pinguins[ip]->state==DIGGING){
	 if(nouvelEtat==FALLING){
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
	 }*/

	//TODO: prise en compte de la noyade
	//TODO: prise en compte du prob de DESTRUCTABILITE
	CollisionDirection nouvelEtatGraphic;
	int ip;
	for (ip = 0; ip < board->nbPinguins; ip++) {
		if (board->pinguins[ip]->state != EXITING
				&& board->pinguins[ip]->state != SAVE
				&& board->pinguins[ip]->state != DEAD
				&& board->pinguins[ip]->state != KILLING) {
			nouvelEtatGraphic = NONE;
			int ig;
			for (ig = 0; ig < board->nbGraphics; ig++) {
				//unsigned char breakTest = 0;
				int breakTest = 0;
				if (board->graphics[ig]->collision) {
					int nc = collisionDetectionRectRect(
							board->graphics[ig]->position,
							board->pinguins[ip]->position);
					if (nc != NONE) {
						if (nc == LEFTRIGHT && nouvelEtatGraphic != INCLUT) {
							nouvelEtatGraphic = LEFTRIGHT;
						}
						if (nc == UPDOWN && nouvelEtatGraphic == NONE) {
							nouvelEtatGraphic = UPDOWN;
						}
						if (nc == INCLUT)
							nouvelEtatGraphic = INCLUT;
					}
				}
				if (breakTest)
					break;
			}
			CollisionDirection nouvelEtatGreen = NONE;
			int iv;
			for (iv = 0; iv < board->nbGreen; iv++) {
				CollisionDirection nv = collisionDetectionRectRect(
						board->green[iv]->position,
						board->pinguins[ip]->position);
				if (nv == LEFTRIGHT && nouvelEtatGreen == NONE)
					nouvelEtatGreen = LEFTRIGHT;
				if (nv == UPDOWN && nouvelEtatGreen == NONE)
					nouvelEtatGreen = UPDOWN;
				if (nv == INCLUT)
					nouvelEtatGreen = INCLUT;

			}
			int io;
			CollisionDirection nouvelEtatIO = NONE;
			for(io=0;io<board->nbOrange;io++) {
				CollisionDirection nv = collisionDetectionRectRect(
										board->orange[io]->position,
										board->pinguins[ip]->position);
								if (nv == LEFTRIGHT && nouvelEtatIO == NONE)
									nouvelEtatIO = LEFTRIGHT;
								if (nv == UPDOWN && nouvelEtatIO == NONE)
									nouvelEtatIO = UPDOWN;
								if (nv == INCLUT)
									nouvelEtatIO = INCLUT;
			}
			if (board->pinguins[ip]->state == FLOATING
					&& nouvelEtatGraphic != UPDOWN) {
				//board->pinguins[ip]->state==UPDOWN;
			}else if(board->pinguins[ip]->state==BRIDGING){
				if(board->pinguins[ip]->sprite.x>=256 && board->pinguins[ip]->sprite.x<=288)
				board_addBrick(board,board->pinguins[ip]->position);
			}else if(board->pinguins[ip]->state==BOOMING){
//TODO : detection des hautbas pour creuser en L
				//TODO : marche pinguin dans les deux sens inclusion classe;
				if(board->pinguins[ip]->sprite.x>=256){
					int ip2;
					for(ip2=0;ip2<board->nbPinguins;ip2++){
						if(board->pinguins[ip2]->state!=DEAD && collisionDetectionRectRect(
													board->pinguins[ip]->position,
													board->pinguins[ip2]->position)!=NONE){
							board->pinguins[ip2]->state=KILLING;
						}
					}
					board_addRect(board,board->pinguins[ip]->position);
				}
			} else if (board->pinguins[ip]->state == DIGGING) { //TODO: PRECONDITION : etre INCLU sinon test en boucle!
				printf("Position actuelle: x:%d, y:%d,w:%d,h:%d\n",
						board->pinguins[ip]->position.x,
						board->pinguins[ip]->position.y,
						board->pinguins[ip]->position.w,
						board->pinguins[ip]->position.h);
				if (nouvelEtatGraphic == INCLUT)
					printf("nouvelEtatGraphic=INCLUT\n");
				if (nouvelEtatGraphic == NONE)
					printf("nouvelEtatGraphic=NONE\n");
				if (nouvelEtatGraphic == LEFTRIGHT)
					printf("nouvelEtatGraphic=LEFTRIGHT\n");
				if (nouvelEtatGraphic == UPDOWN)
					printf("nouvelEtatGraphic=UPDOWN\n");
				board_addRect(board, board->pinguins[ip]->position);
				if (nouvelEtatGraphic == LEFTRIGHT
						&& board->pinguins[ip]->previousColision == INCLUT)
					board->pinguins[ip]->state = FALLING;
			} else if (board->pinguins[ip]->state == BASHING) {
				//ON BASH
				//TODO: précond: être INCLUT
				board_addOrange(board, board->pinguins[ip]->position);
				if (board->pinguins[ip]->previousColision == INCLUT
						&& nouvelEtatGraphic == LEFTRIGHT)
					board->pinguins[ip]->state = WALKING;
			} else if (nouvelEtatGreen == INCLUT) {
				if (board->pinguins[ip]->state != FLOATING)
					board->pinguins[ip]->state = FALLING;
			} else if (nouvelEtatGraphic == LEFTRIGHT && nouvelEtatIO==NONE)
				if (board->pinguins[ip]->previousState == WALKING)
					pinguin_switchDirection(board->pinguins[ip]);
				else {
					board->pinguins[ip]->state = FALLING;
					if (board->graphics[ig]->type==WATER)
						board->pinguins[ip]->state = DROWNING;
				}
			else if (nouvelEtatGraphic == UPDOWN) {
				board->pinguins[ip]->state = WALKING;
			} else if (nouvelEtatGraphic == NONE)
				board->pinguins[ip]->state = FALLING;

			if (collisionDetectionCursorRect(
					board->graphics[1]->position.x
							+ board->graphics[1]->position.w / 2 - 10,
					board->graphics[1]->position.y
							+ board->graphics[1]->position.h - 15,
					board->pinguins[ip]->position) == POINT
					&& collisionDetectionCursorRect(
							board->graphics[1]->position.x
									+ board->graphics[1]->position.w / 2 + 10,
							board->graphics[1]->position.y
									+ board->graphics[1]->position.h - 15,
							board->pinguins[ip]->position) == POINT) {

				board->pinguins[ip]->state = EXITING;
			}
			board->pinguins[ip]->previousColision = nouvelEtatGraphic;
		}
	}

	//######################################################################################
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
void board_createPanel(Board *board) {
	//TODO: coef avec constante
	board->panel = malloc(sizeof(Button*) * NBBTN);
	board->panel[0] = button_create(board->render, PAUSE, 10, 520, 50, 70);
	board->panel[1] = button_create(board->render, FLOATER, 60, 520, 50, 70);
	board->panel[2] = button_create(board->render, MINER, 110, 520, 50, 70);
	board->panel[3] = button_create(board->render, BASHER, 160, 520, 50, 70);
	board->panel[4] = button_create(board->render, BLOCKER, 210, 520, 50, 70);
	board->panel[5] = button_create(board->render, BOMBER, 260, 520, 50, 70);
	board->panel[6] = button_create(board->render, BRIDGER, 310, 520, 50, 70);
	board->panel[7] = button_create(board->render, CLIMBER, 360, 520, 50, 70);
	board->panel[8] = button_create(board->render, DIGGER, 410, 520, 50, 70);
}

void board_manageEvent(Board *board, int x, int y) {
	if (collisionDetectionCursorRect(x, y, board->panel[0]->position)
			== POINT) {
		if (board->pause == 0) {
			board->pause = 1;
		} else {
			board->pause = 0;
		}
		//board->pause=!board->pause;
	} else if (collisionDetectionCursorRect(x, y, board->panel[1]->position)
			== POINT) {
		board->idS = FLOATER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[8]->position)
			== POINT) {
		board->idS = DIGGER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[3]->position)==POINT) {
		board->idS = BASHER;
	}else if(collisionDetectionCursorRect(x,y,board->panel[4]->position)==POINT){
			board->idS=BLOCKER;}
	else if(collisionDetectionCursorRect(x,y,board->panel[5]->position)==POINT){
				board->idS=BOMBER;
	}else if(collisionDetectionCursorRect(x,y,board->panel[6]->position)==POINT){
			board->idS=BRIDGER;
	} else if (board->idS != -1) {
		int i;
		int breaktest = 0;
		//TODO: état sélectionné pour les boutons
		for (i = 0; i < board->nbPinguins; i++) {
			if(board->pinguins[i]->state!=EXITING && board->pinguins[i]->state!=SAVE && board->pinguins[i]->state!=DEAD){
			if (board->pinguins[i]->state == FALLING
					&& collisionDetectionCursorRect(x, y,
							board->pinguins[i]->position) == POINT && board->idS==FLOATER) {
				board->pinguins[i]->state = FLOATING;
				breaktest = 1;
			}
			if(collisionDetectionCursorRect(x, y,
					board->pinguins[i]->position) == POINT && board->idS==BRIDGER){
				board->pinguins[i]->state=BRIDGING;
				breaktest=1;
			}
			if (collisionDetectionCursorRect(x, y, board->pinguins[i]->position)
					== POINT && board->idS == DIGGER) {
				board->pinguins[i]->state = DIGGING;
				breaktest = 1;
			}
			if (collisionDetectionCursorRect(x, y, board->pinguins[i]->position)
					== POINT && board->idS == BASHER) {
				board->pinguins[i]->state = BASHING;
				breaktest = 1;
			}
			//TODO: supprimmer proprement le sprite
			//TODO: animation du STOPPER
			if(collisionDetectionCursorRect(x, y, board->pinguins[i]->position)==POINT && board->idS==BLOCKER){
				if(board->pinguins[i]->state!=FLOATING || board->pinguins[i]->state!=FALLING)
				{board->pinguins[i]->state=DEAD;board_addStop(board, board->pinguins[i]->position);}
				breaktest=1;
			}

			if(collisionDetectionCursorRect(x, y, board->pinguins[i]->position)==POINT && board->idS==BOMBER){
				board->pinguins[i]->state=BOOMING;
			}

			if (breaktest)
				break;
		}
		}
	}
}
