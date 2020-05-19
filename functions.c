#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "functions.h"
#include "gestion.h"

#define NB_OBST_S1  10
#define LONG_S1  13653
#define HAUT_S1  768
#define VITESSE_S1  16
#define LARG_ECRAN  800
#define HAUT_ECRAN  768
#define LARG_PERSO  50
#define HAUT_PERSO  100
#define POS_Y  445
#define JUMP_Y  110
#define JUMP_X  100



//remplir tab obstacles
void remplir_tabobst (obstacle tabobst[], char emp[])
{
	obstacle ob;
    int i = 0;
FILE * f=NULL;
f = fopen(emp , "r");
    if(f!=NULL)
    {
		while(!feof(f))
		{
			fscanf(f,"nom=%s image=%s x=%d y=%d w=%d h=%d type=%d animer=%d\n",ob.nom,ob.image,&ob.x,&ob.y,&ob.w,&ob.h,&ob.type,&ob.animer);
			i= i+ 1;
			tabobst[i-1] = ob;
		}//while
	}
fclose(f);
}


//mettre à jour tableau des obstacles des obstacles
void maj_tab_obst (int ancx, int ancy, int x, int y, int w , int h, obstacle tabobst[], int n)
{
	obstacle ob;
    int i;
for (i=0; i<n; i++)
	{
		   if ((tabobst[i].x == ancx) && (tabobst[i].y == ancy))
		   {
			      tabobst[i].x=x;
				  tabobst[i].y = y;
				  tabobst[i].w = w;
				  tabobst[i].h = h;
				  break;
		   }
	}
}


// déplacer ennemi un sens
void deplacer_ennemi (SDL_Surface ** ennemi,  SDL_Rect *posenn,  SDL_Rect *posimg,SDL_Surface ** ecran, int v, SDL_Rect rcSprite, int * continuer, obstacle tabobst[], int n)
{
	SDL_Delay(30);
	int c1, c2,c3;
int ancx, ancy;
ancx = (*posenn).x;
ancy = (*posenn).y;
c1 = ((( *posenn).x > rcSprite.x) && (( *posenn).x < rcSprite.x + rcSprite.w));
c2 = ((( *posenn).y >= rcSprite.y) && (( *posenn).y <= rcSprite.y + rcSprite.h));
c3 = (((( *posenn).y + ( *posenn).h) >= rcSprite.y) && ((( *posenn).y + ( *posenn).h)<= rcSprite.y + rcSprite.h));
if  (!(c1 && (c2 || c3)) )
				(*posenn).x = (*posenn).x - v;
else  *continuer = 0;
				 if ((*posimg).x == 0) 
					{(*posimg).x = 50;} 
				 else  if ((*posimg).x == 50) 
                      {(*posimg).x = 100;}    
				else  if ((*posimg).x == 100) 
                      {(*posimg).x = 150;}		
				else {(*posimg).x = 0;}	
maj_tab_obst (ancx, ancy,  (*posenn).x,  (*posenn).y,  (*posenn).w ,  (*posenn).h, tabobst, n);

}

// déplacer ennemi double sens
void deplacer_ennemi_ds (SDL_Surface ** ennemi,  SDL_Rect *posenn,  SDL_Rect *posimg,SDL_Surface ** ecran, int v, int *p, int dist, int *posc, obstacle tabobst[], int n)
{
	SDL_Delay(30);
	int ancx, ancy;
ancx = (*posenn).x;
ancy = (*posenn).y;
	//sens de gauche à droite
 if (*p==0) {
				(*posenn).x = (*posenn).x + v;
				*posc = *posc + v;
				 if ((*posimg).x == 0) 
					{(*posimg).x = 50;} 
				 else  if ((*posimg).x == 50) 
                      {(*posimg).x = 100;}    
				else  if ((*posimg).x == 100) 
                      {(*posimg).x = 150;}		
				else {(*posimg).x = 0;}	
				if (*posc== dist) 
			                {
								
								*p=1;
		                          (*posimg).x == 0;
								  *posc = 0;
							}
 			  }
			//  sens de droite à gauche
 		if (*p==1) {
				(*posenn).x = (*posenn).x - v;
				*posc = *posc + v;
				 if ((*posimg).x == 0) 
					{(*posimg).x = 50;} 
				 else  if ((*posimg).x == 50) 
                      {(*posimg).x = 100;}    
				else  if ((*posimg).x == 100) 
                      {(*posimg).x = 150;}		
				else {(*posimg).x = 0;}	
				
					if (*posc== dist) 
			                {
								
								*p=0;  
                                  (*posimg).x =0;
								    *posc = 0;
							}	
 			  }
			  maj_tab_obst (ancx, ancy,  (*posenn).x,  (*posenn).y,  (*posenn).w ,  (*posenn).h, tabobst, n);

}

