/*
    BACHARELADO MATEMÁTICA - UNIVERSIDADE POSITIVO / CRUZEIRO DO SUL (2024-2026)
    Biblioteca de funções matemáticas para a Linguagem C/C++
    Autor: Giovanni de Almeida Costa - RGM 38153386
    Repositório: https://github.com/GiovanniAlmeidaCosta/BachareladoMatematica/tree/main

    Módulo: mathgac_numeros.h
    Descrição: Teoria dos Números, Primalidade, Fatoração e Crivos.
*/

#ifndef MATHGAC_NUMEROS_H_INCLUDED
#define MATHGAC_NUMEROS_H_INCLUDED

#include "mathgac_defs.h"

/* ========================================================================= */
/* 1. ARITMÉTICA ELEMENTAR, DIVISIBILIDADE E FATORAÇÃO                       */
/* ========================================================================= */

/* Soma de todos os divisores próprios de um inteiro */
int sum_of_divisors(int number);

/* Verifica se um inteiro é perfeito (sum_of_divisors(n) == n) */
int is_perfect_number(int number);

/* Fatorial iterativo de um inteiro n >= 0 */
unsigned long long factorial(int n);

/* Máximo Divisor Comum via Algoritmo de Euclides */
int mdc(int a, int b);

/* Mínimo Múltiplo Comum */
int mmc(int a, int b);

/* Fatoração canônica em fatores primos: n = p1^a1 * p2^a2 * ... */
void fatorar(int n, Fator fatores[], int *tamanho);


/* ========================================================================= */
/* 2. TESTES INDIVIDUAIS DE PRIMALIDADE                                      */
/* ========================================================================= */

/**
 * Teste de primalidade por divisões sucessivas (Trial Division com passo 6k +/- 1).
 * Complexidade Temporal: O(sqrt(n))
 * Memória Auxiliar: O(1)
 */
int is_prime_trial(int n);

/**
 * Teste de primalidade determinístico de Miller-Rabin para inteiros de 32 bits.
 * Avalia as bases a in {2, 7, 61}, provado sem falsos positivos para n < 2^32.
 * Complexidade Temporal: O(log n)
 * Memória Auxiliar: O(1)
 */
int is_prime_miller_rabin(int n);

/**
 * Função primária de teste: utiliza abordagem híbrida de alta performance.
 * Resolve números pequenos por trial division e grandes por Miller-Rabin.
 */
int is_prime(int n);


/* ========================================================================= */
/* 3. CRIVO DE ERATÓSTENES (GERENCIAMENTO MANUAL)                            */
/* ========================================================================= */

/**
 * Aloca dinamicamente um vetor de inteiros onde crivo[p] == 1 se p for primo.
 * Complexidade Temporal: O(n * log(log(n)))
 * Complexidade Espacial: O(n)
 * Retorna ponteiro para o vetor ou NULL em caso de erro.
 */
int* gerar_crivo_primos(int limit);

/**
 * Consulta em O(1) se n é primo a partir de um crivo manual previamente alocado.
 * Retorna 1 se primo, 0 se composto, -1 se fora do limite ou crivo nulo.
 */
int is_prime_crivo(int n, const int* crivo_array, int crivo_limite);


/* ========================================================================= */
/* 4. CRIVO COMPARTILHADO INTERNO (CACHE GLOBAL AUTOMÁTICO)                  */
/* ========================================================================= */

/* Pré-aloca ou redimensiona o crivo interno estático da biblioteca */
void mathgac_numeros_init_sieve(int max_limit);

/* Desaloca a memória do crivo interno estático */
void mathgac_numeros_free_sieve(void);


/* ========================================================================= */
/* 5. DISTRIBUIÇÃO ANALÍTICA E ESTATÍSTICA DE NÚMEROS PRIMOS                 */
/* ========================================================================= */

/* Contagem exata de primos até 'num', equivalente à função contadora pi(x) */
int primeCount(int num);

/* Retorna a posição ordinal do primo 'num' na reta numérica (ou pi(num)) */
int primePosition(int num);

/* Encontra o n-ésimo número primo p_n utilizando estimativas assintóticas */
int primeAtPosition(int num);

/* Emite relatório analítico comparando p_n com n*ln(n) e estimativas de 2ª ordem */
void fullPrimeReport(int num);

/* Mapeia a densidade de primos em intervalos regulares de largura 'inter' até 'num' */
void intervals(int num, int inter);

/**
 * Localiza todos os pares de Primos Gêmeos (p, p + 2) no intervalo [start, end].
 * Fundamentação: Conjectura dos Primos Gêmeos e convergência da Constante de Brun.
 */
void findTwinPrimes(int start, int end);

/**
 * Localiza todos os Tripletos de Primos no intervalo [start, end].
 * Abrange o caso único (3, 5, 7) e as configurações admissíveis (p, p+2, p+6) e (p, p+4, p+6).
 */
void findPrimeTriplets(int start, int end);

#endif // MATHGAC_NUMEROS_H_INCLUDED