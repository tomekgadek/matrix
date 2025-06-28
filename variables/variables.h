#ifndef VARIABLES_H
#define VARIABLES_H

#define VARIABLE_LABEL_SIZE 10

/**
 * Struktura reprezentująca zmienną przechowującą nazwę i powiązaną macierz.
 * Jest elementem listy dwukierunkowej zmiennych.
 */
struct variable {
    char label[VARIABLE_LABEL_SIZE];    // unikalna etykieta (nazwa zmiennej)
    Matrix *mtrx;                       // wskaźnik na przypisaną macierz
    struct variable *next;              // wskaźnik do następnego elementu listy
    struct variable *prev;              // wskaźnik do poprzedniego elementu listy
};

typedef struct variable Variable;

void variables_message();

#endif
