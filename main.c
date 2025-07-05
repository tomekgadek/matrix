#include <stdio.h>
#include <string.h>
#include <math.h>

#include "matrix/matrix.h"
#include "gui/gui.h"
#include "help/help.h"
#include "variables/variables.h"

const int COMMAND_SIZE = 40;

int main() {

    char command[COMMAND_SIZE];

    show_menu();
    
    while (1) {
        printf(">> ");
        if (fgets(command, COMMAND_SIZE, stdin) == NULL) {
            break; // EOF or error
        }

        // Remove trailing newline if present
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        if (strcmp(command, "exit") == 0) {
            break;
        } else if (strcmp(command, "pomoc") == 0) {
            load_help_file("demo/pomoc.txt");
        } else if (strlen(command) == 0) {
            continue;
        } else {
            printf("\'%s\' - Nieznane polecenia lub zmienna \n", command);
        }
    }

    // testy operacji na macierzach
    Matrix* mat = create_matrix(2, 3);
    
    double z = 1.0;
    for (unsigned i = 0; i < mat->rows; ++i) {
        for (unsigned j = 0; j < mat->cols; ++j) {
            mat->mtrx[i][j] = (i + 1) * (j + 1) * z;
        }

        z *= -1.0; // zmiana znaku
    }

    double det = determinant(mat);
    if (isnan(det)) {
        printf("Nie można policzyć wyznacznika!\n");
    } else {
        printf("Wyznacznik: %lf\n", det);
    }

    print_matrix(mat);
    free_matrix(mat);

    printf("\n");

    // macierz zerowa
    Matrix* zero_mat = create_zero_matrix(3, 3);
    print_matrix(zero_mat);
    free_matrix(zero_mat);

    printf("\n");

    // macierz losowa
    Matrix* random_mat = create_random_matrix(3, 3);
    print_matrix(random_mat);
    free_matrix(random_mat);

    // wyznacznik macierzy
    Matrix* square_mat = create_matrix(4, 4);
    // Wprowadzenie danych do macierzy A
    double data[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 1, 2, 3},
        {4, 5, 6, 0}
    };

    for (unsigned i = 0; i < 4; ++i) {
        for (unsigned j = 0; j < 4; ++j) {
            square_mat->mtrx[i][j] = data[i][j];
        }
    }

    printf("Wyznacznik macierzy 4x4: %lf \n", determinant(square_mat));

    // test macierzy odwrotnej
    printf("\n");

    Matrix *A = create_matrix(2, 2);
    A->mtrx[0][0] = 1; A->mtrx[0][1] = 2;
    A->mtrx[1][0] = 3; A->mtrx[1][1] = 4;

    printf("Macierz A:\n");
    print_matrix(A);

    Matrix *Ainv = invert_matrix(A);
    if (Ainv) {
        printf("\nMacierz odwrotna A^-1:\n");
        print_matrix(Ainv);
        free_matrix(Ainv);
    } else {
        printf("\nMacierz nie ma odwrotności.\n");
    }

    // Dodawanie dwóch macierzy
    Matrix *B = create_matrix(2, 2);
    B->mtrx[0][0] = 5; B->mtrx[0][1] = 6;
    B->mtrx[1][0] = 7; B->mtrx[1][1] = 8;

    printf("\nMacierz A:\n");
    print_matrix(A);
    printf("\nMacierz B:\n");
    print_matrix(B);

    Matrix *C = add_matrices(A, B);
    if (C) {
        printf("\nA + B:\n");
        print_matrix(C);
        free_matrix(C);
    } else {
        printf("\nNie można dodać macierzy A i B (różne wymiary).\n");
    }

    Matrix *D = subtract_matrices(A, B);
    if (C) {
        printf("\nA - B:\n");
        print_matrix(D);
        free_matrix(D);
    } else {
        printf("\nNie można odjąć macierzy A i B (różne wymiary).\n");
    }

    free_matrix(B);
    free_matrix(A);
    
    return 0;
}
