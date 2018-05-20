#include "TirClassique.h"

TirClassique::TirClassique(int x, int y, double dX, double dY, int angle, int degat):
    Tir(x, y, dX, dY, ::textureTirClassique, angle, degat)
{
    //cout<<"Creation :\t TirClassique ("<<x<<","<<y<<")"<<endl;
}
