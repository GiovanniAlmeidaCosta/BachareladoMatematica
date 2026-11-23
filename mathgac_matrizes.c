#include "mathgac_matrizes.h"
#include <stdio.h>
#include <stdlib.h>

int aloca_matriz(double ***mat, int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0 || mat == NULL) return 0;

    *mat = (double **)malloc(linhas * sizeof(double *));
    if (*mat == NULL) return 0;

    for (int i = 0; i < linhas; i++) {
        (*mat)[i] = (double *)malloc(colunas * sizeof(double));
        if ((*mat)[i] == NULL) {
            // Rollback para evitar vazamento de memória
            for (int j = 0; j < i; j++) {
                free((*mat)[j]);
            }
            free(*mat);
            *mat = NULL;
            return 0;
        }
    }
    return 1;
}

void libera_matriz(double ***mat, int linhas) {
    if (mat == NULL || *mat == NULL) return;
    for (int i = 0; i < linhas; i++) {
        if ((*mat)[i] != NULL) {
            free((*mat)[i]);
        }
    }
    free(*mat);
    *mat = NULL;
}

void preenche_matriz(double **mat, int linhas, int colunas) {
    if (!mat) return;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (scanf("%lf", &mat[i][j]) != 1) {
                mat[i][j] = 0.0;
            }
        }
    }
}

void imprime_matriz(double **mat, int linhas, int colunas) {
    if (!mat) return;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%.2lf ", mat[i][j]);
        }
        printf("\n");
    }
}

void soma_matrizes(double **A, double **B, double **C, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplica_matrizes(double **A, double **B, double **C, int lA, int cA, int cB) {
    for (int i = 0; i < lA; i++) {
        for (int j = 0; j < cB; j++) {
            C[i][j] = 0.0;
            for (int k = 0; k < cA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double determinante_matriz(double **mat, int n) {
    if (mat == NULL) return 0.0;
    if (n == 2) {
        return (mat[0][0] * mat[1][1]) - (mat[0][1] * mat[1][0]);
    }
    return 0.0;
}

int matriz_inversa(double **mat, double **inv, int n) {
    if (mat == NULL || inv == NULL) return 0;
    if (n == 2) {
        double det = determinante_matriz(mat, n);
        if (det == 0.0) {
            return 0; // Singular
        }
        inv[0][0] =  mat[1][1] / det;
        inv[0][1] = -mat[0][1] / det;
        inv[1][0] = -mat[1][0] / det;
        inv[1][1] =  mat[0][0] / det;
        return 1;
    }
    return 0;
}