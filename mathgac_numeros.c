/*
    BACHARELADO MATEMÁTICA - UNIVERSIDADE POSITIVO / CRUZEIRO DO SUL (2024-2026)
    Biblioteca de funções matemáticas para a Linguagem C/C++
    Autor: Giovanni de Almeida Costa - RGM 38153386
    Repositório: https://github.com/GiovanniAlmeidaCosta/BachareladoMatematica/tree/main

    Módulo: mathgac_numeros.c
    Implementação: Aritmética Modular, Primalidade, Crivos e Análise Assintótica.
*/

#include "mathgac_numeros.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

/* ========================================================================= */
/* GERENCIAMENTO DO CACHE DO CRIVO DE ERATÓSTENES                           */
/* ========================================================================= */

static int* _sieve_cache = NULL;
static int _sieve_limit = 0;

static int _mathgac_sieve_ensure_initialized(int required_limit) {
    if (required_limit <= 0) return 0;
    if (_sieve_cache != NULL && required_limit <= _sieve_limit) {
        return 1;
    }

    if (_sieve_cache != NULL) {
        free(_sieve_cache);
        _sieve_cache = NULL;
        _sieve_limit = 0;
    }

    _sieve_cache = gerar_crivo_primos(required_limit);
    if (_sieve_cache == NULL) {
        return 0;
    }
    _sieve_limit = required_limit;
    return 1;
}

void mathgac_numeros_init_sieve(int max_limit) {
    _mathgac_sieve_ensure_initialized(max_limit);
}

void mathgac_numeros_free_sieve(void) {
    if (_sieve_cache != NULL) {
        free(_sieve_cache);
        _sieve_cache = NULL;
        _sieve_limit = 0;
    }
}

/* ========================================================================= */
/* 1. ARITMÉTICA ELEMENTAR E FATORAÇÃO                                       */
/* ========================================================================= */

int sum_of_divisors(int number) {
    if (number <= 1) return 0;
    int sum = 1;
    for (int i = 2; (long long)i * i <= number; i++) {
        if (number % i == 0) {
            sum += i;
            if (i != number / i) {
                sum += number / i;
            }
        }
    }
    return sum;
}

int is_perfect_number(int number) {
    return sum_of_divisors(number) == number;
}

unsigned long long factorial(int n) {
    if (n < 0) return 0;
    unsigned long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return (a < 0) ? -a : a;
}

int mmc(int a, int b) {
    if (a == 0 || b == 0) return 0;
    int div = mdc(a, b);
    return abs((a / div) * b);
}

/**
 * Fatoração Inteira Única (Teorema Fundamental da Aritmética).
 * Decompõe n em fatores primos p_i e seus respectivos expoentes a_i.
 */
void fatorar(int n, Fator fatores[], int *tamanho) {
    *tamanho = 0;
    if (n <= 1) return;

    for (int i = 2; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            int count = 0;
            while (n % i == 0) {
                n /= i;
                count++;
            }
            if (*tamanho < MAX_FATORES) {
                fatores[*tamanho].valor = i;
                fatores[*tamanho].quantidade = count;
                (*tamanho)++;
            }
        }
    }
    if (n > 1) {
        if (*tamanho < MAX_FATORES) {
            fatores[*tamanho].valor = n;
            fatores[*tamanho].quantidade = 1;
            (*tamanho)++;
        }
    }
}

/* ========================================================================= */
/* 2. TESTES DE PRIMALIDADE: TRIAL DIVISION E MILLER-RABIN                   */
/* ========================================================================= */

/**
 * Teste por Divisões Sucessivas com passo 6k +/- 1:
 * Todo primo p > 3 pertence à classe de equivalência 6k +/- 1.
 * Calcula a raiz quadrada limit = sqrt(n) uma única vez para evitar
 * multiplicações redundantes no laço.
 */
