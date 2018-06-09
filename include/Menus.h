#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
void jeu(int numLevel);

void inputPseudo()                                                                  // Fonction de saisie du pseudo
{
    SDL_StartTextInput();
    SDL_Event events;
    int continuerPseudo=1;
    bool changement=true;

    Bouton Logo((double)MARGE_GAUCHE/TAILLE_CASE/2, 0.24, TAILLE_X_PLATEAU,TAILLE_Y_PLATEAU/6, ::textureLogo);
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
            //Ecrire("CollegiateInsideFLF",0.84,"Trop de caracteres",255,255,255,6,10);
            pseudo.pop_back();

        }
        if(changement)                                                                    // S'il y a changement, on l'écrit et l'affiche
        {
            SDL_SetRenderDrawColor(renderer, 0,127,127,255);
            SDL_RenderClear(renderer);
            //affichageTexture(textureLogo,200,12);
            Logo.affiche();
            Ecrire("CollegiateInsideFLF",0.84,"Entrez un pseudo :",255,255,255,6.4,3);
            Ecrire("CollegiateBlackFLF",0.74,"Valider",255,255,255,8.8,7.4);
            int longueurPseudo=pseudo.length();
            Ecrire("CollegiateOutlineFLF",0.84,pseudo,255,255,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE/TAILLE_CASE)/2-(longueurPseudo*0.22)),5); // Placement du pseudo de manière centrée en fonction de sa longueur
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
    Ecrire("WingdingReview",0.8,"ñ",255,255,255,1,1);
    Ecrire("CollegiateInsideFLF",0.5,"Retour",255,255,255,0.6,0.5);
    Ecrire("CollegiateInsideFLF",1,"CHOIX DU NIVEAU",255,255,255,5.5,1);
    Ecrire("Arial",1.3,"+",255,255,255,12.8,4.6);
    Ecrire("Arial",1.3,"-",255,255,255,12.2,4.5);
    Ecrire("CollegiateBlackFLF",0.74,"Valider",255,255,255,8.8,7.4);
    Ecrire("CollegiateInsideFLF",0.9,"NIVEAU 1",255,255,255,7,5);
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

                    Ecrire("WingdingReview",0.8,"ñ",255,255,255,1,1);
                    Ecrire("CollegiateInsideFLF",0.5,"Retour",255,255,255,0.6,0.5);
                    Ecrire("CollegiateInsideFLF",0.9,"NIVEAU " + to_string(numLevel),255,255,255,7,5);
                    Ecrire("CollegiateInsideFLF",1,"CHOIX DU NIVEAU",255,255,255,5.5,1);
                    Ecrire("Arial",1.3,"+",255,255,255,12.8,4.6);
                    Ecrire("Arial",1.3,"-",255,255,255,12.2,4.5);
                    Ecrire("CollegiateBlackFLF",0.74,"Valider",255,255,255,8.8,7.4);

                    SDL_RenderPresent(renderer);
                }

                // Si le joueur sélectionne le niveau précédent
                if (numLevel>1 && x>607 && x<633 && y>260 && y<278)
                {
                    numLevel--;
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",0.8,"ñ",255,255,255,1,1);
                    Ecrire("CollegiateInsideFLF",0.5,"Retour",255,255,255,0.6,0.5);
                    Ecrire("CollegiateInsideFLF",0.9,"NIVEAU " + to_string(numLevel),255,255,255,7,5);
                    Ecrire("CollegiateInsideFLF",1,"CHOIX DU NIVEAU",255,255,255,5.5,1);
                    Ecrire("Arial",1.3,"+",255,255,255,12.8,4.6);
                    Ecrire("Arial",1.3,"-",255,255,255,12.2,4.5);
                    Ecrire("CollegiateBlackFLF",0.74,"Valider",255,255,255,8.8,7.4);
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
    Ecrire("CollegiateInsideFLF",0.5,"Pseudo : " + pseudo,255,255,255,0.6,4);
    Ecrire("CollegiateInsideFLF",1,"MENU",255,255,255,9,1);
    Ecrire("WingdingReview",0.8,"ñ",255,255,255,1,1);
    Ecrire("CollegiateInsideFLF",0.5,"Retour",255,255,255,0.6,0.5);
    Ecrire("CollegiateInsideFLF",0.5,"Nombre de parties jouees : " + to_string(nbParties),255,255,255,0.6,3);
    Ecrire("CollegiateInsideFLF",0.5,"Record : " + to_string(highscore)+" $",255,255,255,0.6,5);
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
    Ecrire("WingdingReview",0.8,"ñ",255,255,255,1,1);
    Ecrire("CollegiateInsideFLF",0.5,"Retour",255,255,255,0.6,0.5);
    Ecrire("CollegiateInsideFLF",1,"AIDE",255,255,255,9,1);
    SDL_RenderPresent(renderer);

    string nomfichier= "regles.txt";                    // String contenant le nom du fichier et son extension
    fstream fichier(nomfichier.c_str(), ios::in);      // Ouverture du fichier regles
    string ligne;
    double saut=0;
    if (fichier)                                       // Si le fichier existe ...
    {

    while(getline(fichier, ligne))                      // Affichage des règles du jeu
    {
     Ecrire("BKANT",0.56,ligne,255,255,255,1,(2.7+saut));
     saut+=0.6;
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
    SDL_SetRenderDrawColor(renderer, 0,91,14,255);
    SDL_RenderClear(renderer);
    Bouton Accueil((double)MARGE_GAUCHE/TAILLE_CASE/2,(double)MARGE_HAUT/TAILLE_CASE/2, TAILLE_X_PLATEAU, TAILLE_Y_PLATEAU, ::textureAccueil);
    Accueil.affiche();
    Ecrire("CollegiateInsideFLF",0.84,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE*TAILLE_CASE)/2-(longueurPseudo*0.24)),0); // Affichage du pseudo du joueur
    SDL_Event events;
    int continuerDebut=1;

    Bouton Commencer(1, 13, 8, 2, ::textureBpCommencer);
    Bouton Menu(10, 13, 5, 2, ::textureBpMenu);
    Bouton Aide(16, 13, 4, 2, ::textureBpAide);

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
                    SDL_SetRenderDrawColor(renderer, 0,91,14,255);
                    SDL_RenderClear(renderer);
                    Accueil.affiche();
                    Ecrire("CollegiateInsideFLF",0.84,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE*TAILLE_CASE)/2-(longueurPseudo*0.24)),0);
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


                if (Menu.clique(x, y))
                {
                    // MENU //
                    menu();
                    SDL_SetRenderDrawColor(renderer, 0,91,14,255);
                    SDL_RenderClear(renderer);
                    Accueil.affiche();
                    Ecrire("CollegiateInsideFLF",0.84,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE*TAILLE_CASE)/2-(longueurPseudo*0.24)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (Commencer.clique(x, y))
                {
                    // COMMENCER //
                    choixLevel();
                    SDL_SetWindowSize(fenetre,20*TAILLE_CASE + MARGE_GAUCHE, 15*TAILLE_CASE + MARGE_HAUT);
                    SDL_SetRenderDrawColor(renderer, 0,91,14,255);
                    SDL_RenderClear(renderer);
                    Accueil.affiche();
                    Ecrire("CollegiateInsideFLF",0.84,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE*TAILLE_CASE)/2-(longueurPseudo*0.24)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (Aide.clique(x, y))
                {
                    // AIDE //
                    aide();
                    SDL_SetRenderDrawColor(renderer, 0,91,14,255);
                    SDL_RenderClear(renderer);
                    Accueil.affiche();
                    Ecrire("CollegiateInsideFLF",0.84,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU+MARGE_GAUCHE*TAILLE_CASE)/2-(longueurPseudo*0.24)),0);
                    SDL_RenderPresent(renderer);
                }
                break;
            }
        }
        Commencer.affiche();
        Menu.affiche();
        Aide.affiche();
        SDL_RenderPresent(renderer);
    }
}

#endif // MENUS_H_INCLUDED
