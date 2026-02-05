#ifndef VARIABLES_H
#define VARIABLES_H

#include "../matrix/matrix.h"

#define VARIABLE_LABEL_SIZE 10

/**
 * Struktura reprezentująca zmienną przechowującą nazwę i powiązaną macierz.
 * Jest elementem listy dwukierunkowej zmiennych.
 */
struct variable {
  char label[VARIABLE_LABEL_SIZE]; // unikalna etykieta (nazwa zmiennej)
  Matrix *mtrx;                    // wskaźnik na przypisaną macierz
  struct variable *next;           // wskaźnik do następnego elementu listy
  struct variable *prev;           // wskaźnik do poprzedniego elementu listy
};

typedef struct variable Variable;

void variables_message();

Variable *create_variable(const char *label, Matrix *mtrx);
void add_variable(Variable **head, Variable *new_var);
Variable *find_variable(Variable *head, const char *label);
void remove_variable(Variable **head, const char *label);
void free_variables(Variable *head);

#endif
