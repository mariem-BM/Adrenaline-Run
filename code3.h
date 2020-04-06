#ifndef SCROLLING_H_INCLUDED
#define SCROLLING_H_INCLUDED
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_char.h"
#include <SDL/SDL_ttf.h>
#include "SDL_collision.h"

SDL_RECT moveCamera(SDL_Rect camera, hero player, SDL_Surface* game);

SDL_Rect moveCameraPlayer1(SDL_Rect camera, hero player,SDL_Surface* game);

//SDL_Rect moveCameraPlayer2 (SDL_REct camera, hero player, SDL_Surface* game);

SDL_Rect makeItRelative(SDL_REct positionEntit,SDL_Rect camera);

//SDL_Rect makeItRelativePlayer2(SDL_Rect positionEntit, SDL_Rect camera);

void Acceleration(hero *h);

void Decceleration (hero *h);

#endif 

