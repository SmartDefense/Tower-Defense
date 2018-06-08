#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
void jeu(int numLevel);

void inputPseudo()                                                                  // Fonction de saisie du pseudo
{
    SDL_StartTextInput();
    SDL_Event events;
    int continuerPseudo=1;
    bool changement=true;
    while(continuerPseudo==1 && continuer==1)                                       // Tant que l'on ne quitte pas ou clique sur retour
    {

        while(SDL_PollEvent(&events))                                               // Récupération des évènements
        {
            switch(events.type)
            {
            case SDL_QUIT :                                                         // Fermeture de la fenêtre
                continuer=0;
                break;
            case SDL_TEXTINPUT :                                                    // Saisie du texte dans la variable pseudo
                pseudo += events.text.text;
                changement=true;
                break;
            case SDL_KEYDOWN:
                if(events.key.keysym.scancode==SDL_SCANCODE_BACKSPACE && pseudo.length() > 0)   // Suppression du dernier caractère
                {
                    pseudo.pop_back();
                    changement=true;
                }
                if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && pseudo.length() > 0)                             // Validation par la touche entrée
                {
                    continuerPseudo=0;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;
                if (x>437 && x<591 && y>370 && y<410 && pseudo.length()>2)                  // Si le pseudo contient 3 caractères ou plus, on peut valider
                {
                    continuerPseudo=0;
                }
                break;
            }
        }
        while (pseudo.length()>=17)                                                        // Si le pseudo contient plus de 16 caractères, on efface le 17ème saisi
        {
            //Ecrire("CollegiateInsideFLF",42,"Trop de caracteres",255,255,255,300,500);
            pseudo.pop_back();

        }
        if(changement)                                                                    // S'il y a changement, on l'écrit et l'affiche
        {
            SDL_SetRenderDrawColor(renderer, 0,127,127,255);
            SDL_RenderClear(renderer);
            affichageTexture(textureLogo,200,12);
            Ecrire("CollegiateInsideFLF",42,"Entrez un pseudo :",255,255,255,320,150);
            Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
            int longueurPseudo=pseudo.length()+1;
            Ecrire("CollegiateOutlineFLF",42,pseudo,255,255,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*11)),250); // Placement du pseudo de manière centrée en fonction de sa longueur
            changement=false;
        }
        SDL_RenderPresent(renderer);        // On rafraichit
    }
}

void choixLevel() // Fonction de choix du niveau
{
    // Affichage des éléments graphiques sur la fenêtre
    numLevel=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
    Ecrire("Arial",65,"+",255,255,255,640,232);
    Ecrire("Arial",65,"-",255,255,255,610,226);
    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
    Ecrire("CollegiateInsideFLF",45,"NIVEAU 1",255,255,255,350,250);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    SDL_RenderPresent(renderer);

    SDL_Event events;
    int continuerLevel=1;
    while(continuerLevel==1 && continuer==1)
    {

        while(SDL_PollEvent(&events))  // Récupération des évènements
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;
            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)   // Revenir en arrière avec le bp Echap
                {
                    continuerLevel=0;
                }
                else if (events.key.keysym.scancode==SDL_SCANCODE_RETURN){
                    continuerLevel=0;
                    jeu(numLevel);
                }
                break;

            case SDL_QUIT :                                          // Quitter le jeu
                continuer=0;
                break;

            case SDL_MOUSEBUTTONUP:

                // Récupération du clic
                int x = events.button.x;
                int y = events.button.y;
                //std::cout << x << SDL_GetError() << std::endl;
                //std::cout << y << SDL_GetError() << std::endl;


                // Si le joueur sélectionne le niveau suivant
                if (x>638 && x<678 && y>250 && y<285)
                {
					numLevel++;
					ifstream fichier(CHEMIN_LEVELS+"level"+to_string(numLevel)+".txt");
					if(!fichier.is_open()){
						numLevel--;
					}
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(numLevel),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                // Si le joueur sélectionne le niveau précédent
                if (numLevel>1 && x>607 && x<633 && y>260 && y<278)
                {
                    numLevel--;
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(numLevel),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                // Validation du choix
                else if (x>437 && x<585 && y>370 && y<410)
                {
                    continuerLevel=0;
                    jeu(numLevel);
                }

                // Clic sur le bp retour
                else if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerLevel=0;
                }
                break;
            }
        }
    }
}

void menu()
{
    SDL_Event events;
    int continuerMenu=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);

    // Affichage des éléments graphiques
    Ecrire("CollegiateInsideFLF",25,"Pseudo : " + pseudo,255,255,255,30,200);
    Ecrire("CollegiateInsideFLF",50,"MENU",255,255,255,450,50);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",25,"Nombre de parties jouees : " + to_string(nbParties),255,255,255,30,150);
    Ecrire("CollegiateInsideFLF",25,"Record : " + to_string(highscore)+" $",255,255,255,30,250);
    SDL_RenderPresent(renderer);

    while (continuerMenu==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerMenu=0;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;

                // Clic sur le bp retour
                if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerMenu=0;
                }
                break;
            }
        }
    }
}

void aide()
{
    // Affichage des éléments graphiques
    SDL_Event events;
    int continuerAide=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",50,"AIDE",255,255,255,450,50);
    SDL_RenderPresent(renderer);

    string nomfichier= "regles.txt";                    // String contenant le nom du fichier et son extension
    fstream fichier(nomfichier.c_str(), ios::in);      // Ouverture du fichier regles
    string ligne;
    int saut=0;
    if (fichier)                                       // Si le fichier existe ...
    {

    while(getline(fichier, ligne))                      // Affichage des règles du jeu
    {
     Ecrire("BKANT",28,ligne,255,255,255,50,(137+saut));
     saut+=30;
    }

    SDL_RenderPresent(renderer);
    fichier.close();
    }

    while (continuerAide==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerAide=0;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;

                if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerAide=0;
                }
                break;
            }
        }
    }
}

void debut() // Affichage de l'écran initial
{
    recupInfos();
    inputPseudo();  // Saisie du pseudo
    int longueurPseudo=pseudo.length()+8;
    affichageTexture(textureAccueil,0,0); // Affichage de l'image d'accueil
    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0); // Affichage du pseudo du joueur
    SDL_RenderPresent(renderer);
    SDL_Event events;
    int continuerDebut=1;

    while(continuerDebut==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerDebut=0;
                }

                else if(events.key.keysym.scancode==SDL_SCANCODE_SPACE){
                    // COMMENCER //
                    choixLevel();
                    SDL_SetWindowSize(fenetre,20*TAILLE_CASE + MARGE_GAUCHE, 15*TAILLE_CASE + MARGE_HAUT);
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_MOUSEBUTTONUP:

                // Récupération des clics et affichage du menu suivant en conséquence //
                int x = events.button.x;
                int y = events.button.y;

                if (x>507 && x<726 && y>669 && y<763)
                {
                    // MENU //
                    menu();
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>45 && x<428 && y>670 && y<763)
                {
                    // COMMENCER //
                    choixLevel();
                    SDL_SetWindowSize(fenetre,20*TAILLE_CASE + MARGE_GAUCHE, 15*TAILLE_CASE + MARGE_HAUT);
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>807 && x<990 && y>669 && y<763)
                {
                    // AIDE //
                    aide();
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                break;
            }
        }
    }
}

#endif // MENUS_H_INCLUDED
