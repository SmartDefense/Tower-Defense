#include "TirAerien.h"

TirAerien::TirAerien(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien):
    Tir(x, y, dX, dY, ::textureTirAerien, angle, degat, peutToucherTerrestre, peutToucherAerien)
{
    //cout<<"Creation :\t TirAerien ("<<x<<","<<y<<")"<<endl;
}
