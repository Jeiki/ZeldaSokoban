#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmod.h>
#include "constante.h"
#include <fmodex/fmod.h>
#include "jeu.h"

void jeu()
{
    int pool, andgo;
    SDL_Surface *ecran={NULL},*fond={NULL},*link={NULL},*coffre={NULL},*interupteur={NULL},*mur={NULL},*reset={NULL};
    ecran=SDL_SetVideoMode(1200,900,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    fond=IMG_Load("images/fond.jpg");
    link=IMG_Load("images/link.png");
    coffre=IMG_Load("images/coffre.jpg");
    interupteur=IMG_Load("images/interupteur.jpg");
    mur=IMG_Load("images/mur.jpg");
    reset=IMG_Load("images/reset.png");
    SDL_Rect imageLink,posLink, posCoffre[180], posInt[180],posFond,posCoffreID;
    imageLink.w=50;
    imageLink.h=61;
    imageLink.x=0;
    imageLink.y=85;
    posFond.x=0;
    posFond.y=0;

    SDL_Event event;
    int quitter=0,i,j,k,nbrCoffre=0, tempAct=0,tempPrec=0,avancer=0,lvl=1,temps=0, curseurReset=0;
    char plan[24][15];
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 5, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *coffrePlacer;
    FMOD_SOUND *ocarina;
    FMOD_SOUND *musique;
    FMOD_SOUND *sonReset;
    FMOD_System_CreateSound(system,"sound/ocarina.wav",FMOD_CREATESAMPLE,0,&ocarina);
    FMOD_System_CreateSound(system, "sound/LTTP_Switch.wav", FMOD_CREATESAMPLE, 0, &coffrePlacer);
    FMOD_System_CreateSound(system, "sound/Inside_a_House.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM|FMOD_LOOP_NORMAL, 0, &musique);
    FMOD_System_CreateSound(system, "sound/LTTP_Text_Done.wav", FMOD_CREATESAMPLE, 0, &sonReset);

    FMOD_CHANNEL *channel;


    FMOD_System_PlaySound(system, 0, musique, 0, NULL);
    FMOD_System_GetChannel(system, 0, &channel);
    initialisation(plan,&posLink,posCoffre,&nbrCoffre,posInt,lvl);



    animation(1,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
    transition(ecran,2,posLink);

    SDL_EnableKeyRepeat(1,1);

    while (quitter==0)
    {
        while(SDL_PollEvent(&event));
        switch(event.type)
        {
        case SDL_QUIT:
            quitter=1;
            break;
            case SDL_KEYUP:
            avancer=0;
            break;
        case SDL_KEYDOWN:
            avancer=1;
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quitter=1;
                break;
            case SDLK_UP:
                if(verification(haut,plan,&posCoffreID))
                {
                    i=posLink.y-50;
                    while(posLink.y>i)
                    {
                        imageLink.y=12;
                        tempAct=SDL_GetTicks();
                        if(tempAct-tempPrec>30)
                        {
                            imageLink.x+=imageLink.w;
                            if (imageLink.x>=imageLink.w*11)
                            {
                                imageLink.x=imageLink.w;
                            }
                            tempPrec=tempAct;
                        }
                        else
                        {
                            SDL_Delay(30-(tempAct-tempPrec));
                        }
                        temps++;
                        posLink.y-=5;
                        for(j=0;j!=nbrCoffre;j++)
                        {
                            if(posCoffreID.x==posCoffre[j].x && posCoffreID.y==posCoffre[j].y)
                            {
                                posCoffre[j].y-=2;
                                posCoffreID.y-=2;
                                posLink.y+=3;
                                for(k=0;k!=nbrCoffre;k++)
                                {
                                    if(posCoffre[j].x==posInt[k].x && posCoffre[j].y==posInt[k].y)
                                    {
                                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, coffrePlacer, 0, NULL);
                                    }
                                }
                            }
                        }
                        animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
                    }
                }
                else
                {
                    imageLink.y=12;
                }
                break;
            case SDLK_DOWN:
                if(verification(bas,plan,&posCoffreID))
                {
                    i=posLink.y+50;
                    while(posLink.y<i)
                    {
                        imageLink.y=85;
                        tempAct=SDL_GetTicks();
                        if(tempAct-tempPrec>30)
                        {
                            imageLink.x+=imageLink.w;

                            if (imageLink.x>=imageLink.w*11)
                            {
                                imageLink.x=imageLink.w;
                            }
                            tempPrec=tempAct;
                        }
                        else
                        {
                            SDL_Delay(30-(tempAct-tempPrec));
                        }
                        temps++;
                        posLink.y+=5;
                        for(j=0;j!=nbrCoffre;j++)
                        {
                            if(posCoffreID.x==posCoffre[j].x && posCoffreID.y==posCoffre[j].y)
                            {
                                posCoffre[j].y+=2;
                                posCoffreID.y+=2;
                                posLink.y-=3;
                                for(k=0;k!=nbrCoffre;k++)
                                {
                                    if(posCoffre[j].x==posInt[k].x && posCoffre[j].y==posInt[k].y)
                                    {
                                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, coffrePlacer, 0, NULL);
                                    }
                                }
                            }
                        }

                        animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
                    }
                }
                else
                {
                    imageLink.y=85;
                }
                break;
            case SDLK_LEFT:
                if(verification(gauche,plan,&posCoffreID))
                {
                    i=posLink.x-50;
                    while(posLink.x>i)
                    {
                        imageLink.y=158;
                        tempAct=SDL_GetTicks();
                        if(tempAct-tempPrec>30)
                        {
                            imageLink.x-=imageLink.w;

                            if (imageLink.x<imageLink.w)
                            {
                                imageLink.x=imageLink.w*10;
                            }
                            tempPrec=tempAct;
                        }
                        else
                        {
                            SDL_Delay(30-(tempAct-tempPrec));
                        }
                        temps++;
                        posLink.x-=5;
                        for(j=0;j!=nbrCoffre;j++)
                        {
                            if(posCoffreID.x==posCoffre[j].x && posCoffreID.y==posCoffre[j].y)
                            {
                                posCoffre[j].x-=2;
                                posCoffreID.x-=2;
                                posLink.x+=3;
                                for(k=0;k!=nbrCoffre;k++)
                                {
                                    if(posCoffre[j].x==posInt[k].x && posCoffre[j].y==posInt[k].y)
                                    {
                                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, coffrePlacer, 0, NULL);
                                    }
                                }
                            }
                        }
                        animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
                    }
                }
                else
                {
                    imageLink.y=158;
                }
                break;
            case SDLK_RIGHT:
                if(verification(droite,plan,&posCoffreID))
                {
                    i=posLink.x+50;
                    while(posLink.x<i)
                    {
                        imageLink.y=231;
                        tempAct=SDL_GetTicks();
                        if(tempAct-tempPrec>30)
                        {
                            imageLink.x+=imageLink.w;
                            if (imageLink.x>=imageLink.w*11)
                            {
                                imageLink.x=imageLink.w;
                            }
                            tempPrec=tempAct;
                        }
                        else
                        {
                            SDL_Delay(30-(tempAct-tempPrec));
                        }
                        temps++;
                        posLink.x+=5;
                        for(j=0;j!=nbrCoffre;j++)
                        {
                            if(posCoffreID.x==posCoffre[j].x && posCoffreID.y==posCoffre[j].y)
                            {
                                posCoffre[j].x+=2;
                                posCoffreID.x+=2;
                                posLink.x-=3;
                                for(k=0;k!=nbrCoffre;k++)
                                {
                                    if(posCoffre[j].x==posInt[k].x && posCoffre[j].y==posInt[k].y)
                                    {
                                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, coffrePlacer, 0, NULL);
                                    }
                                }
                            }
                        }
                        animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
                    }
                }
                else
                {
                    imageLink.y=231;
                }
                break;
            default:break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.motion.x>=(ecran->w/2)-(reset->w/2) && event.motion.x<=(ecran->w/2)+(reset->w/2)&& event.motion.y>=ecran->h-reset->h-30 && event.motion.y<=ecran->h-30)
            {
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonReset, 0, NULL);
                nbrCoffre=0;
                imageLink.y=85;
                initialisation(plan,&posLink,posCoffre,&nbrCoffre,posInt,lvl);
                animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
            }
            break;
        case SDL_MOUSEMOTION:
            if(event.motion.x>=(ecran->w/2)-(reset->w/2) && event.motion.x<=(ecran->w/2)+(reset->w/2)&& event.motion.y>=ecran->h-reset->h-30 && event.motion.y<=ecran->h-30)
            {
                curseurReset=1;
            }
            else
            {
                curseurReset=0;
            }
            break;

        }
        posCoffreID.x=0;
        posCoffreID.y=0;
        //si link est a l'arret
        if(avancer==0)
        {
            animation(NULL,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
        }
        //verification de victoire
        if(checkIfWin(posCoffre,posInt,nbrCoffre)==0)
        {
            FMOD_Channel_SetPaused(channel,1);
            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, ocarina, 0, NULL);
            animation(1,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
            animationEnvole(ecran,posLink);
            transition(ecran,1,posLink);
            FMOD_Channel_SetPaused(channel,0);
            lvl++;
            nbrCoffre=0;
            imageLink.y=85;
            initialisation(plan,&posLink,posCoffre,&nbrCoffre,posInt,lvl);
            animation(1,posLink,imageLink,avancer,&posInt,&posCoffre,nbrCoffre,plan,ecran,fond,link,coffre,interupteur,mur,reset,curseurReset);
            transition(ecran,2,posLink);
        }

    }
    FMOD_Sound_Release(sonReset);
    FMOD_Sound_Release(musique);
    FMOD_Sound_Release(ocarina);
    FMOD_Sound_Release(coffrePlacer);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(link);
    SDL_FreeSurface(coffre);
    SDL_FreeSurface(interupteur);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(reset);
}

