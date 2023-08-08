#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//////////////////// MACROS ///////////////////////////

#define TPOS 4

#define GRILLE_L 19
#define GRILLE_C 20
#define INDICES_L 12
#define INDICES_C 12


//////////////////// STRUCTURES ///////////////////////////

typedef struct Tir Tir;
struct Tir
{
    int ligne;
    int colonne;
};

typedef struct Bateau Bateau;
struct Bateau
{
    int taille;
    int nombre;
};

#endif // MACROS_H_INCLUDED
