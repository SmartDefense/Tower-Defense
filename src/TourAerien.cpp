#include "TourAerien.h"

TourAerien::TourAerien(int x, int y, int priorite):
    Tour(x, y, ::textureTourClassiqueBase, ::textureTourClassiqueCanon, 5, priorite, 10, 6, 12, 3, false, true)
{
	Case::type="TourAerien";
    //cout<<"Creation :\t TourClassique ("<<x<<","<<y<<")"<<endl;
}

TourAerien::~TourAerien()
{
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
    //cout<<"Destruction :\t TourAerien ("<<x<<","<<y<<")"<<endl;
}

void TourAerien::tir(double dX, double dY, double angle)
{
    listeTirs.push_back(new TirClassique(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat));
    compteurRechargement=rechargement;
}

void TourAerien::amelioration(const int typeAmelioration)
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