void transition(SDL_Surface *ecran,int sens, SDL_Rect posLink)
{
    int tempAct=0,tempPrec=0,temps=0;
    SDL_Surface *link;
    link=IMG_Load("images/oiseau.png");
    SDL_Surface *screen, *collonne;
    SDL_Rect posCollonne, animLink,posLinkTemp;
    posCollonne.x=0;
    posCollonne.y=0;
    posCollonne.w=30;
    posCollonne.h=900;
    screen=IMG_Load("image/screen.bmp");
    collonne=SDL_CreateRGBSurface(SDL_HWSURFACE,30,900,32,0,0,0,0);
    SDL_FillRect(collonne,NULL,SDL_MapRGB(ecran->format,0,0,0));
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 5, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *fly;
    FMOD_System_CreateSound(system,"sound/fly.wav",FMOD_CREATESAMPLE,0,&fly);

    switch (sens)
    {
    case 1:
        while(posCollonne.x<=ecran->w)
        {
            SDL_BlitSurface(screen,NULL,ecran,NULL);
            SDL_BlitSurface(collonne,NULL,ecran,&posCollonne);
            SDL_Flip(ecran);

            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>30)
            {
                posCollonne.x+=collonne->w;
                tempPrec=tempAct;
            }
            else
            {
                SDL_Delay(30-(tempAct-tempPrec));
            }

        }
        break;
    case 2:
        screen=IMG_Load("images/screen.bmp");
        SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
        while(posCollonne.x<=ecran->w)
        {
            SDL_BlitSurface(screen,&posCollonne,ecran,&posCollonne);
            SDL_Flip(ecran);

            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>30)
            {
                posCollonne.x+=collonne->w;
                tempPrec=tempAct;
            }
            else
            {
                SDL_Delay(30-(tempAct-tempPrec));
            }
        }
        posCollonne.x=0;
        posCollonne.y=posLink.y-70;
        posLinkTemp.x=365;
        posLinkTemp.y=51;
        animLink.y=0;
        animLink.x=541;
        animLink.w=60;
        animLink.h=109;
        posLinkTemp.w=60;
        posLinkTemp.h=109;
        while(posCollonne.x<=posLink.x)
        {
            SDL_BlitSurface(screen,NULL,ecran,NULL);
            SDL_BlitSurface(link,&animLink,ecran,&posCollonne);
            SDL_Flip(ecran);

            tempAct=SDL_GetTicks();
            if(tempAct-tempPrec>30)
            {
                posCollonne.x+=30;
                animLink.x+=60;
                tempPrec=tempAct;
                if(animLink.x>=660)
                {
                    animLink.x=541;
                }
            }
            else
            {
                SDL_Delay(30-(tempAct-tempPrec));
            }
            temps++;
            switch(temps)
            {
            case 1:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            case 31:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            case 61:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            case 121:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            case 181:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            case 241:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
            }
        }

        if(posCollonne.x>posLink.x)
        {
            posCollonne.y-=20;
            animLink.x+=60;
            while(posCollonne.x<=ecran->w)
            {
                SDL_BlitSurface(screen,NULL,ecran,NULL);
                SDL_BlitSurface(link,&animLink,ecran,&posCollonne);
                SDL_BlitSurface(link,&posLinkTemp,ecran,&posLink);

                SDL_Flip(ecran);

                tempAct=SDL_GetTicks();
                if(tempAct-tempPrec>30)
                {
                    posCollonne.x+=30;
                    animLink.x+=60;
                    tempPrec=tempAct;
                    if(animLink.x>=840)
                    {
                        animLink.x=661;
                    }
                }
                else
                {
                    SDL_Delay(30-(tempAct-tempPrec));
                }
                temps++;
                switch(temps)
                {
                case 1:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
                case 31:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
                case 61:FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);break;
                }

            }
        }
        break;
    }

    FMOD_Sound_Release(fly);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface(screen);
    SDL_FreeSurface(collonne);
}
void animationEnvole(SDL_Surface *ecran, SDL_Rect posLink)
{
    int temps=0;
    SDL_Surface *oiseau=NULL,*linkOiseau=NULL,*screen;
    SDL_Rect posOiseau,posAnimOiseau, posAnimLinkOiseau;
    posLink.y=posLink.y-52;
    posOiseau.x=0;
    posOiseau.y=posLink.y;
    posAnimOiseau.x=661;
    posAnimOiseau.y=0;
    posAnimOiseau.w=60;
    posAnimOiseau.h=109;
    posAnimLinkOiseau.x=0;
    posAnimLinkOiseau.y=0;
    posAnimLinkOiseau.w=60;
    posAnimLinkOiseau.h=109;
    int tempAct=0,tempPrec=0;
    linkOiseau=IMG_Load("images/oiseau.png");
    screen=IMG_Load("images/screen.bmp");
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 5, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *fly;
    FMOD_System_CreateSound(system,"sound/fly.wav",FMOD_CREATESAMPLE,0,&fly);


    while(posOiseau.x<ecran->w)
    {
        tempAct=SDL_GetTicks();
        if(temps<=15)// link sort son ocarina et joue
        {
            if(tempAct-tempPrec>120)
            {
                posAnimLinkOiseau.x+=60;
                if(posAnimLinkOiseau.x>=240)
                {
                    posAnimLinkOiseau.x=120;
                }
                tempPrec=tempAct;

            }
            else
            {
                SDL_Delay(120-(tempAct-tempPrec));
            }
            temps++;
        }
        else if (temps>15 && temps<=19)// link range son ocarina
        {
            if(tempAct-tempPrec>120)
            {
                posAnimLinkOiseau.x+=60;
                tempPrec=tempAct;
            }
            else
            {
                SDL_Delay(120-(tempAct-tempPrec));
            }
            temps++;
        }
        else if (temps>19 && temps<=21)
        {
            if(tempAct-tempPrec>120)
            {
            }
            else
            {
                SDL_Delay(120-(tempAct-tempPrec));
            }
            temps++;
        }
        else if(temps>21 && posOiseau.x<posLink.x)//oiseau arrive
        {
            if(oiseau==NULL)
            {
                oiseau=IMG_Load("images/oiseau.png");
            }

            if(tempAct-tempPrec>30)
            {
                posAnimOiseau.x+=60;
                posOiseau.x+=30;
                tempPrec=tempAct;
                if(posAnimOiseau.x>=840)
                {
                    posAnimOiseau.x=661;
                }
            }
            else
            {
                SDL_Delay(30-(tempAct-tempPrec));
            }
            temps++;
        }
        if(posOiseau.x>=posLink.x-100 && posOiseau.x<posLink.x)
        {
            posAnimLinkOiseau.x=421;
            if (posOiseau.x>=posLink.x-10 && posOiseau.x<posLink.x)
            {
                posAnimLinkOiseau.x=481;
            }
        }

        else if(posOiseau.x>=posLink.x)
        {
            linkOiseau=NULL;
            if(tempAct-tempPrec>30)
            {
                posAnimOiseau.x+=60;
                posOiseau.x+=30;
                tempPrec=tempAct;
                if(posAnimOiseau.x>=660)
                {
                    posAnimOiseau.x=541;
                }
            }
            else
            {
                SDL_Delay(30-(tempAct-tempPrec));
            }
            temps++;


        }
        switch(temps)
            {
            case 23:
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);
                break;
            case 53:
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);
                break;
            case 83:
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, fly, 0, NULL);
                break;
            }


        SDL_BlitSurface(screen,NULL,ecran,NULL);
        SDL_BlitSurface(oiseau,&posAnimOiseau,ecran,&posOiseau);
        SDL_BlitSurface(linkOiseau,&posAnimLinkOiseau,ecran,&posLink);
        SDL_Flip(ecran);
    }

    FMOD_Sound_Release(fly);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface(oiseau);
    SDL_FreeSurface(linkOiseau);
    SDL_FreeSurface(screen);


}

