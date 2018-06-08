#ifndef VARIABLES2_H
#define VARIABLES2_H

extern SDL_Window* fenetre;
extern SDL_Renderer* renderer;
extern SDL_Texture  *textureChemin,
                    *textureCaseSimple,
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

                    *textureEnnemiVolant[nbImageEnnemiVolant],
                    *textureEnnemiRapide[4],
                    *textureCase[nbImageCase],


                    *textureExplosion[TEMPS_ANIM_TIR];

#endif // VARIABLES2_H
