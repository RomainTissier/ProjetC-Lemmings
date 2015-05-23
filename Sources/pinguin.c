#include "pinguin.h"

static const int shift = 5;

/*Function creating a pinguin*/
Pinguin* pinguin_create(SDL_Renderer* render) {
	Pinguin *pinguin = malloc(sizeof(Pinguin));
	pinguin->render = render;
	pinguin->position.x = 0;
	pinguin->position.y = 0;
	pinguin->position.w = 32 - shift * 2;
	pinguin->position.h = 32;
	pinguin->state = INIT;
	pinguin->previousState = INIT;
	pinguin->height = 0;
	pinguin->sens = 0;
	pinguin->previousColision = NONE;
	return pinguin;
}

/*Function switching a pinguin direction*/
void pinguin_switchDirection(Pinguin* pinguin) {
	pinguin->sens = !pinguin->sens;
	pinguin->sprite.y = (pinguin->sprite.y == 0) ? 32 : 0;
	pinguin->sprite.x = 0 + shift;
}

/*Function actualising position and pinguin sprite*/
void pinguin_computePosition(Pinguin* pinguin) {
	if (pinguin->state != SAVE) {
		if (pinguin->state == WALKING) {
			/*Managing the changing of state*/
			if (pinguin->previousState != WALKING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/walker.png");
				pinguin->sprite.x = 0 + shift;
				if (pinguin->sens == 0)
					pinguin->sprite.y = 32;
				else
					pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			}
			/*Test the falling height*/
			//TODO: COLISION EAU === MORT :p
			if (pinguin->height >= 40) {
				pinguin->state = KILLING;
			} else {
				pinguin->height = 0;
				pinguin->sprite.x += 32;
				if (pinguin->sprite.x >= 256)
					pinguin->sprite.x = 0 + shift;
				pinguin->position.x += (pinguin->sprite.y == 0) ? -2 : 2;
			}
		} else if (pinguin->state == BASHING) {
			//############DEBUT BASHING
			/*Managing the changing of state*/
			if (pinguin->previousState != BASHING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/basher.png");
				pinguin->sprite.x = 0 + shift;
				if (pinguin->sens == 0)
					pinguin->sprite.y = 32;
				else
					pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			}
			pinguin->height = 0;
			pinguin->sprite.x += 32;
			if (pinguin->sprite.x >= 384)
				pinguin->sprite.x = 0 + shift;
			pinguin->position.x += (pinguin->sprite.y == 0) ? -2 : 2;
			//#################### fin bashing
		} else if (pinguin->state == FALLING) {
			/*Manage the changing of state*/
			if (pinguin->previousState != FALLING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/faller.png");
				pinguin->sprite.x = 0 + shift;
				pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			}
			pinguin->sprite.x += 32;
			if (pinguin->sprite.x >= 256)
				pinguin->sprite.x = 0 + shift;
			pinguin->position.y += 3;
			pinguin->height += 1;
		} else if (pinguin->state == FLOATING) {
			if (pinguin->previousState != FLOATING) {
				pinguin->height = 0;
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/floater.png");
				pinguin->sprite.x = 0 + shift;
				pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			}
			pinguin->sprite.x += 32;
			if (pinguin->sprite.x >= 256)
				pinguin->sprite.x = 0 + shift;
			pinguin->position.y += 2;
		} else if (pinguin->state == EXITING) {
			if (pinguin->previousState != EXITING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/disappearence.png");
				pinguin->sprite.x = 0 + shift;
				pinguin->sprite.y = (pinguin->sens == 0) ? 32 : 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			}
			pinguin->sprite.x += 32;
			if (pinguin->sprite.x >= 256) {
				pinguin->state = SAVE;
				pinguin->sprite.h = 0;
			}
		} else if (pinguin->state == DIGGING) {
			if (pinguin->previousState != DIGGING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/digger.png");
				pinguin->sprite.x = 0 + shift;
				pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;

			}
			pinguin->sprite.x += 32;
			if (pinguin->sprite.x >= 256) {
				pinguin->sprite.x = 0 + shift;
			}
			pinguin->position.y += 2;
		}
		if (pinguin->state == KILLING) {
			if (pinguin->previousState != KILLING) {
				pinguin->texture = IMG_LoadTexture(pinguin->render,
						"img/splash.png");
				pinguin->sprite.x = 0 + shift;
				pinguin->sprite.y = 0;
				pinguin->sprite.h = 32;
				pinguin->sprite.w = 32 - shift * 2;
			} else {
				pinguin->sprite.x += 32;
				if (pinguin->sprite.x >= 256) {
					pinguin->state = DEAD;
					pinguin->sprite.h = 0;
				}
			}
		}
		pinguin->previousState = pinguin->state;
	}
}

/*Function freeing memory*/
void pinguin_destroy(Pinguin *pinguin) {
	SDL_DestroyTexture(pinguin->texture);
	free(pinguin);
}
