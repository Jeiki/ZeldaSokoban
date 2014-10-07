#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmod.h>
#include "constante.h"


void transition(SDL_Surface *ecran, int typeTransition)
{
    SDL_Surface *transition,*screen=NULL;
    SDL_Rect posTransGauche,posTransDroite;
    transition=SDL_CreateRGBSurface(SDL_HWSURFACE, 15, ecran->h, 32, 0, 0, 0, 0);
    SDL_FillRect(transition, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    posTransGauche.x=0;
    posTransGauche.y=0;
    posTransDroite.x=ecran->w-transition->w;
    posTransDroite.y=0;
    SDL_SaveBMP(ecran,"images/tmpScreen.bmp");


    int tempAct=0, tempPrec=0;


    switch (typeTransition)
    {
    case verticFermer:
        while(posTransGauche.x!= ecran->w/2)
        {
            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>20)
            {
                SDL_BlitSurface(transition,NULL,ecran,&posTransGauche);SDL_BlitSurface(transition,NULL,ecran,&posTransDroite);
                posTransGauche.x+=transition->w;posTransDroite.x-=transition->w;
                SDL_Flip(ecran);
                tempPrec=tempAct;
            }
            else{SDL_Delay(20-(tempAct-tempPrec));}
        }
        break;
    case verticOuvert:
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        posTransGauche.x=ecran->w/2-transition->w;
        posTransGauche.y=0;

        posTransDroite.x=ecran->w/2;
        posTransDroite.y=0;

        posTransGauche.w=transition->w;
        posTransDroite.w=transition->w;
        posTransGauche.h=transition->h;
        posTransDroite.h=transition->h;
        screen=SDL_LoadBMP("images/tmpScreen.bmp");
        while(posTransGauche.x)
        {
            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>20)
            {
                SDL_BlitSurface(screen,&posTransDroite,ecran,&posTransDroite);SDL_BlitSurface(screen,&posTransGauche ,ecran,&posTransGauche);
                SDL_Flip(ecran);
                posTransDroite.x+=transition->w;posTransGauche.x-=transition->w;
                tempPrec=tempAct;
            }
            else{SDL_Delay(20-(tempAct-tempPrec));}
        }
        break;
    case vertic:
        posTransGauche.x=0;
        posTransGauche.y=0;
        while(posTransGauche.x< ecran->w)
        {
            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>10)
            {
                SDL_BlitSurface(transition,NULL,ecran,&posTransGauche);
                posTransGauche.x+=transition->w;
                SDL_Flip(ecran);
                tempPrec=tempAct;
            }
            else{SDL_Delay(10-(tempAct-tempPrec));}
        }
        break;
    case verticSuite:
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        posTransGauche.x=0;
        posTransGauche.w=transition->w;
        posTransGauche.h=transition->h;
        screen=SDL_LoadBMP("images/tmpScreen.bmp");
        while(posTransGauche.x<ecran->w)
        {
            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>10)
            {
                SDL_BlitSurface(screen,&posTransGauche ,ecran,&posTransGauche);
                SDL_Flip(ecran);
                posTransGauche.x+=transition->w;
                tempPrec=tempAct;
            }
            else{SDL_Delay(10-(tempAct-tempPrec));}
        }

        break;
    }
    SDL_FreeSurface(transition);
    if(screen!=NULL)
    {
        SDL_FreeSurface(screen);
    }else;

}

void deplacement(SDL_Surface *ecran,int direction, SDL_Rect posLink)
{
    int tempAct=0,tempPrec=0,continuer=1,savePos=0,i=1;
    SDL_Surface *link[3]= {NULL}, screen;
    link[0]=IMG_Load("images/link.png");
    link[1]=IMG_Load("images/link2.png");
    link[2]=IMG_Load("images/link3.png");

   switch (direction)
    {
    case 1:

        break;
    case 2:
        savePos=posLink.y;
        while(posLink.y<savePos+50)
        {
            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>100)
            {
                SDL_BlitSurface(link[i],NULL,ecran,&posLink);
                SDL_Flip(ecran);
                posLink.y+=10;
                tempPrec=tempAct;
                if(i<=1)
                {
                    i++;
                }
                else
                {
                    i=0;
                }
            }
            else
            {
                SDL_Delay(100-(tempAct-tempPrec));
            }

        }

        break;
    case 3:

        break;
    case 4:

        break;
    }




    SDL_FreeSurface(link[0]);
    SDL_FreeSurface(link[1]);
    SDL_FreeSurface(link[2]);
}