// ennemi
void charger_ennemi (SDL_Surface ** ennemi, char image[], SDL_Rect *posenn,  SDL_Rect *posimg,SDL_Surface ** ecran, int posx, int posy, int w, int h)
{
	
	int colorkey;
	
	*ennemi   = IMG_Load(image);
	colorkey = SDL_MapRGB((*ecran)->format, 255, 0, 255);
	SDL_SetColorKey((*ennemi), SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
	/* position ennemi au départ*/
	(*posenn).x = posx;
	(*posenn).y = posy;
	(*posenn).w = w;
	(*posenn).h= h;
	
	/* set animation frame */
	(*posimg).x = 0;
	(*posimg).y = 0;
	(*posimg).w = w;
	(*posimg).h = h;

}



//ennemi


obstacle existeobst (int x, int y, obstacle tabobst[],int n, int choix)
{
obstacle ob;
int c1,c2,c3,c4,c5,c6;

int i;
for (i=0; i < n ; i++)
{
	ob = tabobst[i];
	if (choix == 1) 
	{
		c1 = (((x +(LARG_ECRAN / 2)) >= ob.x)&&((x +(LARG_ECRAN / 2)) <= (ob.x + ob.w)));
		c6 = (((x +(LARG_ECRAN / 2) - LARG_PERSO) >= ob.x)&&((x +(LARG_ECRAN / 2) - LARG_PERSO) <= (ob.x + ob.w)));
	}
	else
	{
		c1 = (((x ) >= ob.x)&&((x ) <= (ob.x + ob.w)));
		c6 = (((x  + LARG_PERSO) >= ob.x)&&((x + LARG_PERSO) <= (ob.x + ob.w)));
	}
c2 = ((ob.y >= y)&&(ob.y <= (y + HAUT_PERSO)));
c3 = (((ob.y + ob.h) >= y)&&((ob.y + ob.h) <= (y + HAUT_PERSO)));
c4 = ((y>= ob.y)&&(y <= (ob.y + ob.h)));
c5 = (((y + HAUT_PERSO) >= ob.y)&&((y + HAUT_PERSO) <= (ob.y + ob.h)));

//printf("c1=%d, c6= %d, c2=%d, c3=%d, c4=%d, c5=%d \n",c1,c6, c2,c3,c4,c5);
if ((c1 || c6) && ((c2 || c3)||(c4||c5))) {return ob;}
  }//for
ob.x = -1;
ob.y = -1;
return ob;
}

void descendre (int v, int arvy, SDL_Surface** ecran , SDL_Surface**sprite, SDL_Surface** imageDeFond, SDL_Rect positionFond, SDL_Rect rcSrc, SDL_Rect *rcSprite,  SDL_Rect *rcFond, SDL_Surface**ennemi, SDL_Rect posimg, SDL_Rect *posenn)
{
	int n,i,jy;
	jy = arvy - ((*rcSprite).y + HAUT_PERSO);
    n = jy / v;
	for(i=0 ; i<n ; i++)
	{
		if (((*rcSprite).y + HAUT_PERSO + v)<= arvy) (*rcSprite).y=(*rcSprite).y + v;
		else (*rcSprite).y = arvy - HAUT_PERSO;
		
		 if (((*rcSprite).x + LARG_PERSO) > LARG_ECRAN) (*rcSprite).x = LARG_ECRAN - LARG_PERSO;
  	SDL_BlitSurface(*imageDeFond,rcFond,*ecran,&positionFond);
	SDL_BlitSurface(*sprite, &rcSrc, *ecran, rcSprite);
	if (  (*posenn).x  > 0) {
	SDL_BlitSurface(*ennemi, &posimg, *ecran, posenn); }
	SDL_UpdateRect(*ecran, 0, 0, 0, 0);    	
	//SDL_Delay(10);
	}
}

void sauter (int v, int jx, int jy, SDL_Surface** ecran , SDL_Surface**sprite, SDL_Surface** imageDeFond, SDL_Rect positionFond, SDL_Rect rcSrc, SDL_Rect *rcSprite,  SDL_Rect *rcFond, int choix,SDL_Surface**ennemi, SDL_Rect posimg, SDL_Rect *posenn, obstacle tabobst[], int nb)
{
	obstacle ob;
	int n,i,arvx,arvy;
	if (choix==0)
	{
		ob = existeobst (((*rcSprite).x + jx),((*rcSprite).y - jy), tabobst,nb,0);
		if (ob.x == -1)
				{
					arvx = (*rcSprite).x + jx;
					arvy = (*rcSprite).y - jy;
					
				}
		else
				{
					if (((*rcSprite).x + jx) > ob.x) 
					{
							arvx = ob.x;
							jx = arvx - ((*rcSprite).x + (*rcSprite).w);
					}
					
					if ((((*rcSprite).y - jy) < (ob.y + ob.h)) && (((*rcSprite).y) > (ob.y + ob.h)))
					{
							arvy = (ob.y + ob.h);
							jy =  (*rcSprite).y - arvy;
					}
				}
		
		if (jx>=jy) n = jx / v;
		else n = jy / v;
		
	for(i=0 ; i<n ; i++)
	{
		if (((*rcSprite).x + v)<= arvx) (*rcSprite).x=(*rcSprite).x + v;
		else (*rcSprite).x = arvx;
		if (((*rcSprite).y - v)>= arvy) (*rcSprite).y=(*rcSprite).y - v;
		else (*rcSprite).y = arvy;
		
		 if (((*rcSprite).x + LARG_PERSO) > LARG_ECRAN) (*rcSprite).x = LARG_ECRAN - LARG_PERSO;
  	SDL_BlitSurface(*imageDeFond,rcFond,*ecran,&positionFond);
	SDL_BlitSurface(*sprite, &rcSrc, *ecran, rcSprite);
	if (  (*posenn).x  > 0) {
	SDL_BlitSurface(*ennemi, &posimg, *ecran, posenn); }
	SDL_UpdateRect(*ecran, 0, 0, 0, 0);    	
	//SDL_Delay(10);
	}
	} //choix == 0
else
	{
			ob = existeobst (((*rcFond).x + jx),((*rcSprite).y - jy), tabobst,nb,1);
		
		if (ob.x == -1)
				{
					arvx = (*rcFond).x + jx;
					arvy = (*rcSprite).y - jy;
					
				}
		else
		{
			//printf("xsauter= %d  ysauter= %d \n",ob.x,ob.y);
			//if ((((*rcFond).x + (LARG_ECRAN/2))  + jx) > ob.x) 
				if (((*rcSprite).x +(*rcSprite).w + jx) > (ob.x- (*rcFond).x)) 
					{
						
							jx = (ob.x - (*rcFond).x) - ((*rcSprite).x + (*rcSprite).w)  ;
						//	jx = ob.x - ((*rcFond).x + (LARG_ECRAN/2)) ;
							//if (((*rcFond).x + (LARG_ECRAN/2)) < ob.x) 
							if (((*rcSprite).x) < (ob.x - (*rcFond).x)) 
							arvx=(*rcFond).x + jx;
						   else arvx = (*rcFond).x;
					}
					
					if ((((*rcSprite).y - jy) < (ob.y + ob.h)) && (((*rcSprite).y) > (ob.y + ob.h)))
					{
							arvy = (ob.y + ob.h);
							jy =  (*rcSprite).y - arvy;
					}
				}
	
		if (jx>=jy) n = jx / v;
		else n = jy / v;
		
	//	(*rcSprite).x = LARG_ECRAN/2 - (*rcSprite).w;
	for(i=0 ; i<n ; i++)
	{
		if (((*rcFond).x + v)<= arvx) 
			{
				(*rcFond).x=(*rcFond).x + v;
				(*posenn).x = (*posenn).x - v;
				maj_tab_obst ( (*posenn).x,  (*posenn).y,  ((*posenn).x - v),  (*posenn).y,  (*posenn).w ,  (*posenn).h, tabobst,nb);
				
			}
		else (*rcFond).x = arvx;
		if (((*rcSprite).y - v)>= arvy) (*rcSprite).y=(*rcSprite).y - v;
		else (*rcSprite).y = arvy;
		
		 if (((*rcSprite).x + LARG_PERSO) > LARG_ECRAN) (*rcSprite).x = LARG_ECRAN - LARG_PERSO;
  	SDL_BlitSurface(*imageDeFond,rcFond,*ecran,&positionFond);
	SDL_BlitSurface(*sprite, &rcSrc, *ecran, rcSprite);
		if (  (*posenn).x  > 0) {
	SDL_BlitSurface(*ennemi, &posimg, *ecran, posenn); }
	SDL_UpdateRect(*ecran, 0, 0, 0, 0);    
//SDL_Delay(5);	
	}
	} //else choix
}
//vérifier si le personnage est sur un obstacle 
//Si vrai : retourne coordonnée y de l'obstacle 
//Si faux : retourne -1
int sur_obst (int x,int y, obstacle tabobst[],int n, int choix)
{
	int c1,c2,c3;
obstacle ob;
int i;
for (i=0; i <n; i++)
    {
     ob = tabobst[i];
	  if (ob.type != 2) {
//printf("position x=%d obx=%d \n",x +(LARG_ECRAN / 2), ob.x); 
if (choix==1)
{
	c1 = (((x +(LARG_ECRAN / 2)-LARG_PERSO) >= ob.x)&&((x +(LARG_ECRAN / 2)-LARG_PERSO) <= (ob.x + ob.w)));
	c2 = (((x +(LARG_ECRAN / 2)) >= ob.x)&&((x +(LARG_ECRAN / 2)) <= (ob.x + ob.w)));
}
else
{
	c1 = (((x +LARG_PERSO) >= ob.x)&&((x +LARG_PERSO) <= (ob.x + ob.w)));
	c2 = (((x ) >= ob.x)&&((x ) <= (ob.x + ob.w)));
}
	c3 = ((y + HAUT_PERSO)<=ob.y);
if ((c1 || c2) && c3) { return ob.y;}
  }//while
	}//if
return -1;
}


//actions stage 1

void actions_stage1 (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Rect *positionFond, obstacle tabobst[], int n)
{
	int f=1; int ax, ay;
	int sob ;
int saut = 0;
Uint8 *keystates;
int up_pressed;
int down_pressed;
int left_pressed;
int right_pressed;
obstacle ob;
int i, p, posc;
int posx,posy,w,h;
SDL_Surface *sprite, *ennemi;
SDL_Rect rcSrc, rcSprite, rcFond , posimg, posenn;
int colorkey;
/* set keyboard repeat */
SDL_EnableKeyRepeat(70, 70);
//sprite   =SDL_LoadBMP("image/stage1/perso.bmp");
sprite   =IMG_Load("image/stage1/perso.png");
colorkey = SDL_MapRGB((*ecran)->format, 255, 0, 255);
SDL_SetColorKey(sprite, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

rcFond.x = 0;
rcFond.y = 0;
rcFond.w = LARG_ECRAN;
rcFond.h = HAUT_S1;

/* set sprite position */
rcSprite.x = 0;
rcSprite.y = POS_Y - HAUT_PERSO;
rcSprite.w = LARG_PERSO;
rcSprite.h = HAUT_PERSO;
/* set animation frame */
rcSrc.x = 0;
rcSrc.y = 0;
rcSrc.w = LARG_PERSO;
rcSrc.h = HAUT_PERSO;

//*********************gestion de temps
SDL_Surface * scoretext, *livestext,* timetext;
timer t ;
int score, lives, u;
SDL_Surface * obj1;
SDL_Rect rectscore, rectlive, recttime;
rectscore.x=50;
    rectscore.y = 10;
	
	rectlive.x=150;
    rectlive.y = 10;
	
	recttime.x=250;
    recttime.y = 10;
    //rect1.h = obj1->h;
    //rect1.w = obj1->w;
	//***********************gestion de temps

//ennemi
w=50; h=100 ; posx=LARG_ECRAN - w; posy = POS_Y - h;
charger_ennemi (&ennemi, "image/stage1/ennemi.png", &posenn,  &posimg,&* ecran, posx,posy , w, h);

SDL_Event event;
int continuer = 1;
p = 0;
posc = 0;
while (continuer)
{
if (posenn. x > 0)
	deplacer_ennemi (&ennemi,  &posenn,  &posimg,&* ecran, 3, rcSprite, &continuer, tabobst, n);
//deplacer_ennemi_ds (&ennemi,  &posenn,  &posimg,&* ecran, 3, &p, 300, &posc, tabobst, n);
//SDL_WaitEvent(&event);
if (SDL_PollEvent(&event)) {
switch(event.type)
{
	case SDL_QUIT:
	continuer = 0;
	break;

case SDL_KEYDOWN:
	keystates = SDL_GetKeyState(NULL);


up_pressed = keystates[SDLK_UP];
down_pressed = keystates[SDLK_DOWN];
left_pressed = keystates[SDLK_LEFT];
right_pressed = keystates[SDLK_RIGHT];
//printf ("up= %d  - down = %d - left = %d - right = %d \n",up_pressed, down_pressed, left_pressed, right_pressed);
            switch(event.key.keysym.sym)// win teta9ra l click
            {

            case SDLK_RETURN: //bouton entrer
              
                     break;
            case SDLK_DOWN:
               
		     break;

            case SDLK_UP:
		if (right_pressed==0)
		{
			
		}//rigth_pressed
			
                     break;
            case SDLK_RIGHT:
		if (up_pressed == 0) {
		
		if ( rcSrc.x == 0 )
			 rcSrc.x = LARG_PERSO;
		  else if ( rcSrc.x == LARG_PERSO )
			 rcSrc.x = LARG_PERSO * 2;
		 else if ( rcSrc.x == (LARG_PERSO * 2) )
			 rcSrc.x = LARG_PERSO * 3;
		  else if ( rcSrc.x == (LARG_PERSO * 3) )
			 rcSrc.x = LARG_PERSO * 4;
		  else if ( rcSrc.x == (LARG_PERSO * 4) )
			 rcSrc.x = LARG_PERSO * 5;
		  else  rcSrc.x = 0;
		
		 if ((rcSprite.x+LARG_PERSO) < (LARG_ECRAN / 2)) 
		 {
			 ob = existeobst (rcSprite.x,rcSprite.y, tabobst,n,0);
			 if(ob.x==-1)
			 rcSprite.x += VITESSE_S1;
	 		  sob =sur_obst(rcFond.x, rcSprite.y, tabobst,n,0);
			 
		 }
		else {
			
		if ((rcFond.x + LARG_ECRAN)<LONG_S1)
		{
		  rcSprite.x = (LARG_ECRAN / 2) - LARG_PERSO;
		  ob = existeobst (rcFond.x,rcSprite.y, tabobst,n,1);
		  
		if(ob.x==-1)
		{ 
			rcFond.x =  rcFond.x + VITESSE_S1;
			maj_tab_obst ( posenn.x,  posenn.y,  (posenn.x - VITESSE_S1),  posenn.y,  posenn.w ,  posenn.h, tabobst,n);
		   posenn.x = posenn.x - VITESSE_S1;
			 
		}
		 sob =sur_obst(rcFond.x, rcSprite.y, tabobst,n,1);
	
		}
		else
		{
			rcSprite.x += VITESSE_S1;
			 sob =sur_obst(rcFond.x, rcSprite.y, tabobst,n,0);
		}
		     }  
			
			 if (sob != -1)
			 {
				 rcSprite.y = sob - HAUT_PERSO-1;
			 }
			 else rcSprite.y = POS_Y - HAUT_PERSO;
			 }//up_pressed
		  break;
	}

//Saut
   if ((up_pressed == 1) && (right_pressed == 1))
        {
//SDL_EnableKeyRepeat(0, 0);
		if ( rcSrc.x == 0 )
			 rcSrc.x = LARG_PERSO;
		  else if ( rcSrc.x == LARG_PERSO )
			 rcSrc.x = LARG_PERSO * 2;
		  else  rcSrc.x = 0;
//if (saut==0) {
	//	saut = 1;
		
		if ((rcSprite.x+LARG_PERSO) < (LARG_ECRAN / 2)) 
		//{rcSprite.x += JUMP_X; rcSprite.y -= JUMP_Y;}
	sauter (1, JUMP_X, JUMP_Y,  &*ecran ,  &sprite,  &*imageDeFond, *positionFond, rcSrc, &rcSprite,  &rcFond, 0,&ennemi, posimg, &posenn,tabobst,n);
	
		else {
			
		if ((rcFond.x + LARG_ECRAN)<LONG_S1)
		{
		  rcSprite.x = (LARG_ECRAN / 2) - LARG_PERSO;
		//if(existeobsty (rcFond.x,rcSprite.y, "fichier/stage1.txt")==0)
		  //{
			//  rcFond.x =  rcFond.x + JUMP_X; rcSprite.y -= JUMP_Y;
			sauter (1, JUMP_X, JUMP_Y,  &*ecran ,  &sprite,  &*imageDeFond, *positionFond, rcSrc, &rcSprite,  &rcFond, 1,&ennemi, posimg, &posenn,tabobst,n);
			
			  //}
		}
		else 
			sauter (1, JUMP_X, JUMP_Y,  &*ecran ,  &sprite,  &*imageDeFond, *positionFond, rcSrc, &rcSprite,  &rcFond, 0,&ennemi, posimg, &posenn,tabobst,n);
		 
		//{rcSprite.x += JUMP_X; rcSprite.y -= JUMP_Y;}
			}
			
			
			sob =sur_obst(rcFond.x, rcSprite.y, tabobst,n,1);
			 
			 if (sob != -1) 
			 {
				 //rcSprite.y = sob - HAUT_PERSO;
				 descendre (VITESSE_S1, sob-1, &* ecran , &sprite, &* imageDeFond, *positionFond, rcSrc, &rcSprite,  &rcFond,&ennemi, posimg, &posenn);
				 
			 }
			 else
			 {
				// rcSprite.y = POS_Y - HAUT_PERSO;
				  descendre (1, POS_Y, &* ecran , &sprite, &* imageDeFond, *positionFond, rcSrc, &rcSprite,  &rcFond,&ennemi, posimg, &posenn);
			 }
	//	}//saut == 0
		
	}
break;

case SDL_KEYUP:
break;
case SDL_MOUSEBUTTONUP:
if (f==1)
{
printf("f=%d  x= %d \n",f,rcFond.x + event.button.x);
ax = rcFond.x + event.button.x;
f= f + 1;
}
else if (f==2)
{
printf("f=%d  y= %d \n",f,event.button.y);
ay = event.button.y;
f= f + 1;
}
else if (f==3)
{
printf("f=%d  w= %d \n",f,(rcFond.x + event.button.x) - ax);
f= f + 1;
}
else if (f==4)
{
printf("f=%d  h= %d \n",f,event.button.y-ay);
f=  1;
}
//printf("Position obstacle x=%d - y=%d \n",event.button.x + rcFond.x,event.button.y);
printf("Position  x=%d \n", rcFond.x + event.button.x);
break;

case SDL_MOUSEMOTION:
break;

 
	
}//switch1

//****************************************** début Gestion temps et score
switch (event.key.keysym.sym){
         case SDLK_UP:
         // rect1.y-=10;
          score++;
  break;
         case SDLK_DOWN:
        // rect1.y+=10;
         score++;
  break;
  case SDLK_RIGHT:
        // rect1.x+=10;
         score++;
  break;
  case SDLK_LEFT:
         //rect1.x-=10;
         score++;
  break;}//switch 

/*scoretext = updateScore(&score);//score
printf("score :%d \n",score);
livestext = updateLives(&lives);//life
printf("lives :%d \n",lives);
timetext = gameTime(&t);//timer
printf("timer :%d : %d \n", t.min, t.sec);*/

//*********fin gestion temps et score

}//if (SDL_PollEvent(&event))
        if ((rcSprite.x + LARG_PERSO) > LARG_ECRAN) rcSprite.x = LARG_ECRAN - LARG_PERSO;
  	SDL_BlitSurface(*imageDeFond,&rcFond,*ecran,positionFond);
	
	//**gestion de temps
	//  SDL_BlitSurface(scoretext, NULL, *ecran, &rectscore); /* Blit du texte */
	 //  SDL_BlitSurface(livestext, NULL, *ecran, &rectlive); /* Blit du texte */
		  //SDL_BlitSurface(timetext, NULL, *ecran, &recttime); /* Blit du texte */
	//**gestion de temps
	
	SDL_BlitSurface(sprite, &rcSrc, *ecran, &rcSprite);
	if (  posenn.x  > 0) {
	SDL_BlitSurface(ennemi, &posimg, *ecran, &posenn);
	}
	SDL_UpdateRect(*ecran, 0, 0, 0, 0);      
}//while
}

void lancerstage(SDL_Surface **ecran )
{
	obstacle tabobst[NB_OBST_S1];
*ecran = SDL_SetVideoMode(800,768,32,SDL_HWSURFACE);
SDL_Surface *imageDeFond, *temp;
  SDL_Rect positionFond;
     positionFond.x =0;
    positionFond.y =0;
  temp = IMG_Load("image/stage1/background.png");
//temp   = SDL_LoadBMP("image/stage1/background.bmp");
  imageDeFond = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);
 SDL_BlitSurface(imageDeFond,NULL,*ecran,&positionFond);
  SDL_Flip(*ecran);
//SDL_Surface *obstacles[NB_OBST_S1];
//SDL_Rect obstpos[NB_OBST_S1];
/*obstacle ob;
int i = 0;
char ch[50];
strcpy(ch,"image/stage1/");

FILE * f=NULL;
f = fopen("fichier/stage1.txt" , "r");


    if(f!=NULL)
    {
    while(!feof(f))
    {
        fscanf(f,"nom=%s image=%s x=%d y=%d w=%d h=%d type=%d animer=%d\n",ob.nom,ob.image,&ob.x,&ob.y,&ob.w,&ob.h,&ob.type,&ob.animer);
	//temp = IMG_Load(ob.image);
	//temp = SDL_LoadBMP(ob.image);
        //obstacles[i]= SDL_DisplayFormat(temp);
        //SDL_FreeSurface(temp);
 obstacles[i] = SDL_LoadBMP(ob.image);
	obstpos[i].x=ob.x;
	obstpos[i].y=ob.y;
	i=i+1;
    }
    }
    else
        {
    printf("erreur\n");
      }
      fclose(f);

/*for(i=0;i<NB_OBST_S1;i++)
{
SDL_BlitSurface(obstacles[i],NULL,*ecran,&obstpos[i]);
}*/
  SDL_Flip(*ecran);
 remplir_tabobst (tabobst, "fichier/stage1.txt");
actions_stage1 (&*ecran, &imageDeFond,&positionFond, tabobst, NB_OBST_S1);
}

SDL_Surface* load_image (SDL_Surface **ecran, char img[], int posx, int posy)
{
SDL_Surface *image=NULL;
 SDL_Rect pos;


    pos.x =posx;
    pos.y =posy;

    image = SDL_LoadBMP(img);
    SDL_BlitSurface(image,NULL,*ecran,&pos);
    return image;
}

void liberer(SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte, Mix_Music **musique,Mix_Chunk **MB,TTF_Font **police)
{
TTF_CloseFont(*police);
TTF_Quit();


    	SDL_FreeSurface(*imageDeFond);
	SDL_FreeSurface(*texte);	
	SDL_FreeSurface(*bout1);
   	SDL_FreeSurface(*bout2);
	SDL_FreeSurface(*bout3);
        
   	SDL_FreeSurface(*ecran);
	Mix_FreeMusic(*musique);
	Mix_FreeChunk(*MB);
    	Mix_CloseAudio();
    	SDL_Quit();
}

void init_menu (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, SDL_Rect positexte,SDL_Color couleurNoire, Mix_Music **musique,Mix_Chunk **MB,TTF_Font **police)
{

		SDL_Surface *SDL_GetVideoSurface(void);
		TTF_Init();
 		SDL_Init(SDL_INIT_EVERYTHING);
		*ecran = SDL_SetVideoMode(720,720,32,SDL_HWSURFACE);
		SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
  		  {
       			 fprintf(stderr,"%s", Mix_GetError());
   		  }
 		Mix_VolumeMusic(MIX_MAX_VOLUME / 1);

*police = TTF_OpenFont("police/menu/roman.ttf", 15);

   *musique = Mix_LoadMUS("son/menu/G3.mp3");
       *MB = Mix_LoadWAV("son/menu/Click.wav");
     *imageDeFond = SDL_LoadBMP("image/menu/menu.bmp");
    *bout1=SDL_LoadBMP("image/menu/p.bmp");
    *bout2=SDL_LoadBMP("image/menu/oo.bmp");
    *bout3=SDL_LoadBMP("image/menu/e.bmp");
 SDL_BlitSurface(*imageDeFond,NULL,*ecran,&positionFond);
    SDL_BlitSurface(*bout1,NULL,*ecran,&posib1);
    SDL_BlitSurface(*bout2,NULL,*ecran,&posib2);
    SDL_BlitSurface(*bout3,NULL,*ecran,&posib3);
 *texte = TTF_RenderText_Blended(*police, "", couleurNoire);
        SDL_BlitSurface(*texte, NULL, *ecran, &positexte); /* Blit du texte */
        SDL_Flip(*ecran);

 

}

void position_menu(SDL_Rect *posib1,SDL_Rect *posib2,SDL_Rect *posib3,SDL_Rect *positionFond, SDL_Rect *positexte)
{
    positionFond->x =0;
    positionFond->y =0;
    posib1->x=427;
    posib1->y=214;
    posib2->x=383;
    posib2->y=315;
    posib3->x=437;
    posib3->y=420;
    positexte->x =60;
    positexte->y =237;  
    positexte->w=300;
    positexte->h=40;
}

void actualiser(SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Surface **texte,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, SDL_Rect positexte)
{

    SDL_BlitSurface(*imageDeFond,NULL,*ecran,&positionFond);
    SDL_BlitSurface(*bout1,NULL,*ecran,&posib1);
    SDL_BlitSurface(*bout2,NULL,*ecran,&posib2);
    SDL_BlitSurface(*bout3,NULL,*ecran,&posib3);
    SDL_BlitSurface(*texte,NULL,*ecran,&positexte);
    SDL_Flip(*ecran);
}

void actions (SDL_Surface **ecran, SDL_Surface **imageDeFond,SDL_Surface **bout1,SDL_Surface **bout2,SDL_Surface **bout3,SDL_Rect posib1,SDL_Rect posib2,SDL_Rect posib3,SDL_Rect positionFond, Mix_Chunk *MB,SDL_Color couleur, SDL_Rect positexte,TTF_Font *police,SDL_Surface **texte)
{
    int c1=0,c2=0,c3=0, c4=0;
    int i=0;
SDL_Event event;
    int continuer = 1;

while (continuer)
{

SDL_WaitEvent(&event);

switch(event.type)
{
	case SDL_QUIT:
	continuer = 0;
	break;

case SDL_KEYDOWN:
*texte = TTF_RenderText_Blended(police, "", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
            switch(event.key.keysym.sym)// win teta9ra l click
            {

            case SDLK_RETURN: //bouton entrer
                if (i==1)
                {

                }
                else if (i==2)
                {
                }
                else if (i==3)
                {
		 continuer=0;
                }
                     break;
            case SDLK_DOWN:
                i++;
                if(i>3)
                {
                    i=1;

                }

                if(i==1)
                {
                        *bout1=SDL_LoadBMP("image/menu/p.bmp");
            // SDL_BlitSurface(*bout1, NULL, *ecran, & posib1);
                Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Cliquer ici pour jouer", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);}
                else{
                *bout1=SDL_LoadBMP("image/menu/play.bmp");
               SDL_BlitSurface(*bout1, NULL, *ecran, & posib1);
                SDL_Flip(*ecran);
                }
                if(i==2)
                {  *bout2=SDL_LoadBMP("image/menu/oo.bmp");
       SDL_BlitSurface(*bout2, NULL, *ecran, & posib2);
                    Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Configurer le jeu ici", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);}
               else{ *bout2=IMG_Load("image/menu/op.jpg");
                   SDL_BlitSurface(*bout2, NULL, *ecran, & posib2);
                    SDL_Flip(*ecran);
                }
                if(i==3)
                {
          
                *bout3=SDL_LoadBMP("image/menu/e.bmp");
              SDL_BlitSurface(*bout3, NULL, *ecran, & posib3);
                    
                   Mix_PlayChannel(-1,MB,0);
 *texte = TTF_RenderText_Blended(police, "Cliquer ici pour quitter le jeu", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
                    }
                else{ *bout3=SDL_LoadBMP("image/menu/exit.bmp");
                 SDL_BlitSurface(*bout3, NULL, *ecran, & posib3);
               SDL_Flip(*ecran);
		}
     SDL_Flip(*ecran);
	break;


               case SDLK_UP:
                i--;
                if(i<1)
                {
                    i=3;
                }

                if(i==1)
                {
                        *bout1=SDL_LoadBMP("image/menu/p.bmp");
             SDL_BlitSurface(*bout1, NULL, *ecran, & posib1);
                Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Cliquer ici pour jouer", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);}
                else{
                *bout1=SDL_LoadBMP("image/menu/play.bmp");
               SDL_BlitSurface(*bout1, NULL, *ecran, & posib1);
                SDL_Flip(*ecran);
                }
                if(i==2)
                {  *bout2=SDL_LoadBMP("image/menu/oo.bmp");
       SDL_BlitSurface(*bout2, NULL, *ecran, & posib2);
                    Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Configurer le jeu ici", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);}
               else{ *bout2=IMG_Load("image/menu/op.jpg");
                   SDL_BlitSurface(*bout2, NULL, *ecran, & posib2);
                    SDL_Flip(*ecran);
                }
                if(i==3)
                {
          
                *bout3=SDL_LoadBMP("image/menu/e.bmp");
              SDL_BlitSurface(*bout3, NULL, *ecran, & posib3);
                    
                   Mix_PlayChannel(-1,MB,0);
 *texte = TTF_RenderText_Blended(police, "Cliquer ici pour quitter le jeu", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
                    }
                else{ *bout3=SDL_LoadBMP("image/menu/exit.bmp");
                 SDL_BlitSurface(*bout3, NULL, *ecran, & posib3);
               SDL_Flip(*ecran);
		}
     SDL_Flip(*ecran);
	break;
}


	case SDL_MOUSEBUTTONUP:

if(event.button.x >= posib1.x && event.button.x <= posib1.x+(*bout1)->w && event.button.y >= posib1.y && event.button.y <= posib1.y+(*bout1)->h )
{              
                

Mix_VolumeChunk(MB,0);
//*ecran = SDL_SetVideoMode(1920,1080,32,SDL_HWSURFACE | SDL_FULLSCREEN);

lancerstage(&*ecran);
*ecran = SDL_SetVideoMode(720,720,32,SDL_HWSURFACE);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
   
  SDL_Flip(*ecran);              
}
else if(event.button.x >=posib2.x && event.button.x <= posib2.x+(*bout2)->w && event.button.y >=posib2.y && event.button.y <= posib2.y+(*bout2)->h )
{                  
               Mix_PlayChannel(-1,MB,0);
                 SDL_Flip(*ecran);}
else if(event.button.x >= posib3.x && event.button.x <=posib3.x+(*bout3)->w && event.button.y >=posib3.y && event.button.y <=posib3.y+(*bout3)->h )
{
exit(0);
        
}
break;
 case SDL_MOUSEMOTION:
     if (c1==0 && c2==0 && c3==0 && c4==0){ *texte = TTF_RenderText_Blended(police, "", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte); c4=1;}

            if (event.button.x >= posib1.x && event.button.x <= posib1.x+(*bout1)->w && event.button.y >= posib1.y && event.button.y <= posib1.y+(*bout1)->h )
               {    
                 if (c1==0) {
                *bout1=SDL_LoadBMP("image/menu/p.bmp");
           
                Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Cliquer ici pour jouer", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
 c1=1; c4=0;}
}
                else{
                *bout1=SDL_LoadBMP("image/menu/play.bmp");
              SDL_BlitSurface(*bout1, NULL, *ecran, & posib1);



c1=0;
            }//else 1
              if (event.button.x >=posib2.x && event.button.x <= posib2.x+(*bout2)->w && event.button.y >=posib2.y && event.button.y <= posib2.y+(*bout2)->h) 
                 {
		 if (c2==0) {
              *bout2=SDL_LoadBMP("image/menu/oo.bmp");
      
                    Mix_PlayChannel(-1,MB,0);
*texte = TTF_RenderText_Blended(police, "Configurer le jeu ici", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);
c2=1;c4=0;}
}
               else{ *bout2=IMG_Load("image/menu/op.jpg");
                   SDL_BlitSurface(*bout2, NULL, *ecran, & posib2);

c2=0;
}//else 2
                  
	 if (event.button.x >= posib3.x && event.button.x <=posib3.x+(*bout3)->w && event.button.y >=posib3.y && event.button.y <=posib3.y+(*bout3)->h) 
                {
		 if (c3==0) {
              *bout3=SDL_LoadBMP("image/menu/e.bmp");
                    *texte = TTF_RenderText_Blended(police, "Cliquer ici pour quitter le jeu", couleur);
actualiser(&*ecran,&*imageDeFond,&*bout1,&*bout2,&*bout3,&*texte,posib1,posib2,posib3,positionFond,positexte);

                 Mix_PlayChannel(-1,MB,0);
             c3=1;c4=0;}
                    }
                else{ *bout3=SDL_LoadBMP("image/menu/exit.bmp");
                 SDL_BlitSurface(*bout3, NULL, *ecran, & posib3);
      c3=0;         
            }//else 3


SDL_Flip(*ecran);
            break;

 
	
}//switch1
	
	
}//while
}






