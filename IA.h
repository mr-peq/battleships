#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED

#include "macros.h"

void IA_Placement(int indices[INDICES_L][INDICES_C], Bateau *cuirasse, Bateau *croiseur, Bateau *torpilleur, Bateau *sous_marin);

int IA_Placement_Invalide(int indices[INDICES_L][INDICES_C], int ligne, int colonne, Bateau bateau, int direction);

int IA_Case_Visee(int indices[INDICES_L][INDICES_C], int ligne, int colonne);

int IA_Touche_Coule(int indices[INDICES_L][INDICES_C], int ligne, int colonne);
// Si un tir a "touché"(1), vérifie si le bateau est coulé ( => appelée par IA_Case_Visee() )

int Search(int indices[INDICES_L][INDICES_C], int *l, int *c);
// Vérifie s'il existe un '2' (bateau joueur touché) quelque part dans la grille. Si oui, renvoie ses coordonnées dans 'l' et 'c'

int Destroy(int indices[INDICES_L][INDICES_C], int *l, int *c);
// 0 = dans l'eau, 1 = touché, 2 = coulé

int IA_Bateau_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne);

int IA_Bateau_Coule_Adjacent(int indices[INDICES_L][INDICES_C], int ligne, int colonne);

void IA_Actu_indices(int indices[INDICES_L][INDICES_C]); // Transforme les '2' en '3' si un bateau est coulé

void IA_Actu_grille(int indices[INDICES_L][INDICES_C], char grille[GRILLE_L][GRILLE_C]);

#endif // IA_H_INCLUDED
