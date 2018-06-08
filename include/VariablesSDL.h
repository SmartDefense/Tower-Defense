#ifndef VARIABLES2_H
#define VARIABLES2_H

extern SDL_Window* fenetre;
extern SDL_Renderer* renderer;
extern SDL_Texture  *textureChemin,
                    *textureCaseFond,
                    *textureChateau,

                    *textureTourClassiqueBase,
                    *textureTourPoisonBase,
                    *textureTourSniperBase,

                    *textureTourClassiqueCanon,
                    *textureTourSniperCanon,

                    *textureEnnemiClassique,
                    *textureEnnemiRapideSimple,
                    *textureEnnemiTank,
                    *textureEnnemiVolantSimple,

                    *textureTirClassique,
                    *textureTirSniper,

                    *textureEnnemiVolant[NB_IMAGE_ENNEMI_VOLANT],
                    *textureEnnemiRapide[NB_IMAGE_ENNEMI_RAPIDE],
                    *textureCase[NB_CASE_FOND],
                    *textureTourFond[NB_TOUR_FOND],

                    *textureExplosion[TEMPS_ANIM_TIR];

#endif // VARIABLES2_H
