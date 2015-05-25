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
	//TODO: separarer la fonction
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
			board->graphics[board->nbGraphics] = graphicComponent_create(render,
					type, arg1, arg2, arg3, arg4);
			board->nbGraphics++;
		}
		fclose(file);
	} else
		return NULL;

	/*Loading pinguins*/
	board->pinguins = malloc(board->nbPinguins * sizeof(Penguin*));
	int i;
	for (i = 0; i < board->nbPinguins; i++) {
		board->pinguins[i] = penguin_create(render);
		board->pinguins[i]->position.x = board->graphics[0]->position.x + 10;
		board->pinguins[i]->position.y = board->graphics[0]->position.y + 10;
	}
	return board;
}
//TODO: unifier les trois fonctions
void board_addRect(Board *board, SDL_Rect r) {
	board->diggedBlocks = realloc(board->diggedBlocks,
			(board->nbDiggedBlocks + 1) * sizeof(GraphicComponent*));
	board->diggedBlocks[board->nbDiggedBlocks] = graphicComponent_create(
			board->render, DIGGEDBLOCK, r.x - 3, r.y - 3, r.w + 3, r.h + 3);
	board->nbDiggedBlocks++;
}
//TODO: Animer le sprite
void board_addStop(Board *board, SDL_Rect r) {
	board->graphics = realloc(board->graphics,
			(board->nbGraphics + 1) * sizeof(GraphicComponent*));
	board->graphics[board->nbGraphics] = graphicComponent_create(board->render,
			STOPP, r.x - 1, r.y - 2, r.w + 2, r.h + 1);
	board->nbGraphics++;
}

//TODO: optimiser les fonctions add en une seule
void board_addBrick(Board *board, SDL_Rect r) {
	board->graphics = realloc(board->graphics,
			(board->nbGraphics + 1) * sizeof(GraphicComponent*));
	board->graphics[board->nbGraphics] = graphicComponent_create(board->render,
			BRIDGEPART, r.x - 2, r.y + r.h - 1, r.w + 4, 20);
	board->nbGraphics++;
}

//TODO: ajout menu automatique
void board_addOrange(Board *board, SDL_Rect r) {
	board->bashedBlocks = realloc(board->bashedBlocks,
			(board->nbBashedBlocks + 1) * sizeof(GraphicComponent*));
	board->bashedBlocks[board->nbBashedBlocks] = graphicComponent_create(
			board->render, BASHEDBLOCK, r.x - 2, r.y - 2, r.w + 2, r.h + 2);
	board->nbBashedBlocks++;
}

