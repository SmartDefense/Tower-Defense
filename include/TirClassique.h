#ifndef TIRCLASSIQUE_H
#define TIRCLASSIQUE_H

#include <Tir.h>


class TirClassique : public Tir
{
    public:
        TirClassique(int x, int y, double dX, double dY, int angle, int degat, bool peutToucherTerrestre, bool peutToucherAerien);
};

#endif // TIRCLASSIQUE_H
