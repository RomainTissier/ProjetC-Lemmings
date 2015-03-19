#include <stdlib.h>

#include <stdio.h>

#include <SDL/SDL.h>

 

void pause();

 

int main(int argc, char *argv[])

{

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

 

    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE); // Ouverture de la fenêtre

    

    pause(); // Mise en pause du programme

 

    SDL_Quit(); // Arrêt de la SDL

 

    return EXIT_SUCCESS; // Fermeture du programme

}

 

void pause()

{

    int continuer = 1;

    SDL_Event event;

 

    while (continuer)

    {

        SDL_WaitEvent(&event);

        switch(event.type)

        {

            case SDL_QUIT:

                continuer = 0;

        }

    }

}
