#ifndef TOURAERIEN_H
#define TOURAERIEN_H

#include <Tour.h>
#include <TirClassique.h>

class TourAerien : public Tour
{
    public:
        TourAerien(int x, int y, int priorite);
        ~TourAerien();
        virtual void amelioration(const int typeAmelioration);
        static const int multiplicateurCout = 1;

    protected:
        virtual void tir(double dX, double dY, double angle);
};

#endif // TOURAERIEN_H
