#ifndef CASE_H
#define CASE_H

#include <SDL2/SDL.h>

class Case;

#include "Constantes.h"
#include "Variables.h"
#include "VariablesSDL.h"

class Case
{
    public:
        Case(int x, int y , int Block);
        virtual ~Case();
        virtual void affiche();
        virtual void affichePortee();
        virtual int action();
        void ajouteNbPassage();
        virtual void amelioration(const int typeAmelioration);
        string getType();
        int getXcentre();
        int getBlock();
        int getNbPassage();
        int getYcentre();

    protected:
        double distanceDepuisCentre(int x, int y);
        int x,
            y,
            block,
            nbPassage,
            xCentre,
            yCentre,
            nombreAleatoire;
        string type;
        SDL_Rect dest;
        SDL_Texture* textureCaseSimple;

};

#endif // CASE_H
