#include "IA.c"
#include "JOUEUR.c"

int main()
{

    srand(time(NULL)); // génération aléatoire

//// INITIALISATION DES GRILLES ET DES MATRICES D'INDICES ////

    int indices_joueur[INDICES_L][INDICES_C], indices_IA[INDICES_L][INDICES_C];
    char grille_joueur[GRILLE_L][GRILLE_C], grille_IA[GRILLE_L][GRILLE_C];

    Init_indices(indices_joueur);
    Init_indices(indices_IA);
    Init_grille(grille_joueur);
    Init_grille(grille_IA);

    Bateau cuirasse_joueur, croiseur_joueur, torpilleur_joueur, sous_marin_joueur, cuirasse_IA, croiseur_IA, torpilleur_IA, sous_marin_IA;

    cuirasse_joueur.taille = 4, cuirasse_IA.taille = 4, cuirasse_joueur.nombre = 1, cuirasse_IA.nombre = 1;
    croiseur_joueur.taille = 3, croiseur_IA.taille = 3, croiseur_joueur.nombre = 2, croiseur_IA.nombre = 2;
    torpilleur_joueur.taille = 2, torpilleur_IA.taille = 2, torpilleur_joueur.nombre = 3, torpilleur_IA.nombre = 3;
    sous_marin_joueur.taille = 1, sous_marin_IA.taille = 1, sous_marin_joueur.nombre = 4, sous_marin_IA.nombre = 4;

    int total_bateaux_joueur = cuirasse_joueur.nombre + croiseur_joueur.nombre + torpilleur_joueur.nombre + sous_marin_joueur.nombre;
    int total_bateaux_IA = cuirasse_IA.nombre + croiseur_IA.nombre + torpilleur_IA.nombre + sous_marin_IA.nombre;


    while(total_bateaux_IA)
    {
        IA_Placement(indices_IA, &cuirasse_IA, &croiseur_IA, &torpilleur_IA, &sous_marin_IA);
        total_bateaux_IA = cuirasse_IA.nombre + croiseur_IA.nombre + torpilleur_IA.nombre + sous_marin_IA.nombre;
    }

//// PLACEMENT BATEAUX JOUEUR ////

    Menu_Demarrage();
    Affiche_bateaux(cuirasse_joueur, croiseur_joueur, torpilleur_joueur, sous_marin_joueur);

    char continuer[200];
    printf("\nTapez entrée pour continuer\n");
    Lire(continuer, 200);

    Affiche_grille(grille_joueur);
    printf("\nCeci est votre grille\n");

    while(total_bateaux_joueur)
    {
        Placement(indices_joueur, &cuirasse_joueur, &croiseur_joueur, &torpilleur_joueur, &sous_marin_joueur);
        printf("\nTapez entrée pour continuer\n");
        Lire(continuer, 200);

        Actu_grille(indices_joueur, grille_joueur);
        Affiche_grille(grille_joueur);
        total_bateaux_joueur = cuirasse_joueur.nombre + croiseur_joueur.nombre + torpilleur_joueur.nombre + sous_marin_joueur.nombre;

        if(total_bateaux_joueur >= 1)
        {
            printf("\nEncore %d bateaux à placer :\n", total_bateaux_joueur);
            Affiche_bateaux(cuirasse_joueur, croiseur_joueur, torpilleur_joueur, sous_marin_joueur);
            printf("\n");
        }
    }

//// DEBUT DE LA PARTIE ////

printf("\nTous vos bateaux sont placés.\n");
printf("Les miens aussi. Nous pouvons commencer la partie.\n");
printf("\nA vous de commencer\n\n");

int gagnant = 0;
int tours = 1;

while(!gagnant)
{

    // TOUR JOUEUR //
    printf("========== TOUR %d ==========\n\n", tours);

    printf("== GRILLE ADVERSE ==\n\n");
    Affiche_grille(grille_IA);
    printf("\nOù voulez-vous tirer?\n");

    Tir tir_joueur;
    char position[TPOS];
    Lire(position, TPOS);

    while(!Entree_Invalide(position, TPOS, &tir_joueur))
    {
        Erreur_Entree();
        Lire(position, TPOS);
    }

    if(Case_Visee(indices_IA, tir_joueur.ligne, tir_joueur.colonne) == 3) printf("Vous avez déjà tiré à cet endroit... Dommage\n");
    else if(Case_Visee(indices_IA, tir_joueur.ligne, tir_joueur.colonne) == 0)
    {
         printf("Dans l'eau !\n");
         indices_IA[tir_joueur.ligne][tir_joueur.colonne] = -1; // on change la valeur de la case
    }
    else if(Case_Visee(indices_IA, tir_joueur.ligne, tir_joueur.colonne) == 1)
    {
         printf("Touché !\n");
         indices_IA[tir_joueur.ligne][tir_joueur.colonne] = 2; // on change la valeur de la case
    }
    else if(Case_Visee(indices_IA, tir_joueur.ligne, tir_joueur.colonne) == 2) //
    {
         printf("Touché-coulé !\n");
         indices_IA[tir_joueur.ligne][tir_joueur.colonne] = 2; // on change la valeur de la case
         total_bateaux_joueur++;
    }

    IA_Actu_indices(indices_IA);
    IA_Actu_grille(indices_IA, grille_IA);

    if(total_bateaux_joueur == 10) gagnant = 1;

    // TOUR IA //

    if(total_bateaux_joueur != 10)
    {
        printf("\nA mon tour\n\n");
        printf("== VOTRE GRILLE ==\n");
        Affiche_grille(grille_joueur);

        char ligne_IA = 'k'; //
        int colonne_IA = 15; //
        Tir tir_IA;

        if(Search(indices_joueur, &tir_IA.ligne, &tir_IA.colonne))
        {
            int retour = Destroy(indices_joueur, &tir_IA.ligne, &tir_IA.colonne);

            if(retour == 0)
            {
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Dans l'eau ! \n\n");
            }
            else if(retour == 1)
            {
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Touché ! \n\n");
            }
            else if(retour == 2)
            {
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Touché-coulé ! \n\n");
                total_bateaux_IA++;
            }
        }

        else
        {
            tir_IA.ligne = (rand() % 10) + 1;
            tir_IA.colonne = (rand() % 10) + 1;

            while(indices_joueur[tir_IA.ligne][tir_IA.colonne] == -1 || indices_joueur[tir_IA.ligne][tir_IA.colonne] == 3 || IA_Bateau_Coule_Adjacent(indices_joueur, tir_IA.ligne, tir_IA.colonne))
            {
                tir_IA.ligne = (rand() % 10) + 1;
                tir_IA.colonne = (rand() % 10) + 1;
            }

            if(IA_Case_Visee(indices_joueur, tir_IA.ligne, tir_IA.colonne) == 0)
            {
                indices_joueur[tir_IA.ligne][tir_IA.colonne] = -1; // on change la valeur de la case
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Dans l'eau ! \n\n");
            }
            else if(IA_Case_Visee(indices_joueur, tir_IA.ligne, tir_IA.colonne) == 1) //
            {
                indices_joueur[tir_IA.ligne][tir_IA.colonne] = 2; // on change la valeur de la case
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Touché ! \n\n");
            }
            else if(IA_Case_Visee(indices_joueur, tir_IA.ligne, tir_IA.colonne) == 2) //
            {
                indices_joueur[tir_IA.ligne][tir_IA.colonne] = 2; // on change la valeur de la case
                ligne_IA = tir_IA.ligne + 64;
                colonne_IA = tir_IA.colonne;
                printf("%c%d...\n", ligne_IA, colonne_IA);
                printf("Touché-coulé ! \n\n");
                total_bateaux_IA++;
            }
        }

        Actu_indices(indices_joueur);
        Actu_grille(indices_joueur, grille_joueur);

        if(total_bateaux_IA == 10) gagnant = 2;
        tours++;
    }

}

if(gagnant == 1)
{
    printf("Vous avez gagné, félicitations !");
}
else if(gagnant == 2)
{
    printf("J'ai gagné, vous êtes une merde !");
}


    return 0;
}
