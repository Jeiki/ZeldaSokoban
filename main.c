#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmod.h>
#include "constante.h"
#include "jeu.h"
#include <fmodex/fmod.h>

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *ecran={NULL},*fond={NULL},*bouton={NULL};
    ecran=SDL_SetVideoMode(1200,900,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    fond=IMG_Load("images/accueil.jpg");
    bouton=IMG_Load("images/bouton.png");
    SDL_Rect posFond={0},spriteBouton,posBouton;
    SDL_Event event;
    int continuer = 1,jeuContinuer=1;
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);
    FMOD_SOUND *sonBouton;
    FMOD_SOUND *musique;
    FMOD_System_CreateSound(system, "sound/LTTP_Menu_Select.wav", FMOD_CREATESAMPLE, 0, &sonBouton);
    FMOD_System_CreateSound(system,"sound/Fairy_Fountain.mp3",FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM|FMOD_LOOP_NORMAL,0,&musique);
    FMOD_CHANNEL *channel;
    FMOD_System_GetChannel(system, 1, &channel);



    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
    while (continuer&& jeuContinuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                //jeuContinuer=0;
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:

            break;
                break;
        case SDL_MOUSEBUTTONDOWN:
            //AVENTURE
            if((event.motion.x>=348 && event.motion.x<=655)&&(event.motion.y>=652 && event.motion.y <= 745))
            {
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonBouton, 0, NULL);
                transition(ecran,1,posFond);
                FMOD_Channel_SetPaused(channel,1);
                jeu();
                FMOD_Sound_Release(musique);
                FMOD_System_CreateSound(system,"sound/Fairy_Fountain.mp3",FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM|FMOD_LOOP_NORMAL,0,&musique);
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                FMOD_Channel_SetPaused(channel,0);

            }
            //EDITEUR
            else if((event.motion.x>=654 && event.motion.x<=862)&&(event.motion.y>=652 && event.motion.y <= 745))
            {
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, sonBouton, 0, NULL);
                transition(ecran,1,posFond);
                editeur(ecran);
            }
            break;
        }
        SDL_BlitSurface(fond,NULL,ecran,&posFond);
        if((event.motion.x>=348 && event.motion.x<=655)&&(event.motion.y>=652 && event.motion.y <= 745))
            {
                spriteBouton.x=0;
                spriteBouton.y=0;
                spriteBouton.w=210;
                spriteBouton.h=95;
                posBouton.x=345;
                posBouton.y=651;
                SDL_BlitSurface(bouton,&spriteBouton,ecran,&posBouton);

            }
            //EDITEUR
            else if((event.motion.x>=654 && event.motion.x<=862)&&(event.motion.y>=652 && event.motion.y <= 745))
            {
                spriteBouton.x=212;
                spriteBouton.y=0;
                spriteBouton.w=210;
                spriteBouton.h=95;
                posBouton.x=651;
                posBouton.y=651;
                SDL_BlitSurface(bouton,&spriteBouton,ecran,&posBouton);
            }
        SDL_Flip(ecran);
    }
    FMOD_Sound_Release(musique);
    FMOD_Sound_Release(sonBouton);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(fond);
    SDL_FreeSurface(bouton);
    SDL_Quit();
    return 0;
}
