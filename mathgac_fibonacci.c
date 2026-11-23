#include "mathgac_fibonacci.h"
#include <math.h>

unsigned long long fibonacci_binet(unsigned int pos) {
    double phi = (1.0 + sqrt(5.0)) / 2.0;
    return (unsigned long long)round(pow(phi, pos) / sqrt(5.0));
}

unsigned long long fibonacci_recursive(unsigned int pos) {
    if (pos <= 1) return pos;
    return fibonacci_recursive(pos - 1) + fibonacci_recursive(pos - 2);
}

unsigned long long fibonacci_iterative(unsigned int pos) {
    if (pos <= 1) return pos;
    unsigned long long a = 0, b = 1, temp;
    for (unsigned int i = 2; i <= pos; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

unsigned long long fibonacci_memoization(unsigned int pos, unsigned long long memo[]) {
    if (pos <= 1) return pos;
    if (memo[pos] != 0) return memo[pos];
    memo[pos] = fibonacci_memoization(pos - 1, memo) + fibonacci_memoization(pos - 2, memo);
    return memo[pos];
}