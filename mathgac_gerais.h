#ifndef MATHGAC_GERAIS_H_INCLUDED
#define MATHGAC_GERAIS_H_INCLUDED

/* Retorna o número de dígitos de um número (inteiro não negativo) */
int count_digits(unsigned long long num);

/* Verifica se um número é palíndromo */
int is_palindrome(int num);

/* Verifica se 'divisor' é de fato divisor de 'number' */
int is_divisor(int number, int divisor);

#endif // MATHGAC_GERAIS_H_INCLUDED