int is_prime_trial(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if ((n & 1) == 0 || n % 3 == 0) return 0;

    int limit = (int)sqrt(n);
    for (int i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

/* Exponenciação Modular Estável: calcula (base^exp) % mod em O(log exp) */
static unsigned long long _power_mod(unsigned long long base, unsigned long long exp, unsigned long long mod) {
    unsigned long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

/**
 * Teste de Miller-Rabin para uma base específica 'a':
 * Decompõe n - 1 = d * 2^s com d ímpar.
 * Verifica se a^d = 1 (mod n) ou a^(d * 2^r) = n - 1 (mod n).
 *
 * Prova de Não-Overflow: Como n <= 2^31 - 1, x < n, logo x * x < 4.61 * 10^18,
 * cabendo com folga no tipo unsigned long long de 64 bits (máx 1.84 * 10^19).
 */
static int _miller_test(int n, int a) {
    if (n % a == 0) return (n == a);

    int d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    unsigned long long x = _power_mod((unsigned long long)a, (unsigned long long)d, (unsigned long long)n);
    if (x == 1 || x == (unsigned long long)(n - 1)) return 1;

    for (int r = 1; r < s; r++) {
        x = (x * x) % (unsigned long long)n;
        if (x == (unsigned long long)(n - 1)) return 1;
    }
    return 0;
}

/**
 * Miller-Rabin Determinístico para inteiros de 32 bits:
 * A literatura matemática provou que testar as bases {2, 7, 61}
 * elimina completamente os pseudoprimos compostos para n < 2^32.
 */
int is_prime_miller_rabin(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if ((n & 1) == 0 || n % 3 == 0) return 0;

    const int bases[3] = {2, 7, 61};
    for (int i = 0; i < 3; i++) {
        if (n == bases[i]) return 1;
        if (!_miller_test(n, bases[i])) return 0;
    }
    return 1;
}

/**
 * Função primária híbrida:
 * Para n < 64, divisões sucessivas em cache L1 são mais rápidas que a montagem modular.
 * Para n >= 64, Miller-Rabin em O(log n) reduz centenas de operações para ~90 passos.
 */
int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if ((n & 1) == 0 || n % 3 == 0) return 0;
    if (n < 64) {
        return (n % 5 != 0 && n % 7 != 0);
    }
    return is_prime_miller_rabin(n);
}

/* ========================================================================= */
/* 3. CRIVO DE ERATÓSTENES                                                   */
/* ========================================================================= */

int* gerar_crivo_primos(int limit) {
    if (limit < 2) return NULL;

    int* is_prime_array = (int*)malloc((limit + 1) * sizeof(int));
    if (!is_prime_array) return NULL;

    for (int k = 0; k <= limit; k++) {
        is_prime_array[k] = 1;
    }
    is_prime_array[0] = 0;
    is_prime_array[1] = 0;

    for (int p = 2; (long long)p * p <= limit; p++) {
        if (is_prime_array[p]) {
            for (int i = p * p; i <= limit; i += p) {
                is_prime_array[i] = 0;
            }
        }
    }
    return is_prime_array;
}

int is_prime_crivo(int n, const int* crivo_array, int crivo_limite) {
    if (crivo_array == NULL || n < 0 || n > crivo_limite) {
        return -1;
    }
    return crivo_array[n];
}

/* ========================================================================= */
/* 4. ANÁLISE ESTATÍSTICA E DISTRIBUIÇÃO DOS PRIMOS                          */
/* ========================================================================= */

int primeCount(int num) {
    if (num < 2) return 0;
    if (!_mathgac_sieve_ensure_initialized(num)) return 0;
    int count = 0;
    for (int i = 2; i <= num; i++) {
        if (is_prime_crivo(i, _sieve_cache, _sieve_limit) == 1)
            count++;
    }
    return count;
}

int primePosition(int num) {
    if (num < 2) return 0;
    return primeCount(num);
}

/**
 * Busca pelo n-ésimo primo p_n:
 * Aplica o Teorema dos Números Primos para estimar uma cota superior:
 * p_n \approx n * (ln(n) + ln(ln(n)))
 */
int primeAtPosition(int num) {
    if (num <= 0) return -1;

    double est = (num == 1) ? 2.0 : (double)num * (log((double)num) + log(log(num > 2 ? (double)num : 3.0)) * 1.3);
    int estimated_limit = (est < 100.0) ? 100 : (int)est;

    if (!_mathgac_sieve_ensure_initialized(estimated_limit)) return -1;

    int i = 2;
    int count = 0;
    while (count < num) {
        if (i <= _sieve_limit) {
            if (is_prime_crivo(i, _sieve_cache, _sieve_limit) == 1) count++;
        } else {
            if (is_prime(i)) count++;
        }
        if (count < num) i++;
    }
    return i;
}