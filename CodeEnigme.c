
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "ENIGME.h"

void intial (enigme *en ){
int i ;
for (i=0;i<3;i++){
en->selec[i]=0 ; 
}
en->Num_try = 0 ;
}

/*******************************************************/

void intialiser_en (enigme *en ){
en->t[0]= 0 ;
en->Num_en = rand()%6+1 ;
printf ("num = %d \n",en->Num_en);
 
en->posen[0]=getrect(12,185,551,108);
en->posen[1]=getrect(48,275,551,134);
en->posen[2]=getrect(13,404,551,96);
en->posg = getrect(0,0,600,500);
switch (en->Num_en){

case 1 : 
en->menueng = convpng("fichier enigme/enigme1/enigme1.png");
en->reponse[0]=convpng("fichier enigme/enigme1/enigme1reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme1/enigme1reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme1/enigme1reponse3.png");
break ;
case 2 :
en->menueng = convpng("fichier enigme/enigme1/enigme2.png");
en->reponse[0]=convpng("fichier enigme/enigme1/enigme2reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme1/enigme2reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme1/enigme2reponse3.png");
break; 
case 3 :
en->menueng = IMG_Load("fichier enigme/enigme2/enigme3.png");
en->posen[0]=getrect(12,185,551,108);
en->reponse[0]=convpng("fichier enigme/enigme2/enigme3reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme2/enigme3reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme2/enigme3reponse3.png");
break; 
case 4 :
en->menueng = IMG_Load("fichier enigme/enigme2/enigme4.png");
en->reponse[0]=convpng("fichier enigme/enigme2/enigme4reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme2/enigme4reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme2/enigme4reponse3.png");
break ;
case 5 :
en->menueng = IMG_Load("fichier enigme/enigme3/enigme5.png");
en->reponse[0]=convpng("fichier enigme/enigme3/enigme5reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme3/enigme5reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme3/enigme5reponse3.png");
break; 
case 6 :
en->menueng = IMG_Load("fichier enigme/enigme3/enigme6.png");
en->reponse[0]=convpng("fichier enigme/enigme3/enigme6reponse1.png");
en->reponse[1]=convpng("fichier enigme/enigme3/enigme6reponse2.png");
en->reponse[2]=convpng("fichier enigme/enigme3/enigme6reponse3.png");
break ;
}
}


/****************************************/

void freeenigme(enigme *en){
int i; 
SDL_FreeSurface(en->menueng);
for(i=0;i<3;i++)
{SDL_FreeSurface(en->reponse[i];
}
}




for (i=0;i<3;i++){
SDL_FreeSurface(en->reponse[i]);
}
}
