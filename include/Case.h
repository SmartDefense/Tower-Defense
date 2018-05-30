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
        string getType();
        int getXcentre();
        int getBlock();
        void ajouteNbPassage();
        int getNbPassage();
        int getYcentre();
        virtual void amelioration(const int typeAmelioration);

    protected:
        double distanceDepuisCentre(int x, int y);
        int x,
            y,
            block,
            nbPassage,
            xCentre,
            yCentre;
        string type;
        SDL_Rect dest;
        SDL_Texture* textureCase;

};

#endif // CASE_H
