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

Matrix* create_matrix(unsigned rows, unsigned cols);

Matrix* create_zero_matrix(unsigned rows, unsigned cols);

Matrix* create_random_matrix(unsigned rows, unsigned cols);

double determinant(const Matrix* mat);

Matrix* invert_matrix(const Matrix* mat);

Matrix* add_matrices(const Matrix* mat1, const Matrix* mat2);

Matrix* subtract_matrices(const Matrix* mat1, const Matrix* mat2);

void print_matrix(const Matrix* mat);

void free_matrix(Matrix* mat);

void matrix_message();

double get_element(const Matrix* mat, unsigned row, unsigned col);

#endif
