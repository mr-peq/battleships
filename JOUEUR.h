#ifndef JOUEUR_H_INCLUDED
#define JOUEUR_H_INCLUDED

#include "macros.h"

// || Lecture ||

int Lire(char *position, int taille);
void Erase_buffer();
char *MAJ(char position[], int taille); // transforme les min en MAJ
int Entree_Choix(char choix[TPOS]); // pour vérifier que l'utilisateur a bien entré '1' à '4' comme choix


// || Mécaniques ||

int Entree_Invalide(char position[], int taille, Tir *tir); // Vérifie que la position donnée est bien (A/J | 1/10)
                                                         // SI OUI: retourne 1 ET assigne la position au Tir Joueur

void Placement(int indices[INDICES_L][INDICES_C], Bateau *cuirasse, Bateau *croiseur, Bateau *torpilleur, Bateau *sous_marin);
    // Demande au joueur de placer ses bateaux sur la matrice d'indices
    // APPELS : Entree_Choix(), Lire(), *MAJ(), Erreur_Entree(), Bateau_Adjacent(), Entree_Invalide(), Placement_Invalide()

int Placement_Invalide(int indices[INDICES_L][INDICES_C], int ligne, int colonne, Bateau bateau, int direction);
    // Vérifie si l'espace choisi par le joueur pour poser son bateau est valide.
            // Si 0 : Placement valide
            // Si 1 : Dépassement de la grille
            // Si 2 : Un bateau est déjà présent dans l'espace choisi
            // Si 3 : Un bateau est adjacent à l'espace choisi
    // APPEL : Bateau_Adjacent()
    // APPELEE PAR : Placement()

int Bateau_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne);

int Case_Visee(int indices[INDICES_L][INDICES_C], int ligne, int colonne); // Vérifie ce que contient la case visée par le joueur
                                                                             // Si 0 : dans l'eau
   // APPEL : Touche_Coule()                                                 // Si 1 : touché
                                                                             // Si 2 : coulé
                                                                             // Si 3 : case déjà jouée


int Touche_Coule(int indices[INDICES_L][INDICES_C], int ligne, int colonne); // Si un tir joueur à touché un bateau, vérifie si celui-ci est coulé. 0 = touché, 1 = coulé
   // APPELEE PAR : Case_Visee()
   // APPEL : Bateau_Adjacent()

void Actu_indices(int indices[INDICES_L][INDICES_C]); // Transforme les '2' en '3' si un bateau est coulé

void Actu_grille(int indices[INDICES_L][INDICES_C], char grille[GRILLE_L][GRILLE_C]);


#endif // JOUEUR_H_INCLUDED
