#include "Bouton.h"

Bouton::Bouton(double x,double y, double w, double h, SDL_Texture* textureBouton):
    dest({int(x*TAILLE_CASE),
         int(y*TAILLE_CASE),
         int(w*TAILLE_CASE),
         int(h*TAILLE_CASE)}),
    textureBouton(textureBouton)
{
    //ctor
}

void Bouton::affiche(){
    SDL_RenderCopy(renderer, textureBouton, NULL, &dest);

    SDL_SetRenderDrawColor(renderer, 0,255,0,100);
    SDL_Point points[5] = {{dest.x, dest.y},
        {dest.x+dest.w, dest.y},
        {dest.x+dest.w, dest.y+dest.h},
        {dest.x, dest.y+dest.h},
        {dest.x, dest.y}
    };
    //SDL_RenderDrawLines(renderer, points, 5);

}

bool Bouton::clique(int xMouse, int yMouse){
    return (dest.x <= xMouse
            && xMouse<=dest.x+dest.w
            && dest.y <= yMouse
            && yMouse<=dest.y+dest.h);
}
