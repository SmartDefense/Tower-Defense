#ifndef BOUTON_H
#define BOUTON_H

#include <SDL2/SDL.h>
#include "Constantes.h"
#include "VariablesSDL.h"

class Bouton
{
    public:
        Bouton(double x,double y, double w, double h, SDL_Texture* textureBouton);

        bool clique(int xMouse, int yMouse);
        void affiche();

    protected:
        SDL_Rect dest;
        SDL_Texture* textureBouton;

};

#endif // BOUTON_H
