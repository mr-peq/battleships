#include "Affichage.h"

void Menu_Demarrage()
{
    printf("=== DEBUT DE LA PARTIE ===\n\n");
    printf("Vous devez placer vos bateaux sur votre grille.\n");
    printf("Celle-ci contient 10 lignes allant de 'A' à 'J', et 10 colonnes de '1' à '10'\n\n");

    printf("Votre objectif sera de détruire tous les bateaux de votre adversaire avant que\ncelui-ci ne détruise tous les votres.\n");
    printf("Il existe plusieurs types de bateaux, chacun ayant une taille différente.\n\n");
    printf("Voici ceux dont vous disposez : \n\n");

}

void Affiche_bateaux(Bateau cuirasse, Bateau croiseur, Bateau torpilleur, Bateau sous_marin)
{
    printf("x%d Cuirassés (4 cases)     x%d Croiseurs (3 cases)\n", cuirasse.nombre, croiseur.nombre);
    printf("x%d Torpilleurs (2 cases)   x%d Sous-marins(1 case)\n", torpilleur.nombre, sous_marin.nombre);
}

void Erreur_Entree()
{
    printf("\nJe n'ai pas compris votre choix\n");
    printf("Veuillez entrer la ligne (de 'a' à 'j') et la colonne (de '1' à '10') du tir\n");
    printf("Si vous mettez des espaces ou des caractères chelous faudra recommencer.\n");
}

void Init_indices(int indices[INDICES_L][INDICES_C])
{
    int i = 0, j = 0;

    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            indices[i][j] = 0;
        }
    }
}

void Affiche_indices(int indices[INDICES_L][INDICES_C])
{
    int i = 0, j = 0;

    for(i = 0; i < INDICES_L; i++)
    {
        for(j = 0; j < INDICES_C; j++)
        {
            printf("%d ", indices[i][j]);
        }
        printf("\n");
    }
}

void Init_grille(char grille[GRILLE_L][GRILLE_C])
{
    int i = 0, j = 0;
    char c = 'A';
    char nb = '1';

    for(i = 0; i < GRILLE_L; i++) // Lignes de A à J
    {
        if(i % 2 == 0)
        {
            grille[i][j] = c;
            c++;
        }
        else grille[i][j] = '-';
    }

    for(i = 0; i < GRILLE_L; i++) // Cases centrales
    {
        for(j = 1; j < GRILLE_C; j++)
        {
            if(j % 2 == 0)
            {
                grille[i][j] = '|';
            }
            else if(i % 2 != 0) grille[i][j] = '-';
            else grille[i][j] = '*';
        }
    }

}

void Affiche_grille(char grille[GRILLE_L][GRILLE_C])
{
    printf("_ 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10\n");
    int i = 0, j = 0;
    for(i = 0; i < GRILLE_L; i++)
    {
        for(j = 0; j < GRILLE_C; j++)
        {
            printf("%c ", grille[i][j]);
        }
        printf("\n");
    }
}





