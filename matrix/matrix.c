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

Matrix* invert_matrix(const Matrix* mat) {
    // Sprawdzenie czy macierz istnieje i jest kwadratowa
    if (!mat || mat->rows != mat->cols) {
        return NULL;
    }

    unsigned n = mat->rows;
    Matrix* inv = create_matrix(n, n);
    if (!inv) return NULL;

    double det = determinant(mat);
    if (fabs(det) < 1e-9) { // Sprawdzenie czy macierz jest odwracalna
        free_matrix(inv);
        return NULL;
    }

    // Obliczanie macierzy odwrotnej przez macierz dopełnień i transpozycję
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            // Tworzenie minora
            Matrix* minor = create_matrix(n - 1, n - 1);
            if (!minor) {
                free_matrix(inv);
                return NULL;
            }

            unsigned minorRow = 0, minorCol = 0;
            for (unsigned row = 0; row < n; ++row) {
                if (row == i) continue; // Pomijamy wiersz i
                minorCol = 0;
                for (unsigned col = 0; col < n; ++col) {
                    if (col == j) continue; // Pomijamy kolumnę j
                    minor->mtrx[minorRow][minorCol++] = mat->mtrx[row][col];
                }
                minorRow++;
            }

            // Kofaktor
            double cofactor = ((i + j) % 2 == 0 ? 1.0 : -1.0) * determinant(minor);
            inv->mtrx[j][i] = cofactor / det; // Transponowanie
            free_matrix(minor); // Zwolnienie pamięci minora
        }
    }

    return inv;
}

Matrix* add_matrices(const Matrix* mat1, const Matrix* mat2) {
    if (!mat1 || !mat2 || mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        return NULL;
    }

    Matrix* result = create_matrix(mat1->rows, mat1->cols);
    if (!result) {
        return NULL;
    }

    for (unsigned i = 0; i < mat1->rows; ++i) {
        for (unsigned j = 0; j < mat1->cols; ++j) {
            result->mtrx[i][j] = mat1->mtrx[i][j] + mat2->mtrx[i][j];
        }
    }

    return result;
}

Matrix* subtract_matrices(const Matrix* mat1, const Matrix* mat2) {
    if (!mat1 || !mat2 || mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        return NULL;
    }

    Matrix* result = create_matrix(mat1->rows, mat1->cols);
    if (!result) {
        return NULL;
    }

    for (unsigned i = 0; i < mat1->rows; ++i) {
        for (unsigned j = 0; j < mat1->cols; ++j) {
            result->mtrx[i][j] = mat1->mtrx[i][j] - mat2->mtrx[i][j];
        }
    }

    return result;
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

double get_element(const Matrix* mat, unsigned row, unsigned col) {
    if (!mat || row <= 0 || col <= 0 || row > mat->rows || col > mat->cols) {
        return NAN; // Zwracamy NaN jeśli indeksy są nieprawidłowe
    }
    
    return mat->mtrx[row - 1][col - 1];
}