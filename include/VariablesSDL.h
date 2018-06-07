#ifndef VARIABLES2_H
#define VARIABLES2_H

extern SDL_Window* fenetre;
extern SDL_Renderer* renderer;
extern SDL_Texture  *textureCase,
                    *textureChemin,
                    *textureChateau,

                    *textureTourClassiqueBase,
                    *textureTourPoisonBase,
                    *textureTourSniperBase,

                    *textureTourClassiqueCanon,
                    *textureTourSniperCanon,

                    *textureEnnemiClassique,
                    *textureEnnemiRapide,
                    *textureEnnemiTank,
                    *textureEnnemiVolantSimple,

                    *textureTirClassique,
                    *textureTirSniper,

                    *textureEnnemiVolant[nbImageEnnemiVolant],

                    *textureExplosion[TEMPS_ANIM_TIR];

#endif // VARIABLES2_H
