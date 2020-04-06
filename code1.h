#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "SDL_Char.h"
#include <SDL/SDL_Ttf.h>
#include "SDL_collision.h"

/*struct button {
SDL_Rect position;
SDL_SUrface **image;
};

typedef struct button button;*/

struct Enigme{
char question[256];
char answer1[256];
char answer2[256];
char answer3[256];
char answer4[256];
int solution;

SDL_Surface *Button[2];
SDL_Surface *Background;

SDL_SUrface *Question;
SDL_SUrface *Answer1;
SDL_SUrface *Answer2;
SDL_SUrface *Answer3;
SDL_SUrface *Answer4;

SDL_Rect positionBackground;
SDL_Rect positionQuestion;
SDL_Rect positionAnswer1;
SDL_Rect positionAnswer2;
SDL_Rect positionAnswer3;
SDL_Rect positionAnswer4;
};
typedef struct ENigme enigme;


SDL_Rect initPosition(SDL_Rect position,int x,int y,int w, int h);
enigme loadForRiddle(enigme e);
SDL_Surface* loadImage(char file_name[]);
enigme initPrintRiddle(enigme e);

#endif

