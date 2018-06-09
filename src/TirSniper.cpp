#include "TirSniper.h"

TirSniper::TirSniper(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien):
    Tir(x, y, dX, dY, ::textureTirSniper, angle, degat,  peutToucherTerrestre,  peutToucherAerien)
{
    //cout<<"Creation :\t TirSniper ("<<x<<","<<y<<")"<<endl;
}
