#ifndef GESTION_H_INCLUDED
#define GESTION_H_INCLUDED
#define <time.h>
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "SDL_char.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom>
#include "SDL_collision.h"

struct health {
  int vie,
SDL_Rect position;
SDL_SUrface *font_vie;
};

typedef struct health health;

struct score {
  int score;
  SDL_Rect position;
  SDL_Surface *font_score;
};

typedef struct score score;

health gestionVie(SDL_Rect playerPosition,SDL_Rect enemiePosition,health vie,Uint32 *oldTime);

score gestionScore(score sco,int x ,int x2);
void strat(int *started,int *paused, int startTicks);
int getTicks(int *started, int *paused, unt *satrtTicks,int -*pausedTicks);
void roto(SDL_Surface *screen,SDL_SUrface *image,SDL_Surface *rotation,SDL_Rect rect);
void condition_Fin(char *game,hero player,health h, score sco,SDL_Surface *screen);

#endif
