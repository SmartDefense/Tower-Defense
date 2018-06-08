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
                    *textureEnnemiRapide[4],
                    *textureCase[NB_IMAGE_CASE],


                    *textureExplosion[TEMPS_ANIM_TIR];

#endif // VARIABLES2_H
