#ifndef ENNEMI_H
#define ENNEMI_H

#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
class Ennemi;

#include "Constantes.h"
#include "Variables.h"
#include "VariablesSDL.h"

class Ennemi
{
    public:
        Ennemi(int x, int y, SDL_Texture* textureEnnemi, int vie, double multiplicateurVitesse, double multiplicateurArgentMort);
        virtual ~Ennemi();
        void affiche();
        void action();
        void prendDegat(int degat);
        void appliquerEffet(const int effet, int intensite, int duree);
        int getXCentre();
        int getYCentre();

    protected:
        virtual void avance();
        void recentrage(int xCase, int yCase);
        /*virtual void direction0;
        virtual void direction1;
        virtual void direction2;
        virtual void direction3;*/
        void ajouteArgent();
        int vie,
            direction,
            vitesse,
            vieMax;
        SDL_Rect destVie,
                 destVieFond;

        SDL_Texture* textureEnnemi;
        SDL_Rect dest;
        double multiplicateurVitesse,
            multiplicateurArgentMort;
        int poison, intensitePoison;
        void remplissagePoss(int yCase ,int xCase, int poss[][2]);


};

#endif // ENNEMI_H
