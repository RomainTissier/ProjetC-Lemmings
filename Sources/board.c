#include "board.h"
#include "collisiondetection.h"
#include "render.h"
//TODO: à optimiser
//TODO: DIGGER petite surface précond
#define NBBTN 9
#define ECART 40
//TODO: précond nombre de pinguin à sauver
//TODO: précond on ne peut pas changer d'action une fois qu'une action est engagée !=> sauf si elle se termine
//TODO: Précond :prendre en compte la sortie de orange ou vert pour stop falling et changement de sens
//TODO: récupérer fait par de yoni

static void loadLevelFile(Board *board, char level[]) {
	/*Loading graphic component from a configuration file*/
	FILE *file = fopen(level, "r");
	if (file != NULL) {
		board->nbGraphics = 0;
		char string[100];
		char typeName[15];
		fgets(string, 100, file);
		sscanf(string, "%s %d", typeName, &(board->nbPinguins));
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
			board->graphics[board->nbGraphics] = graphicComponent_create(
					board->render, type, arg1, arg2, arg3, arg4);
			board->nbGraphics++;
		}
		fclose(file);
	}
	/*Loading pinguins*/
	board->penguins = malloc(board->nbPinguins * sizeof(Penguin*));
	int i;
	for (i = 0; i < board->nbPinguins; i++) {
		board->penguins[i] = penguin_create(board->render);
		board->penguins[i]->position.x = board->graphics[0]->position.x + 10;
		board->penguins[i]->position.y = board->graphics[0]->position.y + 10;
	}
}
/*Function creating a board*/
Board* board_create(SDL_Renderer *render, char level[]) {
	Board *board = malloc(sizeof(Board));
	board->render = render;
	board->background = IMG_LoadTexture(board->render, "img/background.jpg");
	board->pause = 0;
	board->moment = 10;
	board->nbSavedPenguins = 0;
	board_createPanel(board);
	board->lastSelection = -1;
	board->nbDiggedBlocks = 0;
	board->nbBashedBlocks = 0;
	board->diggedBlocks = malloc(0);
	board->graphics = malloc(0);
	board->bashedBlocks = malloc(0);
	loadLevelFile(board, level);
	return board;
}

void board_addRect(Board *board, SDL_Rect r, GraphicType type) {
	if (type == DIGGEDBLOCK) {
		board->diggedBlocks = realloc(board->diggedBlocks,
				(board->nbDiggedBlocks + 1) * sizeof(GraphicComponent*));
		board->diggedBlocks[board->nbDiggedBlocks] = graphicComponent_create(
				board->render, DIGGEDBLOCK, r.x - 3, r.y - 3, r.w + 3, r.h + 3);
		board->nbDiggedBlocks++;
	} else if (type == STOPP) {
		//TODO: annimer le sprite &&  dans pinguin
		board->graphics = realloc(board->graphics,
				(board->nbGraphics + 1) * sizeof(GraphicComponent*));
		board->graphics[board->nbGraphics] = graphicComponent_create(
				board->render, STOPP, r.x - 1, r.y - 2, r.w + 2, r.h + 1);
		board->nbGraphics++;
	} else if (type == BRIDGEPART) {
		board->graphics = realloc(board->graphics,
				(board->nbGraphics + 1) * sizeof(GraphicComponent*));
		board->graphics[board->nbGraphics] = graphicComponent_create(
				board->render, BRIDGEPART, r.x - 2, r.y + r.h - 1, r.w + 4, 20);
		board->nbGraphics++;
	} else if (type == BASHEDBLOCK) {
		board->bashedBlocks = realloc(board->bashedBlocks,
				(board->nbBashedBlocks + 1) * sizeof(GraphicComponent*));
		board->bashedBlocks[board->nbBashedBlocks] = graphicComponent_create(
				board->render, BASHEDBLOCK, r.x - 2, r.y - 2, r.w + 2, r.h + 2);
		board->nbBashedBlocks++;
	}
}

