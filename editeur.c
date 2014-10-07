#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL_image.h>
#include <fmod.h>
#include "constante.h"
#include "jeu.h"
#include <fmodex/fmod.h>

void editeur(SDL_Surface *ecran)
{
    SDL_Surface *fond,*link,*mur,*coffre,*interrupteur,*barre;
    fond = IMG_Load("images/fondEditeur.jpg");
    link = IMG_Load("images/link.png");
    mur = IMG_Load("images/mur.jpg");
    coffre = IMG_Load("images/coffre.jpg");
    interrupteur = IMG_Load("images/interrupteur.jpg");
    barre = IMG_Load("images/barre.png");
    SDL_Rect posBarre;
    posBarre.x=(ecran->w/2)-(barre->w/2);
    posBarre.y=ecran->h-barre->h;
    SDL_Event event;
    int continuer=1;
    char plan[24][15];

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button)

            break;

        }
        SDL_BlitSurface(fond,NULL,ecran,NULL);
        SDL_BlitSurface(barre,NULL,ecran,&posBarre);
        SDL_Flip(ecran);

    }


}
