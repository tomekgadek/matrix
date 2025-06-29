#include <stdio.h>
#include <stdlib.h>
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