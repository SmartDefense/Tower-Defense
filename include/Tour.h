#ifndef TOUR_H
#define TOUR_H

#include <Case.h>

class Tour : public Case
{
    public:
        Tour(int x, int y, SDL_Texture* textureTourBase, SDL_Texture* textureTourCanon, int rechargement, int priorite, int degat, int vitesseTir, int vitesseCanon, double portee, bool peutToucherTerrestre, bool peutToucherAerien);
        virtual ~Tour();
        virtual void affiche();
        void affichePortee();
        void viseeEnnemi(Ennemi* ennemi, double distance);
        int action();
        virtual void tir(double dX, double dY, double angle);
        virtual void amelioration(const int typeAmelioration);
        int moduloPositif(int nombre, int modulo);

    protected:
        int rechargement,
            compteurRechargement,
            priorite,
            degat,
            vitesseTir,
            vitesseCanon,
            angleCanon,
            fondTourAleatoire,
            directionFondAleatoire;
        double portee;
        bool peutToucherAerien,
             peutToucherTerrestre;
        SDL_Texture *textureTourBase,
                     *textureTourCanon;
        vector<int> idPossibilite;
        Ennemi* choixAlea;

};

#endif // TOUR_H
