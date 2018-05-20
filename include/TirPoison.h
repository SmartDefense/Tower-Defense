#ifndef TIRPOISON_H
#define TIRPOISON_H

#include <Tir.h>


class TirPoison : public Tir
{
    public:
        TirPoison(int x, int y, double dX, double dY, int angle, int degat, int duree);

    protected:
        void degatEnnemi(int idEnnemi);
        int duree;
};

#endif // TIRPOISON_H
