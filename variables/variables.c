#include "variables.h"
#include "../matrix/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Variable *create_variable(const char *label, Matrix *mtrx) {
  Variable *var = (Variable *)malloc(sizeof(Variable));
  if (!var)
    return NULL;
  strncpy(var->label, label, VARIABLE_LABEL_SIZE - 1);
  var->label[VARIABLE_LABEL_SIZE - 1] = '\0';
  var->mtrx = mtrx;
  var->next = NULL;
  var->prev = NULL;
  return var;
}

void add_variable(Variable **head, Variable *new_var) {
  if (!new_var)
    return;
  if (*head == NULL) {
    *head = new_var;
    return;
  }
  Variable *curr = *head;
  while (curr->next) {
    if (strcmp(curr->label, new_var->label) == 0) {
      // Replace existing variable's matrix
      free_matrix(curr->mtrx);
      curr->mtrx = new_var->mtrx;
      free(new_var);
      return;
    }
    curr = curr->next;
  }
  if (strcmp(curr->label, new_var->label) == 0) {
    free_matrix(curr->mtrx);
    curr->mtrx = new_var->mtrx;
    free(new_var);
    return;
  }
  curr->next = new_var;
  new_var->prev = curr;
}

Variable *find_variable(Variable *head, const char *label) {
  Variable *curr = head;
  while (curr) {
    if (strcmp(curr->label, label) == 0) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}

void remove_variable(Variable **head, const char *label) {
  Variable *var = find_variable(*head, label);
  if (!var)
    return;

  if (var->prev)
    var->prev->next = var->next;
  if (var->next)
    var->next->prev = var->prev;
  if (var == *head)
    *head = var->next;

  free_matrix(var->mtrx);
  free(var);
}

void free_variables(Variable *head) {
  Variable *curr = head;
  while (curr) {
    Variable *next = curr->next;
    free_matrix(curr->mtrx);
    free(curr);
    curr = next;
  }
}