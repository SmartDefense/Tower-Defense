#include "BoutonTexte.h"

SDL_Texture* EcrireTexture(string police, double taille, string texte, Uint8 r, Uint8 v, Uint8 b) // Fonction d'écriture
{
    font = TTF_OpenFont(("fonts/" + police + ".ttf").c_str(), taille*TAILLE_CASE);                  // Ouverture de la police
    SDL_Color color = { r, v, b };                                                      // Couleur de police envoyée à la fonction type r,g,b
    SDL_Surface * surface = TTF_RenderUTF8_Blended(font,texte.c_str(), color);          // Rendu de la police sur le fond
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);            // Création de la texture à partir du fond
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    return  texture;
}

BoutonTexte::BoutonTexte() : Bouton(0, 0, -1,-1, NULL){}

BoutonTexte::BoutonTexte(double x, double y, string police, string texte, double taille, Uint8 r, Uint8 v, Uint8 b) : Bouton(x, y, -1,-1, NULL)
{
    textureBouton = EcrireTexture(police, taille, texte, r,v,b);
    SDL_QueryTexture(textureBouton, NULL, NULL, &dest.w, &dest.h);
}
