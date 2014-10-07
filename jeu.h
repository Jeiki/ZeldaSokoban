#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED


void jeu();
int checkIfWin(SDL_Rect posCoffre[180],SDL_Rect posInt[180],int nbrCoffre);
void animationEnvole(SDL_Surface *ecran, SDL_Rect posLink);
void transition(SDL_Surface *ecran,int sens,SDL_Rect posLink);
void initialisation(char plan[24][15],SDL_Rect *posLink, SDL_Rect posCoffre[180],int *nbrCoffre,SDL_Rect posInt[180],int lvl);
int verification(int deplacement,char plan[24][15], SDL_Rect *posCoffreID);
int animation(int nextLvl,SDL_Rect posLink,SDL_Rect imageLink,int avancer,SDL_Rect *posCoffre,SDL_Rect *posInt,int nbrCoffre,char plan[24][15],SDL_Surface *ecran,SDL_Surface *fond,SDL_Surface *link,SDL_Surface *coffre,SDL_Surface *interupteur,SDL_Surface *mur,SDL_Surface *reset, int curseurReset);

#endif // JEU_H_INCLUDED
