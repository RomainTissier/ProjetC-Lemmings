#include <SDL2/SDL.h>
<<<<<<< Updated upstream
#include <SDL2/SDL_image.h>
=======
>>>>>>> Stashed changes

int main(){
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
<<<<<<< Updated upstream
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
			printf("Erreur chargement PNG");
		}
		SDL_Texture *monPNG2 = IMG_LoadTexture(renderer, "img/walker.png");
		if (monPNG2 == NULL){
			printf("Erreur chargement PNG");
		}

		SDL_Rect dst2;
		SDL_Rect src2;
		dst2.x=50;
		dst2.y=50;
		dst2.w=32;
		dst2.h=32;
		src2.x=0;
		src2.y=0;
		src2.w=32;
		src2.h=32;
		
		SDL_Rect dst;
		dst.x=100;
		dst.y=100;
		dst.w=100;
		dst.h=100;	
	
		SDL_RenderClear(renderer);
        	SDL_RenderCopy(renderer, bitmapTex, NULL, NULL);
		SDL_RenderCopy(renderer, monPNG,NULL,&dst);
		SDL_RenderCopy(renderer, monPNG2,&src2,&dst2);
        	SDL_RenderPresent(renderer);

 while (continuer)
    {
        SDL_PollEvent(&event); /* On utilise PollEvent et non WaitEvent pour ne pas bloquer le programme */
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées depuis le dernier tour de boucle */
        {
            positionZozor.x++; /* On bouge Zozor */
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);
    }
		
		SDL_Delay(3000);  		// On crée une temporisation de 3 secondes 

		SDL_DestroyTexture(bitmapTex);
    		SDL_DestroyRenderer(renderer);


        	SDL_DestroyWindow(fenetre);	// On détruit la fenetre
        }else
            printf("Erreur SDL: %s\n",SDL_GetError());
    	SDL_Quit();				// On ferme la librairie SDL
    	return EXIT_SUCCESS;	
=======
                SDL_WINDOW_SHOWN
	);
        if(fenetre){				// On vérifie que la fenêtre s'instancie bien
        	SDL_Delay(3000);  
        	SDL_DestroyWindow(fenetre);
        }else
            printf("Erreur SDL: %s\n",SDL_GetError());
    	SDL_Quit();
    	return EXIT_SUCCESS;
>>>>>>> Stashed changes
}
