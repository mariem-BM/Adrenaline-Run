#include "SDL_scrolling.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "SDL_char.h"
#include <SDL/SDL_ttf.h>
#include "SDL_collision.h"
const int SCREEN_WIDTH =640;
const int SCREEN_HEIGHT=480;

SDL_Rect moveCamera (SDL_Rect camera,hero player,SDL_Surface *game) {
  camera.x=(player.position.x+player.position.w/2)-SCREEN_WIDTH/2;
  camera.y=(player.poqition.y+player.position.h/2)-SCREEN_HEIGHT/2;

  if (camera.x<0) 
  {
    camera.x=0;
  }

  if (camera.y<0)
  {
    camera.y=0;
  }

if (player.position.x>game->w-camera.w) 
{
  camera.x=game->w -camera.w;
}

return camera;

}

SDL_Rect moveCameraPlayer1(SDL_Rect camera,hero player, SDL_Surface *game )
{
  camera.x=(player.position.x + player.position.w / 2) - SCREEN_WIDTH/4;
  camera.y= (player.position.y+player.position.h /2 )- CREEN_HEIGHT / 2;

if(camera.x<0) 
{
  camera.x=0;
}

if(camera.y<0)
{
camera.y=0;
}
if(player.position.x > game->w -camera.w) 
{
  camera.x = game->w - camera.w;
}

if(player.position.y > game->h - camera.h) 
{
  camera.y = game->h - camera.h;
}
return camera;
}

