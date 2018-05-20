#ifndef TIR_H
#define TIR_H

#include <SDL2/SDL.h>

class Tir;

#include "Constantes.h"
#include "Variables.h"
#include "VariablesSDL.h"

class Tir
{
    public:
        Tir(int x, int y, double dX, double dY, SDL_Texture* textureTir, int angle, int degat);
        virtual ~Tir();
        void affiche();
        void action();
        void avance();
        virtual void degatEnnemi(int idEnnemi);

    protected:
        SDL_Texture* textureTir;
        int degat,
            angle;
        double x,
            y,
            dX,
            dY;


};

#endif // TIR_H