/*Function freeing memory*/
void board_destroy(Board * board) {
	int i;
	SDL_DestroyTexture(board->background);
	for (i = 0; i < board->nbPinguins; i++)
		penguin_destroy(board->penguins[i]);
	for (i = 0; i < board->nbGraphics; i++)
		graphicComponent_destroy(board->graphics[i]);
	for (i = 0; i < board->nbDiggedBlocks; i++)
		graphicComponent_destroy(board->diggedBlocks[i]);
	for (i = 0; i < board->nbBashedBlocks; i++)
		graphicComponent_destroy(board->bashedBlocks[i]);
	for (i = 0; i < NBBTN; i++)
		button_destroy(board->panel[i]);
	free(board->penguins);
	free(board->graphics);
	free(board->diggedBlocks);
	free(board->bashedBlocks);
	free(board->panel);
	free(board);
}

/*Function refreshing board's display.*/
void board_refresh(Board *board) {
	SDL_RenderCopy(board->render, board->background, NULL, NULL);
	int i;
	for (i = 0; i < board->nbGraphics; i++)
		SDL_RenderCopy(board->render, board->graphics[i]->texture, NULL,
				&(board->graphics[i]->position));
	for (i = 0; i < board->nbBashedBlocks; i++)
		SDL_RenderCopy(board->render, board->bashedBlocks[i]->texture, NULL,
				&(board->bashedBlocks[i]->position));
	for (i = 0; i < board->nbDiggedBlocks; i++)
		SDL_RenderCopy(board->render, board->diggedBlocks[i]->texture, NULL,
				&(board->diggedBlocks[i]->position));
	for (i = 0; i < board->nbPinguins && (i < board->moment / ECART); i++)
		SDL_RenderCopy(board->render, board->penguins[i]->texture,
				&(board->penguins[i]->sprite), &(board->penguins[i]->position));
	for (i = 0; i < NBBTN; i++)
		SDL_RenderCopy(board->render, board->panel[i]->background, NULL,
				&(board->panel[i]->position));

}

//TODO : merger green et orange

/*Function computing component's position*/
int board_computePosition(Board *board) {
	int i;
	for (i = 0; i < board->nbPinguins && (i < board->moment / ECART); i++)
		penguin_computePosition(board->penguins[i]);
	if (board->moment / ECART < board->nbPinguins)
		board->moment++;
	int nbS = 0, nbM = 0;
	for (i = 0; i < board->nbPinguins; i++) {
		if (board->penguins[i]->state == SAVED)
			nbS++;
		else if (board->penguins[i]->state == DEAD)
			nbM++;
	}
	board->nbSavedPenguins = nbS;
	if (nbS + nbM == board->nbPinguins) {
		return 1;
	}
	return 0;
}

