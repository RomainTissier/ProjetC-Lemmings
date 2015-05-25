#include "penguin.h"


/*Function creating a penguin*/
Penguin* penguin_create(SDL_Renderer* render) {
	Penguin *penguin = malloc(sizeof(Penguin));
	penguin->render = render;
	penguin->position.x = 0;
	penguin->position.y = 0;
	penguin->position.w = 32 - SHIFT * 2;
	penguin->position.h = 32;

	penguin->sprite.x=0;
	penguin->sprite.y=0;
	penguin->sprite.w=0;
	penguin->sprite.h=0;

	penguin->state = INIT;
	penguin->texture = IMG_LoadTexture(render, "img/faller.png");
	penguin->previousState = INIT;
	penguin->counter = 0;
	penguin->sens = 0;
	penguin->previousColision = NONE;
	return penguin;
}

/*Function switching a penguin direction*/
void pinguin_switchDirection(Penguin* pinguin) {
	pinguin->sens = !pinguin->sens;
	pinguin->sprite.y = (pinguin->sprite.y == 0) ? 32 : 0;
	pinguin->sprite.x = SHIFT;
}

static void penguin_walkingUpdate(Penguin *p) {
	if (p->previousState != WALKING) {
		if(p->previousState==BRIDGING){
			p->position.x+=(p->sens)?1:-1;
			p->counter=0;
		}
		p->texture = IMG_LoadTexture(p->render, "img/walker.png");
		p->sprite.x = SHIFT;
		p->sprite.y = (p->sens == 0) ? 32 : 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	if (p->counter >= 40) {
		p->state = KILLING;
	} else {
		p->counter = 0;
		p->sprite.x += 32;
		if (p->sprite.x >= 256)
			p->sprite.x = 0 + SHIFT;
		p->position.x += (p->sprite.y == 0) ? -2 : 2;
	}
}

static void penguin_bombingUpdate(Penguin *p) {
	if (p->previousState != BOMBING) {
		p->texture = IMG_LoadTexture(p->render, "img/bomber.png");
		p->sprite.x = 0;
		p->sprite.y = 0;
		p->sprite.h = 32;
		p->sprite.w = 32;
		p->position.x -= 5;
		p->position.y -= 2;
		p->position.h += 2;
		p->position.w += 5;
	} else {
		p->sprite.x += 32;
		p->position.x -= 2;
		p->position.y -= 2;
		p->position.h += 4;
		p->position.w += 4;
		if (p->sprite.x >= 288)
			p->state = DEAD;
	}
}

static void penguin_bridgingUpdate(Penguin *p) {
	if (p->previousState != BRIDGING) {
		p->texture = IMG_LoadTexture(p->render, "img/bridger.png");
		p->counter = 0;
		p->sprite.x = SHIFT;
		p->sprite.y = (p->sens == 0) ? 32 : 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	p->sprite.x += 32;
	if (p->sprite.x >= 384 - 32)
		p->sprite.x = SHIFT;
	p->position.x += (p->sprite.y == 0) ? -1 : 1;
	p->counter++;
	if (p->counter > 100) {
		p->counter = 0;
		//p->previousState=WALKING;
		p->state = WALKING;
	}
}

static void penguin_bashingUpdate(Penguin *p) {
	if (p->previousState != BASHING) {
		p->texture = IMG_LoadTexture(p->render, "img/basher.png");
		p->sprite.x = SHIFT;
		p->sprite.y = (p->sens == 0) ? 32 : 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	p->sprite.x += 32;
	if (p->sprite.x >= 384)
		p->sprite.x = SHIFT;
	p->position.x += (p->sprite.y == 0) ? -1 : 1;
}
static void penguin_fallingUpdate(Penguin *p) {
	if (p->previousState != FALLING) {
		p->texture = IMG_LoadTexture(p->render, "img/faller.png");
		p->sprite.x = SHIFT;
		p->sprite.y = 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	p->sprite.x += 32;
	if (p->sprite.x >= 256)
		p->sprite.x = 0 + SHIFT;
	p->position.y += 3;
	p->counter += 1;
}

static void penguin_floatingUpdate(Penguin *p) {
	if (p->previousState != FLOATING) {
		p->counter = 0;
		p->texture = IMG_LoadTexture(p->render, "img/floater.png");
		p->sprite.x = SHIFT;
		p->sprite.y = 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	p->sprite.x += 32;
	if (p->sprite.x >= 256)
		p->sprite.x = 0 + SHIFT;
	p->position.y += 2;
}
static void penguin_exitingUpdate(Penguin *p) {
	if (p->previousState != EXITING) {
		p->texture = IMG_LoadTexture(p->render, "img/disappearence.png");
		p->sprite.x = SHIFT;
		p->sprite.y = (p->sens == 0) ? 32 : 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	}
	p->sprite.x += 32;
	if (p->sprite.x >= 256) {
		p->state = SAVED;
	}
}

static void penguin_diggingUpdate(Penguin *p) {
	if (p->previousState != DIGGING) {
		p->texture = IMG_LoadTexture(p->render, "img/digger.png");
		p->sprite.x = SHIFT;
		p->sprite.y = 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;

	}
	p->sprite.x += 32;
	if (p->sprite.x >= 256)
		p->sprite.x = SHIFT;

	p->position.y += 2;
}

static void penguin_killingUpdate(Penguin *p) {
	if (p->previousState != KILLING) {
		p->texture = IMG_LoadTexture(p->render, "img/splash.png");
		p->sprite.x = SHIFT;
		p->sprite.y = 0;
		p->sprite.h = 32;
		p->sprite.w = 32 - SHIFT * 2;
	} else {
		p->sprite.x += 32;
		if (p->sprite.x >= 256) {
			p->state = DEAD;
		}
	}
}
static void penguin_drowningUpdate(Penguin *p){
	if (p->previousState != DROWNING) {
			p->texture = IMG_LoadTexture(p->render, "img/drownfall.png");
			p->sprite.x = SHIFT;
			p->sprite.y = 0;
			p->sprite.h = 32;
			p->sprite.w = 32 - SHIFT * 2;
		} else {
			p->sprite.x += 32;
			if (p->sprite.x >= 480) {
				p->state = DEAD;
			}
		}
}

/*Function actualizing position and penguin sprite*/
void penguin_computePosition(Penguin* penguin) {
	switch (penguin->state) {
	case BOMBING:
		penguin_bombingUpdate(penguin);
		break;
	case BRIDGING:
		penguin_bridgingUpdate(penguin);
		break;
	case BASHING:
		penguin_bashingUpdate(penguin);
		break;
	case FALLING:
		penguin_fallingUpdate(penguin);
		break;
	case FLOATING:
		penguin_floatingUpdate(penguin);
		break;
	case EXITING:
		penguin_exitingUpdate(penguin);
		break;
	case DIGGING:
		penguin_diggingUpdate(penguin);
		break;
	default:
		break;
	}
	/*Final states*/
	if (penguin->state == WALKING)
		penguin_walkingUpdate(penguin);
	if (penguin->state == SAVED || penguin->state == DEAD)
		penguin->sprite.h = 0;
	else if (penguin->state == KILLING)
		penguin_killingUpdate(penguin);
	else if(penguin->state==DROWNING)
		penguin_drowningUpdate(penguin);
	penguin->previousState = penguin->state;
}

/*Function freeing memory*/
void penguin_destroy(Penguin *pinguin) {
	SDL_DestroyTexture(pinguin->texture);
	free(pinguin);
}
