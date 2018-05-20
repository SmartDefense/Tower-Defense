#ifndef CHEMIN_H
#define CHEMIN_H

#include <Case.h>


class Chemin : public Case
{
    public:
        Chemin(int x, int y, int block);
        virtual ~Chemin();
        virtual void affiche();
        int getNbPassage();
        virtual int action();
        virtual void amelioration(const int typeAmelioration);
        int getVitesseDeplacement();

    protected:
        int vitesseDeplacement;
        int nbPassage;

};

#endif // CHEMIN_H
