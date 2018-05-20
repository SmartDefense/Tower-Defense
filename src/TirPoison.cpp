#include "TirPoison.h"

TirPoison::TirPoison(int x, int y, double dX, double dY, int angle, int degat, int duree):
    Tir(x, y, dX, dY, ::textureTirPoison, angle, degat),
    duree(duree)
{
    //cout<<"Creation :\t TirPoison ("<<x<<","<<y<<")"<<endl;
}

void TirPoison::degatEnnemi(int idEnnemi)
{
    listeEnnemis[idEnnemi]->appliquerEffet(EFFET_POISON, degat, duree);
    delete this;
}
