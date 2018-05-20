#ifndef TOURCLASSIQUE_H
#define TOURCLASSIQUE_H

#include <Tour.h>
#include <TirClassique.h>


class TourClassique : public Tour
{
    public:
        TourClassique(int x, int y, int priorite);
        ~TourClassique();
        virtual void amelioration(const int typeAmelioration);
        static const int multiplicateurCout = 1;

    protected:
        virtual void tir(double dX, double dY, double angle);

};

#endif // TOURCLASSIQUE_H
