#include "JOUEUR.h"
#include "Affichage.c"

///////////// |LECTURE| ///////////////

void Erase_buffer()
{
    int c = 0;
    while(c != '\n' && c != 'EOF' ) c = getchar();
}

int Lire(char *position, int taille)
{
    char *fin = NULL;

    if(fgets(position, TPOS, stdin) != NULL)
    {
        fin = strchr(position, '\n');

        if(fin != NULL) *fin = '\0';
        else Erase_buffer();
        return 1;
    }

    else
    {
        Erase_buffer();
        return 0;
    }
}

char *MAJ(char position[], int taille)
{
    for(int i = 0; i < taille; i++)
    {
        if(position[i] > 96 && position[i] < 123) position[i] -= 32;
    }
}

int Entree_Choix(char entree[TPOS])
{
    if(entree[0] < 49 || entree[0] > 52)
    {
         printf("Je n'ai pas compris votre choix. Veuillez choisir parmi les options 1 à 4.\n");
         return 0;
    }
    else
    {
        if(entree[1] != '\0')
        {
             printf("Je n'ai pas compris votre choix. Veuillez choisir parmi les options 1 à 4.\n");
             return 0;
        }
        else return entree[0] - 48;
    }
}


///////////// |MECANIQUES| ///////////////

int Entree_Invalide(char position[], int taille, Tir *tir)
{
    if(position[0] < 65 || position[0] > 74) return 0; // si le 1er caractère n'est pas entre 'A' et 'J'
    else
    {
        if(position[1] < 49 || position[1] > 57) return 0; // si le 2e carac n'est pas entre '1' et '9'

        else if(position[1] == 49) // si le 2e carac est '1'
        {
            if(position[2] == 48) // et le 3e un '0' (donc '10')
            {
                tir->ligne = position[0] - 64;
                tir->colonne = 10;
                return 1;
            }
            else if(position[2] == '\0')
            {
                tir->ligne = position[0] - 64;
                tir->colonne = 1;
                return 1;
            }
        }

        else
        {
            if(position[2] != '\0') return 0;
            else
            {
                tir->ligne = position[0] - 64;
                tir->colonne = position[1] - 48;
                return 1;
            }
        }

    }
}

