#ifndef BOUTONTEXTE_H
#define BOUTONTEXTE_H

#include <Bouton.h>


class BoutonTexte : public Bouton
{
    public:
        BoutonTexte();
        BoutonTexte(double x, double y, string police, string texte, double taille, Uint8 r, Uint8 v, Uint8 b);
};

#endif // BOUTONTEXTE_H
