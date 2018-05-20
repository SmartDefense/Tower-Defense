#ifndef TOURPOISON_H
#define TOURPOISON_H

#include <Tour.h>
#include <TirPoison.h>


class TourPoison : public Tour
{
    public:
        TourPoison(int x, int y, int priorite);
        ~TourPoison();
        virtual void amelioration(const int typeAmelioration);
        static const int multiplicateurCout = 2;

    protected:
        virtual void tir(double dX, double dY, double angle);
        int duree;
};

#endif // TOURPOISON_H