void Placement(int indices[INDICES_L][INDICES_C], Bateau *cuirasse, Bateau *croiseur, Bateau *torpilleur, Bateau *sous_marin)
{
    printf("\nQuel bateau voulez vous placer?\n");
    printf("1 = Cuirassé\n2 = Croiseur\n3 = Torpilleur\n4 = Sous-marin\n");

    char entree[TPOS];
    Lire(entree, TPOS);

    int choix = 0;
    while(!choix)
    {
         choix = Entree_Choix(entree);
         Lire(entree, TPOS);
    }

    char position[TPOS];
    Tir placement;
    placement.ligne = 0, placement.colonne = 0;

    switch(choix)
    {
        case 1: // CUIRASSÉ
            if(cuirasse->nombre == 0)
            {
                printf("Vous avez déjà placé tous vos cuirassés\n");
                break;
            }
            else
            {
                printf("Ou voulez-vous placer votre cuirassé?\n");
                Lire(position, TPOS);
                position[TPOS] = MAJ(position, TPOS);

                if(!Entree_Invalide(position, TPOS, &placement))
                {
                    Erreur_Entree();
                    break;
                }
                if(indices[placement.ligne][placement.colonne] == 1) // tant que la case est occupée OU qu'il y a un bateau adjacent à la case choisie
                {
                    printf("La case choisie est déjà occupée\n");
                    break;
                }
                if(Bateau_Adjacent(indices, placement.ligne, placement.colonne))
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
            }

            Entree_Invalide(position, TPOS, &placement);

            printf("\nVers quelle direction voulez vous l'orienter?\n");
            printf("1 = haut    2 = bas\n");
            printf("3 = gauche  4 = droite\n");

            entree[TPOS] = 0, choix = 0;
            Lire(entree, TPOS);
            while(!choix) // Tant que le choix n'est pas compris entre 1 et 4
            {
                choix = Entree_Choix(entree);
                Lire(entree, TPOS);
            }

            int l = placement.ligne, c = placement.colonne;

            switch(choix)
            {
            case 1: // HAUT
                if(Placement_Invalide(indices, l, c, *cuirasse, 1) == 1)
                {
                    printf("Pas assez d'espace vers le haut\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 1) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 1) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1, indices[l - 2][c] = 1, indices[l - 3][c] = 1; // on met toutes les cases choisies à 1
                    printf("Cuirassé placé\n");
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 2: // BAS
                if(Placement_Invalide(indices, l, c, *cuirasse, 2) == 1)
                {
                    printf("Pas assez d'espace vers le bas\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 2) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 2) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1, indices[l + 2][c] = 1, indices[l + 3][c] = 1; // on met toutes les cases choisies à 1
                    printf("Cuirassé placé\n");
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(Placement_Invalide(indices, l, c, *cuirasse, 3) == 1)
                {
                    printf("Pas assez d'espace vers la gauche\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 3) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 3) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1, indices[l][c - 2] = 1, indices[l][c - 3] = 1; // on met toutes les cases choisies à 1
                    printf("Cuirassé placé\n");
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(Placement_Invalide(indices, l, c, *cuirasse, 4) == 1)
                {
                    printf("Pas assez d'espace vers la droite\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 4) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *cuirasse, 4) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1, indices[l][c + 2] = 1, indices[l][c + 3] = 1; // on met toutes les cases choisies à 1
                    printf("Cuirassé placé\n");
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 2: // CROISEUR
            if(croiseur->nombre == 0)
            {
                printf("Vous avez déjà placé tous vos croiseurs\n");
                break;
            }
            else
            {
                printf("Ou voulez-vous placer votre croiseur?\n");
                Lire(position, TPOS);
                position[TPOS] = MAJ(position, TPOS);

                if(!Entree_Invalide(position, TPOS, &placement))
                {
                    Erreur_Entree();
                    break;
                }
                if(indices[placement.ligne][placement.colonne] == 1) // SI la case est occupée
                {
                    printf("La case choisie est déjà occupée\n");
                    break;
                }
                if(Bateau_Adjacent(indices, placement.ligne, placement.colonne))
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
            }

            Entree_Invalide(position, TPOS, &placement);

            printf("\nVers quelle direction voulez vous l'orienter?\n");
            printf("1 = haut    2 = bas\n");
            printf("3 = gauche  4 = droite\n");

            entree[TPOS] = 0, choix = 0;
            Lire(entree, TPOS);
            while(!choix) // Tant que le choix n'est pas compris entre 1 et 4
            {
                choix = Entree_Choix(entree);
                Lire(entree, TPOS);
            }

            l = placement.ligne, c = placement.colonne;

            switch(choix)
            {
            case 1: // HAUT
                if(Placement_Invalide(indices, l, c, *croiseur, 1) == 1)
                {
                    printf("Pas assez d'espace vers le haut\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 1) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 1) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1, indices[l - 2][c] = 1; // on met toutes les cases choisies à 1
                    printf("Croiseur placé\n");
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 2: // BAS
                if(Placement_Invalide(indices, l, c, *croiseur, 2) == 1)
                {
                    printf("Pas assez d'espace vers le bas\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 2) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 2) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1, indices[l + 2][c] = 1; // on met toutes les cases choisies à 1
                    printf("Croiseur placé\n");
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(Placement_Invalide(indices, l, c, *croiseur, 3) == 1)
                {
                    printf("Pas assez d'espace vers la gauche\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 3) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 3) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1, indices[l][c - 2] = 1; // on met toutes les cases choisies à 1
                    printf("Croiseur placé\n");
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(Placement_Invalide(indices, l, c, *croiseur, 4) == 1)
                {
                    printf("Pas assez d'espace vers la droite\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 4) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *croiseur, 4) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1, indices[l][c + 2] = 1; // on met toutes les cases choisies à 1
                    printf("Croiseur placé\n");
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 3: // TORPILLEUR
            if(torpilleur->nombre == 0)
            {
                printf("Vous avez déjà placé tous vos torpilleurs\n");
                break;
            }
            else
            {
                printf("Ou voulez-vous placer votre torpilleur?\n");
                Lire(position, TPOS);
                position[TPOS] = MAJ(position, TPOS);

                if(!Entree_Invalide(position, TPOS, &placement))
                {
                    Erreur_Entree();
                    break;
                }
                if(indices[placement.ligne][placement.colonne] == 1) // SI la case est occupée
                {
                    printf("La case choisie est déjà occupée\n");
                    break;
                }
                if(Bateau_Adjacent(indices, placement.ligne, placement.colonne))
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
            }

            Entree_Invalide(position, TPOS, &placement);

            printf("\nVers quelle direction voulez vous l'orienter?\n");
            printf("1 = haut    2 = bas\n");
            printf("3 = gauche  4 = droite\n");

            entree[TPOS] = 0, choix = 0;
            Lire(entree, TPOS);
            while(!choix) // Tant que le choix n'est pas compris entre 1 et 4
            {
                choix = Entree_Choix(entree);
                Lire(entree, TPOS);
            }

            l = placement.ligne, c = placement.colonne;

            switch(choix)
            {
            case 1: // HAUT
                if(Placement_Invalide(indices, l, c, *torpilleur, 1) == 1)
                {
                    printf("Pas assez d'espace vers le haut\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 1) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 1) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1; // on met toutes les cases choisies à 1
                    printf("Torpilleur placé\n");
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 2: // BAS
                if(Placement_Invalide(indices, l, c, *torpilleur, 2) == 1)
                {
                    printf("Pas assez d'espace vers le bas\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 2) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 2) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1; // on met toutes les cases choisies à 1
                    printf("Torpilleur placé\n");
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(Placement_Invalide(indices, l, c, *torpilleur, 3) == 1)
                {
                    printf("Pas assez d'espace vers la gauche\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 3) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 3) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1; // on met toutes les cases choisies à 1
                    printf("Torpilleur placé\n");
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(Placement_Invalide(indices, l, c, *torpilleur, 4) == 1)
                {
                    printf("Pas assez d'espace vers la droite\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 4) == 2)
                {
                    printf("L'espace est déjà occupé par l'un de vos bateaux\n");
                    break;
                }
                if(Placement_Invalide(indices, l, c, *torpilleur, 4) == 3)
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1; // on met toutes les cases choisies à 1
                    printf("Torpilleur placé\n");
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 4: // SOUS-MARIN
            if(sous_marin->nombre == 0)
            {
                printf("Vous avez déjà placé tous vos sous-marins\n");
                break;
            }
            else
            {
                printf("Ou voulez-vous placer votre sous-marin?\n");
                Lire(position, TPOS);
                position[TPOS] = MAJ(position, TPOS);

                if(!Entree_Invalide(position, TPOS, &placement))
                {
                    Erreur_Entree();
                    break;
                }
                if(indices[placement.ligne][placement.colonne] == 1) // SI la case est occupée
                {
                    printf("La case choisie est déjà occupée\n");
                    break;
                }
                if(Bateau_Adjacent(indices, placement.ligne, placement.colonne))
                {
                    printf("Vos bateaux ne peuvent pas être placés côte à côte\n");
                    break;
                }
            }

            indices[placement.ligne][placement.colonne] = 1;
            sous_marin->nombre--;
            printf("Sous-marin placé\n");
    }
}

int Placement_Invalide(int indices[INDICES_L][INDICES_C], int ligne, int colonne, Bateau bateau, int direction)
{
    int l = ligne, c = colonne;
    int i;

    switch(direction)
    {
    case 1: // HAUT
        if(l - (bateau.taille - 1) <= 0) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne - i][colonne] == 1) return 2;
        }

        int vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(Bateau_Adjacent(indices, l - i, c)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 2: // BAS
        if(l + (bateau.taille - 1) >= 12) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne + i][colonne] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(Bateau_Adjacent(indices, l + i, c)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 3: // GAUCHE
        if(c - (bateau.taille - 1) <= 0) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne][colonne - i] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(Bateau_Adjacent(indices, l, c - i)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 4: // DROITE
        if(c + (bateau.taille - 1) >= 12) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne][colonne + i] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(Bateau_Adjacent(indices, l, c + i)) vrai++;
        }

        if(vrai) return 3;
        else return 0;
    }
}

int Bateau_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{
    if(indices[ligne + 1][colonne] == 1) return 1;
    if(indices[ligne - 1][colonne] == 1) return 1;
    if(indices[ligne][colonne + 1] == 1) return 1;
    if(indices[ligne][colonne - 1] == 1) return 1;

    else return 0;
}

int Case_Visee(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{

    if(indices[ligne][colonne] == 1)
    {
        if(Touche_Coule(indices, ligne, colonne)) return 2; // => si bateau coulé
        else if(Touche_Coule(indices, ligne, colonne) == 0) return 1; // => si bateau touché
    }
    else if(indices[ligne][colonne] == 0) return 0; // => si dans l'eau
    else return 3; // => si case déjà jouée

}

int Touche_Coule(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{
    int haut = 0, bas = 0, droite = 0, gauche = 0;

    if(indices[ligne - 1][colonne] <= 0 && indices[ligne][colonne + 1] <= 0 && indices[ligne + 1][colonne] <= 0 && indices[ligne][colonne - 1] <= 0) // CAS bateau 1 case
    {
        return 1; // => coulé
    }

    else if(indices[ligne - 1][colonne] == 1 || indices[ligne][colonne + 1] == 1 || indices[ligne + 1][colonne] == 1 || indices[ligne][colonne - 1] == 1) // CAS bateau touché pas encore coulé
    {
        return 0; // => touché
    }


    if(indices[ligne - 1][colonne] >= 2) haut = 1; // >= 2 A CAUSE DE ACTU_INDICES
    if(indices[ligne + 1][colonne] >= 2) bas = 1;
    if(indices[ligne][colonne + 1] >= 2) droite = 1;
    if(indices[ligne][colonne - 1] >= 2) gauche = 1;

    if(haut)
    {
        int i = ligne - 1, j = colonne;
        while(indices[i][j] >= 2) i--;
        if(indices[i][j] == 1) return 0; // => touché
        else
        {
            i = ligne + 1;
            if(indices[i][j] <= 0) return 1; // => coulé
            else
            {
                while(indices[i][j] >= 2) i++;
                if(indices[i][j] == 1) return 0; // => touché
                else return 1; // => coulé
            }
        }
    }

    else if(bas)
    {
        int i = ligne + 1, j = colonne;
        while(indices[i][j] >= 2) i++;
        if(indices[i][j] == 1) return 0; // => touché
        else
        {
            i = ligne - 1;
            if(indices[i][j] <= 0) return 1; // => coulé
            else
            {
                while(indices[i][j] >= 2) i--;
                if(indices[i][j] == 1) return 0; // => touché
                else return 1; // => coulé
            }
        }
    }

    else if(droite)
    {
        int i = ligne, j = colonne + 1;
        while(indices[i][j] >= 2) j++;
        if(indices[i][j] == 1) return 0; // => touché
        else
        {
            j = colonne - 1;
            if(indices[i][j] <= 0) return 1; // => coulé
            else
            {
                while(indices[i][j] >= 2) j--;
                if(indices[i][j] == 1) return 0; // => touché
                else return 1; // => coulé
            }
        }
    }

    else if(gauche)
    {
        int i = ligne, j = colonne - 1;
        while(indices[i][j] >= 2) j--;
        if(indices[i][j] == 1) return 0; // => touché
        else
        {
            j = colonne + 1;
            if(indices[i][j] <= 0) return 1; // => coulé
            else
            {
                while(indices[i][j] >= 2) j++;
                if(indices[i][j] == 1) return 0; // => touché
                else return 1; // => coulé
            }
        }
    }
}

void Actu_indices(int indices[INDICES_L][INDICES_C])
{
    int i = 0, j = 0;
    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            if(indices[i][j] == 2)
            {
                if(Touche_Coule(indices, i, j)) indices[i][j] = 3;
            }
        }
    }
}

void Actu_grille(int indices[INDICES_L][INDICES_C], char grille[GRILLE_L][GRILLE_C])
{
    int i = 0, j = 0;
    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            if(indices[i][j] == 2) grille[(i - 1) * 2][(j * 2) - 1] = 'x'; // => touché
            else if(indices[i][j] == 3) grille[(i - 1) * 2][(j * 2) - 1] = 'X'; // => coulé
            else if(indices[i][j] == -1) grille[(i - 1) * 2][(j * 2) - 1] = 'o'; // => dans l'eau
            else if(indices[i][j] == 1) grille[(i - 1) * 2][(j * 2) - 1] = '@'; // => bateau joueur
        }
    }
}

