#ifndef UTILITAIRES_H_INCLUDED
#define UTILITAIRES_H_INCLUDED

void Ecrire(string police, double taille, string texte, Uint8 r, Uint8 v, Uint8 b, double x, double y) // Fonction d'écriture
{
    font = TTF_OpenFont(("fonts/" + police + ".ttf").c_str(), taille*TAILLE_CASE);                  // Ouverture de la police
    SDL_Color color = { r, v, b };                                                      // Couleur de police envoyée à la fonction type r,g,b
    SDL_Surface * surface = TTF_RenderUTF8_Blended(font,texte.c_str(), color);          // Rendu de la police sur le fond
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);            // Création de la texture à partir du fond

    int texW = 0;                                                                       // Largeur de la texture en pixels
    int texH = 200;                                                                     // Hauteur de la texture en pixels
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);                                // Appel de la texture
    SDL_Rect dstrect = { x*TAILLE_CASE, y*TAILLE_CASE, texW, texH };                                            // Position de la zone d'écriture à partir de x et y, position du premier caractère
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);                                  // Copie de la texture dans le renderer

    SDL_DestroyTexture(texture);                                                        // Suppression de la texture
    TTF_CloseFont(font);                                                                // Fermeture de la police
}

void EcrireArgent()                 // Fonction d'écriture paramétrée pour afficher l'argent
{
    SDL_Color color = { 0,0,0 };
    SDL_Surface* surface = TTF_RenderText_Blended(fontArgent,(to_string(argent)+"$").c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 200;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 1000-texW, 35, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
}

void affichageTexture(SDL_Texture* texture, int x, int y)                               // Fonction d'affichage de chaque texture à la position x,y
{
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,texture,NULL,&position);
}

SDL_Surface* surface;
void chargeTexture(SDL_Texture* &dest, string nomImage){
    surface=IMG_Load((CHEMIN_IMAGES+nomImage).c_str());
    dest= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

#endif // UTILITAIRES_H_INCLUDED
