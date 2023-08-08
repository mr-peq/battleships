#include "IA.h"

void IA_Placement(int indices[INDICES_L][INDICES_C], Bateau *cuirasse, Bateau *croiseur, Bateau *torpilleur, Bateau *sous_marin)
{
    int type_bateau = (rand() % 4) +1;

    Tir placement;
    placement.ligne = 0, placement.colonne = 0;

    switch(type_bateau)
    {
        case 1: // CUIRASSÉ
            if(cuirasse->nombre == 0) break;
            else
            {
                placement.ligne = (rand() % 10) + 1;
                placement.colonne = (rand() % 10) + 1;

                if(indices[placement.ligne][placement.colonne] == 1) break; // tant que la case est occupée OU qu'il y a un bateau adjacent à la case choisie

                if(IA_Bateau_Adjacent(indices, placement.ligne, placement.colonne)) break;
            }

            int direction = (rand() % 4) +1;
            int l = placement.ligne, c = placement.colonne;

            switch(direction)
            {
            case 1: // HAUT
                if(IA_Placement_Invalide(indices, l, c, *cuirasse, 1)) break;
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1, indices[l - 2][c] = 1, indices[l - 3][c] = 1; // on met toutes les cases choisies à 1
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 2: // BAS
                if(IA_Placement_Invalide(indices, l, c, *cuirasse, 2)) break;
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1, indices[l + 2][c] = 1, indices[l + 3][c] = 1; // on met toutes les cases choisies à 1
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(IA_Placement_Invalide(indices, l, c, *cuirasse, 3)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1, indices[l][c - 2] = 1, indices[l][c - 3] = 1; // on met toutes les cases choisies à 1
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(IA_Placement_Invalide(indices, l, c, *cuirasse, 4)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1, indices[l][c + 2] = 1, indices[l][c + 3] = 1; // on met toutes les cases choisies à 1
                    cuirasse->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 2: // CROISEUR
            if(croiseur->nombre == 0) break;
            else
            {
                placement.ligne = (rand() % 10) + 1;
                placement.colonne = (rand() % 10) + 1;

                if(indices[placement.ligne][placement.colonne] == 1) break; // tant que la case est occupée OU qu'il y a un bateau adjacent à la case choisie

                if(IA_Bateau_Adjacent(indices, placement.ligne, placement.colonne)) break;
            }

            direction = (rand() % 4) +1;
            l = placement.ligne, c = placement.colonne;

            switch(direction)
            {
            case 1: // HAUT
                if(IA_Placement_Invalide(indices, l, c, *croiseur, 1)) break;
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1, indices[l - 2][c] = 1; // on met toutes les cases choisies à 1
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 2: // BAS
                if(IA_Placement_Invalide(indices, l, c, *croiseur, 2)) break;
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1, indices[l + 2][c] = 1; // on met toutes les cases choisies à 1
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(IA_Placement_Invalide(indices, l, c, *croiseur, 3)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1, indices[l][c - 2] = 1; // on met toutes les cases choisies à 1
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(IA_Placement_Invalide(indices, l, c, *croiseur, 4)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1, indices[l][c + 2] = 1; // on met toutes les cases choisies à 1
                    croiseur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 3: // TORPILLEUR
            if(torpilleur->nombre == 0) break;
            else
            {
                placement.ligne = (rand() % 10) + 1;
                placement.colonne = (rand() % 10) + 1;

                if(indices[placement.ligne][placement.colonne] == 1) break; // tant que la case est occupée OU qu'il y a un bateau adjacent à la case choisie

                if(IA_Bateau_Adjacent(indices, placement.ligne, placement.colonne)) break;
            }

            direction = (rand() % 4) +1;
            l = placement.ligne, c = placement.colonne;

            switch(direction)
            {
            case 1: // HAUT
                if(IA_Placement_Invalide(indices, l, c, *torpilleur, 1)) break;
                else
                {
                    indices[l][c] = 1, indices[l - 1][c] = 1; // on met toutes les cases choisies à 1
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    return 44;
                }

            case 2: // BAS
                if(IA_Placement_Invalide(indices, l, c, *torpilleur, 2)) break;
                else
                {
                    indices[l][c] = 1, indices[l + 1][c] = 1; // on met toutes les cases choisies à 1
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 3: // GAUCHE
                if(IA_Placement_Invalide(indices, l, c, *torpilleur, 3)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c - 1] = 1; // on met toutes les cases choisies à 1
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }

            case 4: // DROITE
                if(IA_Placement_Invalide(indices, l, c, *torpilleur, 4)) break;
                else
                {
                    indices[l][c] = 1, indices[l][c + 1] = 1; // on met toutes les cases choisies à 1
                    torpilleur->nombre--; // il reste 1 cuirassé de moins à poser
                    break;
                }
            }
        break;

    case 4: // SOUS-MARIN
            if(sous_marin->nombre == 0) break;
            else
            {
                placement.ligne = (rand() % 10) + 1;
                placement.colonne = (rand() % 10) + 1;

                if(indices[placement.ligne][placement.colonne] == 1) break;// SI la case est occupée
                if(IA_Bateau_Adjacent(indices, placement.ligne, placement.colonne)) break;
            }

            indices[placement.ligne][placement.colonne] = 1;
            sous_marin->nombre--;
            break;
    }
}

int IA_Placement_Invalide(int indices[INDICES_L][INDICES_C], int ligne, int colonne, Bateau bateau, int direction)
{
    int l = ligne, c = colonne;
    int i;

    switch(direction)
    {
    case 1: // HAUT
        if(l - (bateau.taille - 1) <= 1) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne - i][colonne] == 1) return 2;
        }

        int vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(IA_Bateau_Adjacent(indices, l - i, c)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 2: // BAS
        if(l + (bateau.taille - 1) >= 11) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne + i][colonne] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(IA_Bateau_Adjacent(indices, l + i, c)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 3: // GAUCHE
        if(c - (bateau.taille - 1) <= 1) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne][colonne - i] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(IA_Bateau_Adjacent(indices, l, c - i)) vrai++;
        }

        if(vrai) return 3;
        else return 0;

    case 4: // DROITE
        if(c + (bateau.taille - 1) >= 11) return 1;
        for(i = 0; i < bateau.taille; i++)
        {
            if(indices[ligne][colonne + i] == 1) return 2;
        }

        vrai = 0;
        for(i = 1; i < bateau.taille; i++)
        {
            if(IA_Bateau_Adjacent(indices, l, c + i)) vrai++;
        }

        if(vrai) return 3;
        else return 0;
    }
}

int IA_Case_Visee(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{
    if(indices[ligne][colonne] == 1)
    {
        if(IA_Touche_Coule(indices, ligne, colonne)) return 2; // => si bateau coulé AVEC CE TIR
        else if(IA_Touche_Coule(indices, ligne, colonne) == 0) return 1; // => si bateau touché AVEC CE TIR
    }
    else return 0; // => si dans l'eau

    // ATTENTION !! \\ CAS '-1'/ '3' A EXCLURE DANS LE MAIN (REROLL RAND())
}

int IA_Touche_Coule(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
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


    if(indices[ligne - 1][colonne] >= 2) haut = 1;
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

int Search(int indices[INDICES_L][INDICES_C], int *l, int *c)
{
    int i = 0, j = 0;
    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            if(indices[i][j] == 2)
            {
                *l = i;
                *c = j;
                return 1;
            }
        }
    }
    return 0;
}

int Destroy(int indices[INDICES_L][INDICES_C], int *l, int *c)
{
    int ligne = *l, colonne = *c;

        // 2 CASES '2' COTES A COTES

    if(indices[ligne + 1][colonne] == 2) // CAS BATEAU VERTICAL (case '2' en dessous)
    {
        int position = ligne;

        if(indices[position + 3][colonne] == 3 || indices[position + 2][colonne] == -1) // BATEAU COULÉ A n+2 : VAS VERS LE HAUT /ou\ CASE VIDE DEJA EXPLO A n+1 : VAS VERS LE HAUT
        {
            while(indices[position][colonne] != 1) position--; // on monte (le bas du bateau est déjà détruit) tant qu'on a pas trouvé la prochaine case à viser '1' (bateau non touché)

            indices[position][colonne] = 2; // on change le '1' (bateau J non touché) en '2' (bateau J touché)
            *l = position; // on donne les valeurs de la case visée
            *c = colonne;

            if(indices[position - 1][colonne] == 1) // s'il reste une case bateau J non touchée en dessous
            {
                return 1; // => touché
            }
            else return 2; // => coulé
        }

        else // PAS DE BATEAU COULÉ A n+2 /ni\ DE CASE VIDE DEJA EXPLO A n+1 : VAS VERS LE BAS
        {
            while(indices[position][colonne] == 2) position++;

            if(indices[position][colonne] == 0)
            {
                if(indices[position + 1][colonne] == 3)
                {
                    position--; // on remonte sur le '2'
                    while(indices[position][colonne] == 2) position --;

                    indices[position][colonne] = 2;
                    *l = position; // on donne les valeurs de la case visée
                    *c = colonne;

                    if(indices[position - 1][colonne] == 1) return 1; // => touché
                    else return 2; // => coulé
                }

                else
                {
                    *l = position; // on donne les valeurs de la case visée
                    *c = colonne;
                    indices[position][colonne] = -1; // inexplo sans bateau devient explo sans bateau;
                    return 0; // => dans l'eau
                }

            }

            else if(indices[position][colonne] == -1)
            {
                position--;
                while(indices[position][colonne] == 2) position--;

                indices[position][colonne] = 2;
                *l = position; // on donne les valeurs de la case visée
                *c = colonne;

                if(indices[position - 1][colonne] == 1) return 1; // => touché
                else return 2; // => coulé
            }

            else
            {
                indices[position][colonne] = 2;
                *l = position; // on donne les valeurs de la case visée
                *c = colonne;

                if(indices[position + 1][colonne] == 1) return 1; // => touché
                else
                {
                    position = ligne;                                            //!!!//
                    while(indices[position][colonne] == 2) position--;
                    if(indices[position][colonne] == 1) return 1; // => touché
                    else return 2; // => coulé
                }
            }
        }
    }

    if(indices[ligne][colonne + 1] == 2) // CAS BATEAU HORIZONTAL (case '2' a droite)
    {
        int position = colonne;

        if(indices[ligne][position + 3] == 3 || indices[ligne][position + 2] == -1)
        {
            while(indices[ligne][position] != 1) position--;

            indices[ligne][position] = 2;
            *l = ligne;
            *c = position;

            if(indices[ligne][position - 1] == 1)
            {
                return 1; // => touché
            }
            else return 2; // => coulé
        }

        else
        {
            while(indices[ligne][position] == 2) position++;

            if(indices[ligne][position] == 0)
            {
                if(indices[ligne][position + 1] == 3)
                {
                    position--;
                    while(indices[ligne][position] == 2) position --;

                    indices[ligne][position] = 2;
                    *l = ligne;
                    *c = position;

                    if(indices[ligne][position - 1] == 1) return 1; // => touché
                    else return 2; // => coulé
                }

                else
                {
                    *l = ligne;
                    *c = position;
                    indices[ligne][position] = -1;
                    return 0; // => dans l'eau
                }

            }

            else if(indices[ligne][position] == -1)
            {
                position--;
                while(indices[ligne][position] == 2) position--;

                indices[ligne][position] = 2;
                *l = ligne;
                *c = position;

                if(indices[ligne][position - 1] == 1) return 1; // => touché
                else return 2; // => coulé
            }

            else
            {
                indices[ligne][position] = 2;
                *l = ligne;
                *c = position;

                if(indices[ligne][position + 1] == 1) return 1; // => touché
                else
                {
                    position = colonne;                                       ///!!!///
                    while(indices[ligne][position] == 2) position--;
                    if(indices[ligne][position] == 1) return 1; // => touché
                    else return 2; // => coulé
                }
            }
        }
    }

        // PAS DE CASE '2' A COTE DU '2' TROUVE

    else
    {
        int haut = 0, bas = 0, gauche = 0, droite = 0;

        if(indices[ligne - 1][colonne] != -1) haut = 1; // Si la case au-dessus du '2' n'a pas encore été visée par un tir, alors 'haut' = 1 (vrai). Sinon 'haut' reste à 0 (faux)
        if(indices[ligne + 1][colonne] != -1) bas = 2;  // RAPPEL : la case en question ne peut pas être un '2' (cas '2' et '2' adjacents déjà traités) ni un '3' (bateau adjacent coulé impossible)
        if(indices[ligne][colonne - 1] != -1) gauche = 3;
        if(indices[ligne][colonne + 1] != -1) droite = 4;

        int k = (rand() % 4) + 1; // Génération d'un nb aléatoire - options: 1/2/3/4 ('0' exclut grace à '+ 1')

        while(k != haut && k != bas && k != gauche && k != droite)
        {
            k = (rand() % 4) + 1; // Tant que le nb aléatoire ne correspond pas à l'une des directions, on en génère un nouveau
        }

        if(k == haut) // HAUT \\ Si 'haut' est vrai (on a pas encore tiré au dessus) et que le nb aléatoire a pris sa valeur
        {
            *l = ligne - 1; // on retourne les coordonnées du tir
            *c = colonne;
            if(indices[ligne - 1][colonne] == 0)
            {
                indices[ligne - 1][colonne] = -1;
                return 0; // => dans l'eau
            }
            else
            {
                indices[ligne - 1][colonne] = 2;
                if(IA_Touche_Coule(indices, ligne, colonne)) return 2; // => coulé
                else return 1; // => touché
            }
        }

        else if(k == bas) // BAS
        {
            *l = ligne + 1;
            *c = colonne;
            if(indices[ligne + 1][colonne] == 0)
            {
                indices[ligne + 1][colonne] = -1;
                return 0; // => dans l'eau
            }
            else
            {
                indices[ligne + 1][colonne] = 2;
                if(IA_Touche_Coule(indices, ligne, colonne)) return 2; // => coulé
                else return 1; // => touché
            }
        }

        else if(k == gauche) // GAUCHE
        {
            *l = ligne;
            *c = colonne - 1;
            if(indices[ligne][colonne - 1] == 0)
            {
                indices[ligne][colonne - 1] = -1;
                return 0; // => dans l'eau
            }
            else
            {
                indices[ligne][colonne - 1] = 2;
                if(IA_Touche_Coule(indices, ligne, colonne)) return 2; // => coulé
                else return 1; // => touché
            }
        }

        else if(k == droite) // DROITE
        {
            *l = ligne;
            *c = colonne + 1;
            if(indices[ligne][colonne + 1] == 0)
            {
                indices[ligne][colonne + 1] = -1;
                return 0; // => dans l'eau
            }
            else
            {
                indices[ligne][colonne + 1] = 2;
                if(IA_Touche_Coule(indices, ligne, colonne)) return 2; // => coulé
                else return 1; // => touché
            }
        }
    }
}

int IA_Bateau_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{
    if(indices[ligne + 1][colonne] == 1) return 1;
    if(indices[ligne - 1][colonne] == 1) return 1;
    if(indices[ligne][colonne + 1] == 1) return 1;
    if(indices[ligne][colonne - 1] == 1) return 1;

    else return 0;
}

int IA_Bateau_Coule_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne)
{
    if(indices[ligne + 1][colonne] == 3) return 1;
    if(indices[ligne - 1][colonne] == 3) return 1;
    if(indices[ligne][colonne + 1] == 3) return 1;
    if(indices[ligne][colonne - 1] == 3) return 1;

    else return 0;
}

void IA_Actu_indices(int indices[INDICES_L][INDICES_C])
{
    int i = 0, j = 0;
    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            if(indices[i][j] == 2)
            {
                if(IA_Touche_Coule(indices, i, j)) indices[i][j] = 3;
            }
        }
    }
}

void IA_Actu_grille(int indices[INDICES_L][INDICES_C], char grille[GRILLE_L][GRILLE_C])
{
    int i = 0, j = 0;
    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            if(indices[i][j] == 2) grille[(i - 1) * 2][(j * 2) - 1] = 'x'; // => touché
            else if(indices[i][j] == 3) grille[(i - 1) * 2][(j * 2) - 1] = 'X'; // => coulé
            else if(indices[i][j] == -1) grille[(i - 1) * 2][(j * 2) - 1] = 'o'; // => dans l'eau
        }
    }
}
