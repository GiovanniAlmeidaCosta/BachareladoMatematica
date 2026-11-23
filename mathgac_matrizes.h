#ifndef MATHGAC_MATRIZES_H_INCLUDED
#define MATHGAC_MATRIZES_H_INCLUDED

/* Aloca dinamicamente uma matriz linhas x colunas. Retorna 1 se sucesso, 0 se falha. */
int aloca_matriz(double ***mat, int linhas, int colunas);

/* Libera a memória de uma matriz alocada. */
void libera_matriz(double ***mat, int linhas);

/* Preenche a matriz via scanf. */
void preenche_matriz(double **mat, int linhas, int colunas);

/* Imprime a matriz no stdout. */
void imprime_matriz(double **mat, int linhas, int colunas);

/* Soma C = A + B */
void soma_matrizes(double **A, double **B, double **C, int linhas, int colunas);

/* Multiplicação matricial C = A * B */
void multiplica_matrizes(double **A, double **B, double **C, int lA, int cA, int cB);

/* Determinante para ordem 2 */
double determinante_matriz(double **mat, int n);

/* Inversa de matriz 2x2. Retorna 1 se invertível, 0 caso singular. */
int matriz_inversa(double **mat, double **inv, int n);

#endif // MATHGAC_MATRIZES_H_INCLUDED