#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char argv[]){
	if (SDL_Init(SDL_INIT_VIDEO) != 0 ){	// Initialisation/Test de la SDL
   		printf("Erreur SDL: %si\n", SDL_GetError() );
       	 	return -1;
    	}
        SDL_Window* fenetre = SDL_CreateWindow(	// Création d'une fenêtre
		"Les Lemmings", 		// Titre de la fenêtre
		SDL_WINDOWPOS_UNDEFINED, 	
        	SDL_WINDOWPOS_UNDEFINED,
		640,				// Largeur de la fenêtre
                480,				// Hauteur de la fenêtre
                SDL_WINDOW_SHOWN		// Flag indiquant qu'on ne spécifie pas de comportement en particulier
	);
        if(fenetre){				// On vérifie que la fenêtre s'instancie bien
        	
		SDL_Renderer *renderer = NULL;
	   	SDL_Texture *bitmapTex = NULL;
   		SDL_Surface *bitmapSurface = NULL;
		renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
		
		bitmapSurface = SDL_LoadBMP("img/hello.bmp");
		bitmapTex = SDL_CreateTextureFromSurface(renderer, bitmapSurface);
    		SDL_FreeSurface(bitmapSurface);
		
		SDL_Texture *monPNG = IMG_LoadTexture(renderer, "img/de.png");
		if (monPNG == NULL){
			printf("Ereur chargemetn PNG");
		}
		
		SDL_Rect dst;
		dst.x=100;
		dst.y=100;
		dst.w=100;
		dst.h=100;	
	
		SDL_RenderClear(renderer);
        	SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
		SDL_RenderCopy(renderer, monPNG,NULL,&dst);
        	SDL_RenderPresent(renderer);
		
		SDL_Delay(3000);  		// On créer une temporisation de 3 secondes 

		SDL_DestroyTexture(bitmapTex);
    		SDL_DestroyRenderer(renderer);


        	SDL_DestroyWindow(fenetre);	// On détruit la fenetre
        }else
            printf("Erreur SDL: %s\n",SDL_GetError());
    	SDL_Quit();				// On ferme la librairie SDL
    	return EXIT_SUCCESS;	
}