/*Function managing board's collision*/
void board_manageCollision(Board *board) {
	//TODO: falcult car board meurt prise en compte de la noyade
	//TODO: prise en compte du prob de DESTRUCTABILITE
	CollisionDirection nouvelEtatGraphic;
	int ip;
	for (ip = 0; ip < board->nbPinguins; ip++) {
		if (board->penguins[ip]->state != EXITING
				&& board->penguins[ip]->state != SAVED
				&& board->penguins[ip]->state != DEAD
				&& board->penguins[ip]->state != KILLING) {
			nouvelEtatGraphic = NONE;
			int ig;
			for (ig = 0; ig < board->nbGraphics; ig++) {
				if (board->graphics[ig]->collision) {
					int nc = collisionDetectionRectRect(
							board->graphics[ig]->position,
							board->penguins[ip]->position);
					if (nc != NONE) {
						if (nc == LEFTRIGHT && nouvelEtatGraphic != INCLUT)
							nouvelEtatGraphic = LEFTRIGHT;
						if (nc == UPDOWN && nouvelEtatGraphic == NONE)
							nouvelEtatGraphic = UPDOWN;
						if (nc == INCLUT)
							nouvelEtatGraphic = INCLUT;
					}
				}
			}
			CollisionDirection nouvelEtatDigged = NONE;
			int iv;
			for (iv = 0; iv < board->nbDiggedBlocks; iv++) {
				CollisionDirection nv = collisionDetectionRectRect(
						board->diggedBlocks[iv]->position,
						board->penguins[ip]->position);
				if (nv == LEFTRIGHT && nouvelEtatDigged == NONE)
					nouvelEtatDigged = LEFTRIGHT;
				if (nv == UPDOWN && nouvelEtatDigged == NONE)
					nouvelEtatDigged = UPDOWN;
				if (nv == INCLUT)
					nouvelEtatDigged = INCLUT;
			}
			int io;
			CollisionDirection nouvelEtatBashed = NONE;
			for (io = 0; io < board->nbBashedBlocks; io++) {
				CollisionDirection nv = collisionDetectionRectRect(
						board->bashedBlocks[io]->position,
						board->penguins[ip]->position);
				if (nv == LEFTRIGHT && nouvelEtatBashed == NONE)
					nouvelEtatBashed = LEFTRIGHT;
				if (nv == UPDOWN && nouvelEtatBashed == NONE)
					nouvelEtatBashed = UPDOWN;
				if (nv == INCLUT)
					nouvelEtatBashed = INCLUT;
			}
			//TODO: gestion Stop plusieur penguin
			//TODO : detection des hautbas pour creuser en L
			//TODO : marche pinguin dans les deux sens inclusion classe;
			//TODO: précond: être INCLUT
			//TODO: PRECONDITION : etre INCLU sinon test en boucle!
			if (!(board->penguins[ip]->state == FLOATING
					&& nouvelEtatGraphic != UPDOWN)) {
				if (board->penguins[ip]->position.y < 0
						|| board->penguins[ip]->position.y > 600 - 46)
					/*if the penguin is out of the screen*/
					board->penguins[ip]->state = DROWNING;
				else if (board->penguins[ip]->state == BRIDGING) {
					if (nouvelEtatGraphic != LEFTRIGHT) {
						if (board->penguins[ip]->sprite.x >= 256
								&& board->penguins[ip]->sprite.x <= 288)
							board_addRect(board, board->penguins[ip]->position,
									BRIDGEPART);
					} else
						board->penguins[ip]->state = WALKING;
				} else if (board->penguins[ip]->state == BOMBING) {
					if (board->penguins[ip]->sprite.x >= 256) {
						int ip2;
						for (ip2 = 0; ip2 < board->nbPinguins; ip2++) {
							if (board->penguins[ip2]->state != DEAD
									&& collisionDetectionRectRect(
											board->penguins[ip]->position,
											board->penguins[ip2]->position)
											!= NONE)
								board->penguins[ip2]->state = KILLING;
						}
						board_addRect(board, board->penguins[ip]->position,
								DIGGEDBLOCK);
						printf("x:%d, y:%d, w:%d, h:%d\n",
								board->penguins[ip]->position.x,
								board->penguins[ip]->position.y,
								board->penguins[ip]->position.w,
								board->penguins[ip]->position.h);
					}
				} else if (board->penguins[ip]->state == DIGGING) {
					board_addRect(board, board->penguins[ip]->position,
							DIGGEDBLOCK);
					if (nouvelEtatGraphic == LEFTRIGHT
							&& board->penguins[ip]->previousColision == INCLUT)
						board->penguins[ip]->state = FALLING;
				} else if (board->penguins[ip]->state == BASHING) {
					board_addRect(board, board->penguins[ip]->position,
							BASHEDBLOCK);
					if (board->penguins[ip]->previousColision == INCLUT
							&& nouvelEtatGraphic == LEFTRIGHT)
						board->penguins[ip]->state = WALKING;
				} else if (nouvelEtatDigged == INCLUT) {
					if (board->penguins[ip]->state != FLOATING)
						board->penguins[ip]->state = FALLING;
				} else if (nouvelEtatGraphic == LEFTRIGHT
						&& nouvelEtatBashed == NONE) {
					if (board->penguins[ip]->previousState == WALKING)
						pinguin_switchDirection(board->penguins[ip]);
					else
						board->penguins[ip]->state = FALLING;
				} else if (nouvelEtatGraphic == UPDOWN)
					board->penguins[ip]->state = WALKING;
				else if (nouvelEtatGraphic == NONE)
					board->penguins[ip]->state = FALLING;
			}
				if (collisionDetectionCursorRect(
					board->graphics[1]->position.x
							+ board->graphics[1]->position.w / 2 - 10,
					board->graphics[1]->position.y
							+ board->graphics[1]->position.h - 15,
					board->penguins[ip]->position) == POINT
					&& collisionDetectionCursorRect(
							board->graphics[1]->position.x
									+ board->graphics[1]->position.w / 2 + 10,
							board->graphics[1]->position.y
									+ board->graphics[1]->position.h - 15,
							board->penguins[ip]->position) == POINT)
				board->penguins[ip]->state = EXITING;
			board->penguins[ip]->previousColision = nouvelEtatGraphic;
		}
	}
}
//TODO: annimation STOPPER

