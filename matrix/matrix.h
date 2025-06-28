#ifndef MATRIX_H
#define MATRIX_H

/**
 * Struktura przechowująca macierz liczb zmiennoprzecinkowych (double).
 * Dane przechowywane są jako dynamiczna tablica wskaźników do wierszy.
 */
struct matrix {
    double **mtrx;  // wskaźnik do dynamicznej tablicy wierszy (każdy to double*)
    unsigned rows;  // liczba wierszy w macierzy
    unsigned cols;  // liczba kolumn w macierzy
};

typedef struct matrix Matrix;

void matrix_message();

#endif
