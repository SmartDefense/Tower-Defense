#include "Tir.h"
#include "math.h"

Tir::Tir(int x, int y, double dX, double dY, SDL_Texture* textureTir, int angle, int degat):
    x(x),
    y(y),
    dX(dX),
    dY(dY),
    degat(degat),
    angle(angle),
    textureTir(textureTir)
{
    //cout<<"Creation :\t Tir ("<<x<<","<<y<<")"<<endl;
}

Tir::~Tir(){
    //cout<<"Destruction :\t Tir ("<<x<<","<<y<<")"<<endl;
    for(int i=0;i<listeTirs.size();i++){
        if(listeTirs[i]==this){
            listeTirs.erase(listeTirs.begin()+i);
        }
    }
}

void Tir::affiche()
{
    SDL_Rect dest = {(int)(x+0.5), (int)(y+0.5), TAILLE_X_TIR, TAILLE_Y_TIR};
    SDL_RenderCopyEx(renderer, textureTir, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Tir::action()
{
    x+=dX;
    y+=dY;
    for(int i=0; i<listeEnnemis.size();i++){
        int xEnnemi=listeEnnemis[i]->getXCentre();
        int yEnnemi=listeEnnemis[i]->getYCentre();
        if(sqrt(pow(y+TAILLE_Y_TIR/2-yEnnemi,2)+pow(x+TAILLE_X_TIR/2-xEnnemi,2))<TAILLE_ENNEMI/2){
            degatEnnemi(i);
            break;
        }
    }
    if(x<MARGE_GAUCHE
       || x>MARGE_GAUCHE+TAILLE_CASE*TAILLE_X_PLATEAU
       || y<MARGE_HAUT
       || y>MARGE_HAUT+TAILLE_CASE*TAILLE_Y_PLATEAU){
        delete this;
    }
}

void Tir::avance()
{

}

void Tir::degatEnnemi(int idEnnemi)
{
    listeEnnemis[idEnnemi]->prendDegat(degat);
    delete this;
}

