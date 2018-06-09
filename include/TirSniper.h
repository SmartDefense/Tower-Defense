#ifndef TIRSNIPER_H
#define TIRSNIPER_H

#include <Tir.h>


class TirSniper : public Tir
{
    public:
        TirSniper(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien);
};

#endif // TIRSNIPER_H
