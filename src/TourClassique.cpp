#include "TourClassique.h"

TourClassique::TourClassique(int x, int y, int priorite):
    Tour(x, y, ::textureTourClassiqueBase, ::textureTourClassiqueCanon, 30, priorite, 50, 12, 6, 3, true, false)
{
	Case::type="TourClassique";
    //cout<<"Creation :\t TourClassique ("<<x<<","<<y<<")"<<endl;
}

TourClassique::~TourClassique()
{
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
    //cout<<"Destruction :\t TourClassique ("<<x<<","<<y<<")"<<endl;
}

void TourClassique::tir(double dX, double dY, double angle)
{
    listeTirs.push_back(new TirClassique(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat, peutToucherTerrestre, peutToucherAerien));
    compteurRechargement=rechargement;
}

void TourClassique::amelioration(const int typeAmelioration)
{
    switch(typeAmelioration){
    case AMELIORATION_CADENCE:
        if(rechargement>5) rechargement-=5;
        break;
    case AMELIORATION_DEGAT_TIR:
        degat+=10;
        break;
    case AMELIORATION_PORTEE_TOUR:
        portee+=TAILLE_CASE*0.5;
        break;
    case AMELIORATION_VITESSE_TIR:
        vitesseTir+=2;
        break;
    }
}
