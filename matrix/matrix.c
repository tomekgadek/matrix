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
    if (!mat || mat->rows != mat->cols) {
        fprintf(stderr, "Błąd: macierz NULL lub niekwadratowa w determinant().\n");
        return NAN;  // specjalna wartość oznaczająca „nie liczba”
    }

    unsigned n = mat->rows;

    if (n == 1) {
        return mat->mtrx[0][0];
    }

    if (n == 2) {
        return mat->mtrx[0][0] * mat->mtrx[1][1] - mat->mtrx[0][1] * mat->mtrx[1][0];
    }

    double det = 0.0;
    for (unsigned col = 0; col < n; ++col) {
        Matrix *minor = create_submatrix(mat, 0, col);
        if (!minor) {
            fprintf(stderr, "Błąd alokacji minor.\n");
            return NAN;
        }

        double cofactor = ((col % 2 == 0) ? 1.0 : -1.0) * mat->mtrx[0][col] * determinant(minor);
        det += cofactor;
        free_matrix(minor);
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