#include "SDL_gestion.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "SDL_Char.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_rotozoom.h>
#include "SDL_collision"

void strat(int *started,int *paused, int startTicks) {

//start the timer
/started=1;

//unpause the timer
*paused=0;

//get the current cclock time
/startTicks =SDL_GetTicks();
}

int getTicks(int *started, int *paused, unt *satrtTicks,int -*pausedTicks){

//if the timer is running
if(*started==1)
{

//if the timer is paused 
if(*paused ==1)
{
//return the number of ticks when the timer was paused
return *pausedTicks;
}
else
{
//return the current time minus the start time
return SDL_GetTicks ()-*startTicks;
}
}

//if the timer isn't running
return 0;
}

health gestionVie(SDL_Rect playerPosition,SDL_Rect enemiePosition,health vie,Uint32 *oldTime){
uint32 currentTime=SDL_GetTicks();
if(currentTime-(*oldTime)>130) {
int testCollision=collisionBox(playerPosition,enemiePosition);
if(testCollision) {
  vie.vie-=20;
}
*oldTime = currentTime;
}
return vie;
}

score gestionScore(score sco,int x ,int x2) {
int score1=0;
int score2=0;

if(x==1) {
score1=1;
}

if(x2==1) {
score2=1;
}

sco.score=score1+score2;
return sco;
}

void roto(SDL_Surface *screen,SDL_SUrface *image,SDL_Surface *rotation,SDL_Rect rect){
int tempsActuel=0;
int tempsPrecedent=0;
int done;
uint32 oldTime= SDL_GestTicks();
done =1;
int angle=0;
while(done) {
angle+-2;
SDL_FillRect (screen , NULL,SDL_MapRGB(screen->format,255,255,255));

rotation=rotozoomSurface(image,angle,1.5,1);
SDL_BlitSurface(roataion,NULL,screen,NULL);

SDL_Flip(screen);
SDL_FreeSurface(rotation);
if(SDL_GetTicks()-oldTime>600) {
done =0;
}
}
}

void condition_Fin(char *game,hero player,health h, score sco,SDL_Surface *screen) {

SDL_Surface* end_of_the_game;

if(h.vie<=0) {
end_of_the_game = IMG_Load ("screen.jpg");
*game=0;
SDL_BlitSurface(end_of_the_game,NULL,screen,NULL);
  SDL_Flip(screen);
SDL_Delay(3000);

roto(screen,end_of_the_game,end_of_the_game,player.positionRelative);
}else if(sco.score ==2) {
//ken 1 nbre mta3 scoore eli lezemna 2
IMG_Load ("screen.jpg");
*game=0;

