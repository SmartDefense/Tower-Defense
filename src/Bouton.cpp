#include "Bouton.h"

Bouton::Bouton(int x,int y, int w, int h, SDL_Texture* textureBouton):
    dest({x*TAILLE_CASE, y*TAILLE_CASE, w*TAILLE_CASE, h*TAILLE_CASE}),
    textureBouton(textureBouton)
{
    //ctor
}

void Bouton::affiche(){
    SDL_RenderCopy(renderer, textureBouton, NULL, &dest);
}

bool Bouton::clique(int xMouse, int yMouse){
    return (dest.x <= xMouse
            && xMouse<=dest.x+dest.w
            && dest.y <= yMouse
            && yMouse<=dest.y+dest.h);
}
