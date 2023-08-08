#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

#include "macros.h"

void Menu_Demarrage();
void Affiche_bateaux(Bateau cuirasse, Bateau croiseur, Bateau torpilleur, Bateau sous_marin);
void Erreur_Entree(); // si la position donnée n'est pas valable (A/J | 1/10)

/////////////// |Indices| /////////////////

void Init_indices(int indices[INDICES_L][INDICES_C]);
void Affiche_indices(int indices[INDICES_L][INDICES_C]);

////////////// |Grille| /////////////////

void Init_grille(char grille[GRILLE_L][GRILLE_C]);
void Affiche_grille(char grille[GRILLE_L][GRILLE_C]);

#endif // AFFICHAGE_H_INCLUDED
