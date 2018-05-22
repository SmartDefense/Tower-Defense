#ifndef TOURPOISON_H
#define TOURPOISON_H

#include <Tour.h>


class TourPoison : public Tour
{
    public:
        TourPoison(int x, int y, int priorite);
        ~TourPoison();
        virtual int action();
        virtual void amelioration(const int typeAmelioration);
        static const int multiplicateurCout = 2;

    protected:
        int duree;
};

#endif // TOURPOISON_H
