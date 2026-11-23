#include "mathgac_gerais.h"

int count_digits(unsigned long long num) {
    if (num == 0) return 1;
    int digits = 0;
    while (num > 0) {
        digits++;
        num /= 10;
    }
    return digits;
}

int is_palindrome(int num) {
    if (num < 0) return 0;
    long long original = num;
    long long reversed = 0;
    while (original > 0) {
        reversed = (reversed * 10) + (original % 10);
        original /= 10;
    }
    return (long long)num == reversed;
}

int is_divisor(int number, int divisor) {
    if (divisor == 0) return 0;
    return (number % divisor == 0);
}