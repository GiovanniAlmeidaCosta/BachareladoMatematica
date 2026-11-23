#ifndef MATHGAC_FIBONACCI_H_INCLUDED
#define MATHGAC_FIBONACCI_H_INCLUDED

/* Fibonacci via fórmula de Binet (válida até ~n=70 com precisão) */
unsigned long long fibonacci_binet(unsigned int pos);

/* Fibonacci recursivo ingênuo */
unsigned long long fibonacci_recursive(unsigned int pos);

/* Fibonacci iterativo (linear, recomendado) */
unsigned long long fibonacci_iterative(unsigned int pos);

/* Fibonacci com memoization (o vetor 'memo' deve ter tamanho pos+1 e iniciar zerado) */
unsigned long long fibonacci_memoization(unsigned int pos, unsigned long long memo[]);

#endif // MATHGAC_FIBONACCI_H_INCLUDED