void board_createPanel(Board *board) {
//TODO: coef avec constante
	board->panel = malloc(sizeof(Button*) * NBBTN);
	board->panel[0] = button_create(board->render, PAUSE, 10, 520, 50, 70);
	board->panel[1] = button_create(board->render, FLOATER, 60, 520, 50, 70);
	board->panel[2] = button_create(board->render, DIGGER, 110, 520, 50, 70);
	board->panel[3] = button_create(board->render, BASHER, 160, 520, 50, 70);
	board->panel[4] = button_create(board->render, BLOCKER, 210, 520, 50, 70);
	board->panel[5] = button_create(board->render, BOMBER, 260, 520, 50, 70);
	board->panel[6] = button_create(board->render, BRIDGER, 310, 520, 50, 70);
//TODO: gestion dynamique
	board->panel[7] = button_create(board->render, DIGGER, 360, 520, 50, 70);
	board->panel[8] = button_create(board->render, DIGGER, 410, 520, 50, 70);
}
//TODO: board rennomer PINGUINS
//TODO: on ne peut pas creuser en chute libre
void board_manageEvent(Board *board, int x, int y) {
	if (collisionDetectionCursorRect(x, y, board->panel[0]->position)
			== POINT) {
		board->pause = !(board->pause);
	} else if (collisionDetectionCursorRect(x, y, board->panel[1]->position)
			== POINT) {
		board->lastSelection = FLOATER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[8]->position)
			== POINT) {
		board->lastSelection = DIGGER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[3]->position)
			== POINT) {
		board->lastSelection = BASHER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[4]->position)
			== POINT) {
		board->lastSelection = BLOCKER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[5]->position)
			== POINT) {
		board->lastSelection = BOMBER;
	} else if (collisionDetectionCursorRect(x, y, board->panel[6]->position)
			== POINT) {
		board->lastSelection = BRIDGER;
	} else if (board->lastSelection != -1) {
		int i;
		int breaktest = 0;
		for (i = 0; i < board->nbPinguins; i++) {
			if (board->penguins[i]->state != EXITING
					&& board->penguins[i]->state != SAVED
					&& board->penguins[i]->state != DEAD && board->penguins[i]->state!=KILLING) {
				if (collisionDetectionCursorRect(x, y,
						board->penguins[i]->position) == POINT) {
					if (board->penguins[i]->state == FALLING
							&& board->lastSelection == FLOATER) {
						board->penguins[i]->state = FLOATING;
						breaktest = 1;
					} else if (board->lastSelection == BRIDGER) {
						board->penguins[i]->state = BRIDGING;
						breaktest = 1;
					} else if (board->lastSelection == DIGGER
							&& board->penguins[i]->state != FLOATING
							&& board->penguins[i]->state != FALLING) {
						board->penguins[i]->state = DIGGING;
						breaktest = 1;
					} else if (board->lastSelection == BASHER) {
						board->penguins[i]->state = BASHING;
						breaktest = 1;
					} else if (board->lastSelection == BLOCKER) {
						if (board->penguins[i]->state != FLOATING
								&& board->penguins[i]->state != FALLING) {
							board->penguins[i]->state = DEAD;
							board_addRect(board, board->penguins[i]->position,
									STOPP);
						}
						breaktest = 1;
					} else if (board->lastSelection == BOMBER) {
						SDL_Rect projection;
						 projection.x=board->penguins[i]->position.x-21;
						 projection.y=board->penguins[i]->position.y-18;
						 projection.w=board->penguins[i]->position.w+37;
						 projection.h=board->penguins[i]->position.h+34;
						 if(collisionDetectionRectRect(projection,board->graphics[0]->position)==NONE &&
								 collisionDetectionRectRect(board->graphics[1]->position,projection)==NONE && board->penguins[i]->state!=BOMBING)
							 board->penguins[i]->state = BOMBING;
						breaktest = 1;
					}
				}
				if (breaktest)
					break;
			}
		}
	}
}
