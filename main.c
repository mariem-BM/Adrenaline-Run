#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

SDL_Surface *ecran =NULL,*background=NULL,*texte=NULL, *imageDeFond=NULL,*bout1=NULL,*bout2=NULL,*bout3=NULL;
    SDL_Rect positionFond,positionbackground;
    SDL_Rect posib1,posib2,posib3,positexte;
    SDL_Rect posicurseur;
TTF_Font *police = NULL;
SDL_Color couleurNoire={255, 255, 255};


Mix_Music *musique;
Mix_Chunk *MB;

int main(int argc, char *argv[])
{
position_menu(&posib1,&posib2,&posib3,&positionFond, &positexte); 

init_menu (&ecran,&imageDeFond,&bout1,&bout2,&bout3,&texte,posib1,posib2,posib3,positionFond, positexte,couleurNoire,&musique,&MB,&police);
     
actions(&ecran,&imageDeFond,&bout1,&bout2,&bout3,posib1,posib2,posib3,positionFond,MB,couleurNoire, positexte,police,&texte);

liberer(&ecran, &imageDeFond,&bout1,&bout2,&bout3,&texte, &musique,&MB,&police);


return EXIT_SUCCESS;
}