int checkIfWin(SDL_Rect posCoffre[180],SDL_Rect posInt[180],int nbrCoffre)
{
    int i,j, reste=0;
    reste=nbrCoffre;

    for(i=0;i!=nbrCoffre;i++)
    {
        for(j=0;j!=nbrCoffre;j++)
        {
            if (posCoffre[i].x == posInt[j].x && posCoffre[i].y == posInt[j].y)
            {
                reste--;
            }
        }

    }
    return reste;
}

int animation(int nextLvl,SDL_Rect posLink,SDL_Rect imageLink,int avancer,SDL_Rect *posInt,SDL_Rect *posCoffre,int nbrCoffre,char plan[24][15],SDL_Surface *ecran,SDL_Surface *fond,SDL_Surface *link,SDL_Surface *coffre,SDL_Surface *interupteur,SDL_Surface *mur,SDL_Surface *reset,int curseurReset)
{
    int i,j;
    SDL_Rect posPlan,posReset;
    posReset.x=(ecran->w/2)-(reset->w/2);
    posReset.y=ecran->h-reset->h-30;
    SDL_BlitSurface(fond,NULL,ecran,NULL);
    //BLIT MUR
    for(i=0;i!=24;i++)
    {
        for(j=0;j!=15;j++)
        {
            posPlan.x=i*50;
            posPlan.y=j*50;
            if(plan[i][j]==2)
            {
                SDL_BlitSurface(mur,NULL,ecran,&posPlan);
            }
            else if (plan[i][j]==1)
            {
               //SDL_BlitSurface(coffre,NULL,ecran,&posPlan);
            }
            else if (plan[i][j]==4)
            {
               //SDL_BlitSurface(link,&imageLink,ecran,&posPlan);
            }
        }
    }
    //BLIT INTERUPTEUR
    for(i=0;i!=nbrCoffre;i++)
    {
        SDL_BlitSurface(interupteur,NULL,ecran,&posInt[i]);
    }
    //BLIT COFFRE
    for(i=0;i!=nbrCoffre;i++)
    {
        SDL_BlitSurface(coffre,NULL,ecran,&posCoffre[i]);
    }
    //BLIT LINK
    if(avancer==0)
    {
        imageLink.x=0;
    }
    if(nextLvl==NULL)
    {
        SDL_BlitSurface(link,&imageLink,ecran,&posLink);
    }
    else
    {
        SDL_SaveBMP(ecran,"images/screen.bmp");
        SDL_BlitSurface(link,&imageLink,ecran,&posLink);
    }
    if(curseurReset==1)
    {
        SDL_BlitSurface(reset,NULL,ecran,&posReset);
    }

    if(nextLvl==NULL)
    {
        SDL_Flip(ecran);
    }

    return 0;
}

