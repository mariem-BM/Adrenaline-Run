

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "test.h"
#include "quitscreen.h"
#include "menu.h"


void quitscreen(SDL_Surface* bg,SDL_Surface *screen,personnage p,SDL_Rect camera)
{
	SDL_Surface* nomo=IMG_Load("quit2.png");
	SDL_Surface* yesmo=IMG_Load("quit3.png");
	SDL_Surface* native=IMG_Load("quit1.png");
	SDL_Surface* question=IMG_Load("question.png");
	FILE* f=NULL;
	int continuer=1;
	apply_surface(0,0,bg,screen);
	apply_surface(140,220,native,screen);
	apply_surface(190,120,question,screen);
	SDL_Flip(screen);
	SDL_Event event;
	while(continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_MOUSEMOTION : 
			{
				if(event.motion.x>150 && event.motion.x<280 && event.motion.y>220 && event.motion.y<264)
				{
					apply_surface(0,0,bg,screen);
					apply_surface(140,220,nomo,screen);
					apply_surface(190,120,question,screen);
					SDL_Flip(screen);
				}
				else if(event.motion.x>300 && event.motion.x<430 && event.motion.y>220 && event.motion.y<264)
				{
					apply_surface(0,0,bg,screen);
					apply_surface(140,220,yesmo,screen);
					apply_surface(190,120,question,screen);
					SDL_Flip(screen);
				}
				else 
				{
					apply_surface(0,0,bg,screen);
					apply_surface(140,220,native,screen);
					apply_surface(190,120,question,screen);
					SDL_Flip(screen);
				}
			}
			break;
			case SDL_KEYDOWN :
			{
				if(event.key.keysym.sym==SDLK_q)
				{
					continuer=0;
				}
			}
			break;
			case SDL_MOUSEBUTTONDOWN :
			{
				if(event.button.x>150 && event.button.x<280 && event.button.y>220 && event.button.y<264)
				{
					continuer=0;
					menu(bg,screen);
					/** 
				   *  @elseif if "Quit without saving" is clicked
				   *    Go back to menu.
				   *  @endif
				   */
				}
				else if(event.button.x>300 && event.button.x<430 && event.button.y>220 && event.button.y<264)
				{
					f=fopen("savedgame.txt","w");
					fprintf(f,"%d %d %d \n",p.position.x,p.position.y,camera.x);
					fclose(f);
					continuer=0;
					menu(bg,screen);
					/** 
				   *  @elseif if "Save and quit" is clicked
				   *    Open file in write mode.
				   *    write the current game state.
				   *	close the file.
				   *	go back to menu. 
				   *  @endif
				 */
				}}
			
			break;
		}
	}
}
