#ifndef GAME_FONC
#define GAME_FONC
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct {
int Num_try ;
int Num_en ;
int t[2] ; 
SDL_Surface *menueng ; 
SDL_Rect posg ; 
SDL_Surface *reponse[3] ;
int selec[3] ;
SDL_Rect posen[3] ;
}enigme ;
void intialiser_en (enigme *en );
void freeenigme(enigme *en);

#endif