/*Function freeing memory*/
void board_destroy(Board * board) {
	int i;
	SDL_DestroyTexture(board->background);
	for (i = 0; i < board->nbPinguins; i++)
		penguin_destroy(board->pinguins[i]);
	for (i = 0; i < board->nbGraphics; i++)
		graphicComponent_destroy(board->graphics[i]);
	for(i=0;i<board->nbDiggedBlocks;i++)
		graphicComponent_destroy(board->diggedBlocks[i]);
	for(i=0;i<board->nbBashedBlocks;i++)
		graphicComponent_destroy(board->bashedBlocks[i]);
	for(i=0;i<NBBTN;i++)
		button_destroy(board->panel[i]);
	free(board->pinguins);
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
		penguin_computePosition(board->pinguins[i]);
	if (board->moment / ECART < board->nbPinguins)
		board->moment++;
	int nbS = 0, nbM = 0;
	for (i = 0; i < board->nbPinguins; i++) {
		if (board->pinguins[i]->state == SAVED)
			nbS++;
		else if (board->pinguins[i]->state == DEAD)
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
		if (board->pinguins[ip]->state != EXITING
				&& board->pinguins[ip]->state != SAVED
				&& board->pinguins[ip]->state != DEAD
				&& board->pinguins[ip]->state != KILLING) {
			nouvelEtatGraphic = NONE;
			int ig;
			for (ig = 0; ig < board->nbGraphics; ig++) {
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
			for (iv = 0; iv < board->nbDiggedBlocks; iv++) {
				CollisionDirection nv = collisionDetectionRectRect(
						board->diggedBlocks[iv]->position,
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
			for (io = 0; io < board->nbBashedBlocks; io++) {
				CollisionDirection nv = collisionDetectionRectRect(
						board->bashedBlocks[io]->position,
						board->pinguins[ip]->position);
				if (nv == LEFTRIGHT && nouvelEtatIO == NONE)
					nouvelEtatIO = LEFTRIGHT;
				if (nv == UPDOWN && nouvelEtatIO == NONE)
					nouvelEtatIO = UPDOWN;
				if (nv == INCLUT)
					nouvelEtatIO = INCLUT;
			}

			if (board->pinguins[ip]->position.x < 0
							|| board->pinguins[ip]->position.x > 800-32
							|| board->pinguins[ip]->position.y < 0
							|| board->pinguins[ip]->position.y > 600-32) {

							board->pinguins[ip]->state=KILLING;

					}else

			if (board->pinguins[ip]->state == FLOATING
					&& nouvelEtatGraphic != UPDOWN) {
				//board->pinguins[ip]->state==UPDOWN;
				//TODO: gestion Stop plusieur penguin
			} else if (board->pinguins[ip]->state == BRIDGING) {
				if (nouvelEtatGraphic != LEFTRIGHT) {
					if (board->pinguins[ip]->sprite.x >= 256
							&& board->pinguins[ip]->sprite.x <= 288)
						board_addBrick(board, board->pinguins[ip]->position);
				} else {

					board->pinguins[ip]->state = WALKING;

				}

			} else if (board->pinguins[ip]->state == BOMBING) {
//TODO : detection des hautbas pour creuser en L
				//TODO : marche pinguin dans les deux sens inclusion classe;
				if (board->pinguins[ip]->sprite.x >= 256) {
					int ip2;
					for (ip2 = 0; ip2 < board->nbPinguins; ip2++) {
						if (board->pinguins[ip2]->state != DEAD
								&& collisionDetectionRectRect(
										board->pinguins[ip]->position,
										board->pinguins[ip2]->position)
										!= NONE) {
							board->pinguins[ip2]->state = KILLING;
						}
					}
					board_addRect(board, board->pinguins[ip]->position);
				}
			} else if (board->pinguins[ip]->state == DIGGING) { //TODO: PRECONDITION : etre INCLU sinon test en boucle!
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
			} else if (nouvelEtatGraphic == LEFTRIGHT && nouvelEtatIO == NONE)
				if (board->pinguins[ip]->previousState == WALKING)
					pinguin_switchDirection(board->pinguins[ip]);
				else
					board->pinguins[ip]->state = FALLING;
			else if (nouvelEtatGraphic == UPDOWN)
				board->pinguins[ip]->state = WALKING;
			else if (nouvelEtatGraphic == NONE)
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
}
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
		//TODO: état sélectionné pour les boutons
		for (i = 0; i < board->nbPinguins; i++) {
			if (board->pinguins[i]->state != EXITING
					&& board->pinguins[i]->state != SAVED
					&& board->pinguins[i]->state != DEAD) {
				if (board->pinguins[i]->state == FALLING
						&& collisionDetectionCursorRect(x, y,
								board->pinguins[i]->position) == POINT
						&& board->lastSelection == FLOATER) {
					board->pinguins[i]->state = FLOATING;
					breaktest = 1;
				}
				if (collisionDetectionCursorRect(x, y,
						board->pinguins[i]->position) == POINT
						&& board->lastSelection == BRIDGER) {
					board->pinguins[i]->state = BRIDGING;
					breaktest = 1;
				}
				if (collisionDetectionCursorRect(x, y,
						board->pinguins[i]->position) == POINT
						&& board->lastSelection == DIGGER
						&& board->pinguins[i]->state != FLOATING
						&& board->pinguins[i]->state != FALLING) {
					board->pinguins[i]->state = DIGGING;
					breaktest = 1;
				}
				if (collisionDetectionCursorRect(x, y,
						board->pinguins[i]->position) == POINT
						&& board->lastSelection == BASHER) {
					board->pinguins[i]->state = BASHING;
					breaktest = 1;
				}
				//TODO: animation du STOPPER
				if (collisionDetectionCursorRect(x, y,
						board->pinguins[i]->position) == POINT
						&& board->lastSelection == BLOCKER) {
					if (board->pinguins[i]->state != FLOATING
							&& board->pinguins[i]->state != FALLING) {
						board->pinguins[i]->state = DEAD;
						board_addStop(board, board->pinguins[i]->position);
					}
					breaktest = 1;
				}

				if (collisionDetectionCursorRect(x, y,
						board->pinguins[i]->position) == POINT
						&& board->lastSelection == BOMBER) {
					board->pinguins[i]->state = BOMBING;
				}

				if (breaktest)
					break;
			}
		}
	}
}
