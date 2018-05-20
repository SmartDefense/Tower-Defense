#ifndef TOURSNIPER_H
#define TOURSNIPER_H

#include <Tour.h>
#include <TirSniper.h>


class TourSniper : public Tour
{
    public:
        TourSniper(int x, int y, int priorite);
        ~TourSniper();
        virtual void amelioration(const int typeAmelioration);
        static const int multiplicateurCout = 3;

    protected:
        virtual void tir(double dX, double dY, double angle);

};

#endif // TOURSNIPER_H
