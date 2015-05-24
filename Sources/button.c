#include "button.h"

Button * button_create(SDL_Renderer *render,ButtonType type, int x, int y, int w, int h){
	Button *button= (Button *) malloc(sizeof(Button));
	button->position.x=x;
	button->position.y=y;
	button->position.w=w;
	button->position.h=h;
	button->type=type;
	switch(type){
		case FLOATER:
			button->background=IMG_LoadTexture(render,"img/floater_button.png");
			break;
		case MINER:
			button->background=IMG_LoadTexture(render,"img/miner_button.png");
			break;
		case BASHER:
			button->background=IMG_LoadTexture(render,"img/basher_button.png");
			break;
		case BLOCKER:
			button->background=IMG_LoadTexture(render,"img/blocker_button.png");
			break;
		case BOMBER:
			button->background=IMG_LoadTexture(render,"img/bomber_button.png");
			break;
		case BRIDGER:
			button->background=IMG_LoadTexture(render,"img/bridger_button.png");
			break;
		case CLIMBER:
			button->background=IMG_LoadTexture(render,"img/climber_button.png");
			break;
		case DIGGER:
			button->background=IMG_LoadTexture(render,"img/digger_button.png");
			break;
		case PAUSE:
			button->background=IMG_LoadTexture(render,"img/pause.png");
			break;
		case LEVELS:
					button->background=IMG_LoadTexture(render,"img/start_button.png");
					break;
				case QUIT:
					button->background=IMG_LoadTexture(render,"img/quit_button.png");
					break;
				case REESSAYER:
							button->background=IMG_LoadTexture(render,"img/ressayer_button.png");
							break;
						case CONTINUER:
							button->background=IMG_LoadTexture(render,"img/continuer_button.png");
							break;
						case LEVEL1:
									button->background=IMG_LoadTexture(render,"img/level1_button.png");
									break;
								case LEVEL2:
									button->background=IMG_LoadTexture(render,"img/level2_button.png");
									break;
								case LEVEL3:
									button->background=IMG_LoadTexture(render,"img/level3_button.png");
									break;
								case LEVEL4:
									button->background=IMG_LoadTexture(render,"img/level4_button.png");
									break;
								case LEVEL5:
									button->background=IMG_LoadTexture(render,"img/level5_button.png");
									break;
								case LEVEL6:
									button->background=IMG_LoadTexture(render,"img/level6_button.png");
									break;
	}
	return button;
}
void button_destroy(Button *b){}