int verification(int deplacement,char plan[24][15], SDL_Rect *posCoffreID)
{
    int i,j,ok=1;
    for(i=0;i!=24;i++)
    {
        for(j=0;j!=15;j++)
        {
            if(plan[i][j]==4)
            {
                switch(deplacement)
                {
                case haut:
                    switch(plan[i][j-1])
                    {
                    case 0://vide
                        plan[i][j-1]=4;
                        plan[i][j]=0;
                        break;
                    case 1://coffre
                        if(plan[i][j-2]==0 ||plan[i][j-2]==3)
                        {
                            plan[i][j-2]=1;
                            plan[i][j-1]=4;
                            plan[i][j]=0;
                            posCoffreID->x=i*50;
                            posCoffreID->y=(j*50)-50;
                        }
                        else
                        {
                            ok=0;
                        }
                        break;
                    case 2://mur
                        ok=0;
                        break;
                    case 3://interupteur
                        plan[i][j-1]=4;
                        plan[i][j]=0;
                        break;
                    default:
                        break;
                    }
                    break;
                case bas:
                    switch(plan[i][j+1])
                    {
                    case 0://vide
                        plan[i][j+1]=4;
                        plan[i][j]=0;
                        j++;
                        break;
                    case 1://coffre
                        if(plan[i][j+2]==0 ||plan[i][j+2]==3)
                        {
                            plan[i][j+2]=1;
                            plan[i][j+1]=4;
                            plan[i][j]=0;
                            posCoffreID->x=i*50;
                            posCoffreID->y=(j*50)+50;
                            j+=3;
                        }
                        else
                        {
                            ok=0;
                        }
                        break;
                    case 2://mur
                        ok=0;
                        break;
                    case 3://interupteur
                        plan[i][j+1]=4;
                        plan[i][j]=0;
                        j++;
                        break;
                    default:
                        break;
                    }
                    break;
                case gauche:
                    switch(plan[i-1][j])
                    {
                    case 0://vide
                        plan[i-1][j]=4;
                        plan[i][j]=0;
                        break;
                    case 1://coffre
                        if(plan[i-2][j]==0 ||plan[i-2][j]==3)
                        {
                            plan[i-2][j]=1;
                            plan[i-1][j]=4;
                            plan[i][j]=0;
                            posCoffreID->x=(i*50)-50;
                            posCoffreID->y=j*50;
                        }
                        else
                        {
                            ok=0;
                        }
                        break;
                    case 2://mur
                        ok=0;
                        break;
                    case 3://interupteur
                        plan[i-1][j]=4;
                        plan[i][j]=0;
                        break;
                    default:
                        break;
                    }
                    break;
                case droite:
                    switch(plan[i+1][j])
                    {
                    case 0://vide
                        plan[i][j]=0;
                        plan[i+1][j]=4;
                        i++;
                        break;
                    case 1://coffre
                        if(plan[i+2][j]==0 ||plan[i+2][j]==3)
                        {
                            plan[i+2][j]=1;
                            plan[i+1][j]=4;
                            plan[i][j]=0;
                            posCoffreID->x=(i*50)+50;
                            posCoffreID->y=j*50;
                            i+=3;
                        }
                        else
                        {
                            ok=0;
                        }
                        break;
                    case 2://mur
                        ok=0;
                        break;
                    case 3://interupteur
                        plan[i][j]=0;
                        plan[i+1][j]=4;
                        i++;
                        break;
                    default:
                        break;
                    }
                    break;
                }
            }
        }
    }
    return ok;
}

void initialisation(char plan[24][15],SDL_Rect *posLink, SDL_Rect posCoffre[180],int *nbrCoffre,SDL_Rect posInt[180],int lvl)
{
    int i,j,k=0,l=0,m;
    FILE *fichier;
    fichier=fopen("save.txt","r+");
    for(m=0;m!=lvl;m++)
    {
        *nbrCoffre=0;
        k=0;
        l=0;
        for (i=0;i!=24;i++)
        {
            for (j=0;j!=15;j++)
            {
                fscanf(fichier,"%d",&plan[i][j]);
                switch(plan[i][j])
                {
                case 4://LINK
                    posLink->x=i*50;
                    posLink->y=j*50-11;
                    break;
                case 1://COFFRE
                    posCoffre[k].x=i*50;
                    posCoffre[k].y=j*50;
                    k++;
                    break;
                case 3://INTERUPTEUR
                    posInt[l].x=i*50;
                    posInt[l].y=j*50;
                    l++;
                    break;
                }
            }
        }
        *nbrCoffre=k;
    }

    fclose(fichier);
}
