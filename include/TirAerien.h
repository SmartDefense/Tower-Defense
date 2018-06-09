#ifndef TIRAERIEN_H
#define TIRAERIEN_H

#include <Tir.h>


class TirAerien : public Tir
{
    public:
        TirAerien(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien);
};

#endif // TIRAERIEN_H
