#include "Chemin.h"
#include <SDL2/SDL_ttf.h>


Chemin::Chemin(int x, int y, int block):
    Case(x, y, block),
    vitesseDeplacement(1)
{
    Case::textureCaseFond=::textureChemin;
    Case::type="Chemin";
    //cout<<"Creation :\t Chemin ("<<x<<","<<y<<")"<<endl;
}

Chemin::~Chemin(){
    //cout<<"Destruction :\t Chemin ("<<x<<","<<y<<")"<<endl;
}
TTF_Font *font2;
void Ecrire2(string police, int taille, string texte, int r, int v, int b, int x, int y)
{
    font2 = TTF_OpenFont(("fonts/" + police + ".ttf").c_str(), taille);
    SDL_Color color = { r, v, b };
    SDL_Surface * surface = TTF_RenderText_Blended(font2,texte.c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 200;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font2);
}
void Chemin::affiche()
{
    Case::affiche();
    //Ecrire2("Arial", 15, to_string(nbPassage), 0,0,0,dest.x, dest.y);
}

int Chemin::action()
{
    return -1;
}

void Chemin::amelioration(const int typeAmelioration)
{

}

int Chemin::getVitesseDeplacement()
{
    return vitesseDeplacement;
}

