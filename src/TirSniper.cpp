#include "TirSniper.h"

TirSniper::TirSniper(int x, int y, double dX, double dY, int angle, int degat):
    Tir(x, y, dX, dY, ::textureTirSniper, angle, degat)
{
    //cout<<"Creation :\t TirSniper ("<<x<<","<<y<<")"<<endl;
}
