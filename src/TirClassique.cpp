#include "TirClassique.h"

TirClassique::TirClassique(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien):
    Tir(x, y, dX, dY, ::textureTirClassique, angle, degat, peutToucherTerrestre, peutToucherAerien)
{
    //cout<<"Creation :\t TirClassique ("<<x<<","<<y<<")"<<endl;
}
