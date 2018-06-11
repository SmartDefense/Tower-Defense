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
        Ennemi(int x, int y, SDL_Texture* textureEnnemi, int vie, double multiplicateurVitesse, double multiplicateurArgentMort, int vague, bool estVolant,int xChateau,int yChateau,int type);
        virtual ~Ennemi();
        void affiche();
        void action();
        void prendDegat(int degat);
        void appliquerEffet(const int effet, int intensite, int duree);
        int getXCentre();
        int getYCentre();
        int getXCentreFutur(int images);
        int getYCentreFutur(int images);
        int getPrediction();
        int getVie();
        bool getAerien();
        void ajouteCaseParcours();


    protected:
        virtual void avance();
        void recentrage(int xCase, int yCase);
        /*virtual void direction0;
        virtual void direction1;
        virtual void direction2;
        virtual void direction3;*/
        void ajouteArgent();
        void enregistrerPoss(int yCase, int xCase);
        void remplissagePoss(int yCase ,int xCase, int poss[][2]);

        int vie,
            vieMax,
            direction,
            compteurPoison,
            compteurEffet,
            angle,
            intensitePoison,
            numImage,
            type,
            xChateau,
            yChateau;
        double multiplicateurVitesse,
            multiplicateurArgentMort,
            x,
            y,
            vitesse,
            dX,
            dY;
        bool estAerien;
        SDL_Rect destVie,
                 destVieFond;
        SDL_Texture* textureEnnemi;
        vector<pair<int,int>> listePoss;


};

#endif // ENNEMI_H
