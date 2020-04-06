#include "SDL_init.h"
#include <SDL/SDL.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include "SDL_char.h"
#include  <SDL/SDL_ttf.h>
#include "SDL_collision.h"
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

SDL_Rect initPosition(SDL_Rect position,int x,int y,int w, int h) {
if(x!=-1)
{
  position.x=x;
}

if(y!=-1)
{
  position.y=y;
}
if(w!=-1)
{
  position.w=w;
}
if(h!=-1)
{
  position.h=h;
}
return position;
}

enigme loadForRiddle(enigme e) {
TTF_Font *font =NULL;
SDL_Color fontColor = {63,13,58};

if (TTF_init()==-1)
{
  exit(0);
}

font = TTF_OpenFont("baron Neue.otfc",36);
if(font == NULL) 
{
  exit(1);
}

 e.Question=TTF_RenderText_Blended(font,e.question,fontColor);
if(e.Question==NULL)
{
  printf("unable to TTF_RenderText_Solid\n");
}


e.Answer1=TTF_RenderText_Blended(font,e.answer1,fontColor);
if(e.Answer1==NULL)
{
  printf("unable to TTF_RenderText_Solid\n");
}

e.Answer2=TTF_RenderText_Blended(font,e.answer2,fontColor);
if(e.Answer1==NULL)
{
  printf("unable to TTF_RenderText_Solid\n");
}

e.Answer3=TTF_RenderText_Blended(font,e.answer3,fontColor);
if(e.Answer1==NULL)
{
  printf("unable to TTF_RenderText_Solid\n");
}

e.Answer4=TTF_RenderText_Blended(font,e.answer4,fontColor);
if(e.Answer1==NULL)
{
  printf("unable to TTF_RenderText_Solid\n");
}

TTF_CloseFOnt(font);

return e;
}

SDL_Surface* loadImage(char file_name[] {
  SDL_Surface *s=NULL;
s=IMGLoad (filename);
if(s== NULL) 
{
  fprintf(stderr,"loadImage :%s\n",SDL_GetError());
}
return s;
}

enigme initPrintRiddle(enigme e) {
int xBackground, yBackground;
int xA1, yA1;
int xA2, yA2;
int xA3, yA3;
int xA4, yA4;
int xAnswer1,yAnswer1;
int xAnswer2,yAnswer2;
int xAnswer3,yAnswer3;
int xAnswer4,yAnswer4;
int xQuestion,yQuestion;

xBackground=(SCRENN_WIDTH /2)-(e.Background->w/2);
yBackground=(SCRENN_HEIGHT /2)-(e.Background->h/2);

yA1=-yBackground+e.Background->h)/2;
xA1 = xBackground+25;
xA2=e.Button[0]->w+xA1+50;
YA3=yA1+e.Button[0]->h+25;
xA3=xBackground+25;
XA4=e.Button[0]->w+xA3+50;

xAnswer1=xA1;
yAnswer1=yA1;

xAnswer2=xA2;
yAnswer2=yA2;

xAnswer3=xA3;
yAnswer3=yA3;

xAnswer4=xA4;
yAnswer4=yA4;

xQuestion=(xBackground+e.Background->w/2)-(e.QUestion->w/2);
yQuestion=yBackground+20;

e.positionButton1= initPosition(e.positionButton1,xA1,yA1,e.Butoon[0]->w,e.Button[0]->h);

e.positionButton2= initPosition(e.positionButton2,xA2,yA2,e.Butoon[0]->w,e.Button[0]->h);

e.positionButton3= initPosition(e.positionButton3,xA3,yA3,e.Butoon[0]->w,e.Button[0]->h);

e.positionButton4= initPosition(e.positionButton4,xA4,yA4,e.Butoon[0]->w,e.Button[0]->h);

e.positionBackground=initPosition(e.positionBackground,xBackground,yBackground,e.Background->w,e.Background->h);
e.positionQuestion= initPositionQuestion,xQuestion,yQuestion,0,0);

e.postionAnswer1 = initPosition(e.positionAnswer1,xAnswer1,yAnswer1,0,0);
e.postionAnswer2 = initPosition(e.positionAnswer2,xAnswer2,yAnswer2,0,0);
e.postionAnswer3 = initPosition(e.positionAnswer3,xAnswer3,yAnswer3,0,0);
e.postionAnswer4 = initPosition(e.positionAnswer4,xAnswer4,yAnswer4,0,0);

return e;
}



