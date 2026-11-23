#ifndef MATHGAC_DEFS_H_INCLUDED
#define MATHGAC_DEFS_H_INCLUDED

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* CONSTANTES */
#define PI  3.14159265358979323846
#define E   2.71828182845904523536
#define PHI 1.61803398874989484820

#define MAX_FATORES 32

/* ESTRUTURA PARA ARMAZENAR OS FATORES */
typedef struct {
    int valor;
    int quantidade;
} Fator;

#endif // MATHGAC_DEFS_H_INCLUDED