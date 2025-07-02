#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

Matrix* create_matrix(unsigned rows, unsigned cols) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (!mat) {
        return NULL;
    }

    mat->rows = rows;
    mat->cols = cols;
    mat->mtrx = (double **)malloc(rows * sizeof(double *));
    if (!mat->mtrx) {
        free(mat);
        return NULL;
    }

    for (unsigned i = 0; i < rows; ++i) {
        mat->mtrx[i] = (double *)calloc(cols, sizeof(double));
        if (!mat->mtrx[i]) {
            for (unsigned j = 0; j < i; ++j) {
                free(mat->mtrx[j]);
            }

            free(mat->mtrx);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

Matrix* create_zero_matrix(unsigned rows, unsigned cols) {
    Matrix* mat = create_matrix(rows, cols);
    if (!mat) return NULL;
    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            mat->mtrx[i][j] = 0.0;
        }
    }
    return mat;
}

Matrix* create_random_matrix(unsigned rows, unsigned cols) {
    Matrix* mat = create_matrix(rows, cols);
    if (!mat) return NULL;

    for (unsigned i = 0; i < rows; ++i) {
        for (unsigned j = 0; j < cols; ++j) {
            // Losowe wartości od -1000000.0 do +1000000.0
            mat->mtrx[i][j] = ((double)(rand() % 2000001) - 1000000.0);
        }
    }
    return mat;
}

double determinant(const Matrix *mat) {
    // Sprawdzenie czy macierz istnieje i czy jest kwadratowa
    if (!mat || mat->rows != mat->cols) {
        return NAN;
    }
    
    unsigned n = mat->rows;
    // Wyznacznik macierzy 1x1 to jej jedyny element
    if (n == 1) {
        return mat->mtrx[0][0];
    }
    // Wyznacznik macierzy 2x2 obliczamy bezpośrednio
    if (n == 2) {
        return mat->mtrx[0][0] * mat->mtrx[1][1] - mat->mtrx[0][1] * mat->mtrx[1][0];
    }

    double det = 0.0;
    // Rozwinięcie Laplace’a względem pierwszego wiersza
    for (unsigned k = 0; k < n; ++k) {
        // Tworzenie macierzy minor (pomocniczej) bez pierwszego wiersza i k-tej kolumny
        Matrix* minor = create_matrix(n - 1, n - 1);
        if (!minor) return 0.0;
        for (unsigned i = 1; i < n; ++i) {
            unsigned colIdx = 0;
            for (unsigned j = 0; j < n; ++j) {
                if (j == k) continue; // Pomijamy k-tą kolumnę
                minor->mtrx[i - 1][colIdx] = mat->mtrx[i][j];
                ++colIdx;
            }
        }
        // Obliczanie kofaktora i rekurencyjne wywołanie determinanty minora
        double cofactor = ((k % 2 == 0) ? 1.0 : -1.0) * mat->mtrx[0][k] * determinant(minor);
        det += cofactor;
        free_matrix(minor); // Zwolnienie pamięci minora
    }

    return det;
}


void print_matrix(const Matrix* mat) {
    if (!mat) return;
    for (unsigned i = 0; i < mat->rows; ++i) {
        for (unsigned j = 0; j < mat->cols; ++j) {
            printf("%+lf ", mat->mtrx[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(Matrix* mat) {
    if (!mat) {
        return;
    }

    for (unsigned i = 0; i < mat->rows; ++i) {
        free(mat->mtrx[i]);
    }

    free(mat->mtrx);
    free(mat);
}

void matrix_message() {
    printf("Load matrix module. \n");
}