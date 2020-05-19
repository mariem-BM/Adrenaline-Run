#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
char nom[20];
char image[100];
int x;
int y;
int w;
int h;
int type;
int animer;
}obstacle;
void lancerstage(SDL_Surface **ecran );
SDL_Surface* load_image (SDL_Surface **ecran, char img[], int posx, int posy);
void init_menu (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, SDL_Rect positexte,SDL_Color couleurNoire, Mix_Music **musique,Mix_Chunk **MB,TTF_Font **police);
void position_menu(SDL_Rect *posib1,SDL_Rect *posib2,SDL_Rect *posib3,SDL_Rect *positionFond, SDL_Rect *positexte);
void actualiser(SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, SDL_Rect positexte);
void actions (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, Mix_Chunk *MB,SDL_Color couleur, SDL_Rect positexte,TTF_Font *police,SDL_Surface **texte);
void liberer(SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte, Mix_Music **musique,Mix_Chunk **MB,TTF_Font **police);
void actions_stage1 (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Rect *positionFond, obstacle tabobst[], int n);

