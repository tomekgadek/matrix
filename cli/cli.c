#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../gui/gui.h"
#include "../help/help.h"
#include "../matrix/matrix.h"
#include "../variables/variables.h"
#include "cli.h"

#define MAX_LINE 256

static Variable *var_list = NULL;

// --- Prywatne funkcje pomocnicze ---

static void trim(char *str) {
  char *start = str;
  char *end;
  while (isspace((unsigned char)*start))
    start++;
  if (*start == 0) {
    *str = '\0';
    return;
  }
  end = start + strlen(start) - 1;
  while (end > start && isspace((unsigned char)*end))
    end--;
  end[1] = '\0';
  memmove(str, start, end - start + 2);
}

static Matrix *parse_literal(const char *str) {
  if (str[0] != '[' || str[strlen(str) - 1] != ']')
    return NULL;

  char *copy = strdup(str + 1);
  copy[strlen(copy) - 1] = '\0';

  unsigned rows = 1, cols = 0;
  for (int i = 0; copy[i]; i++) {
    if (copy[i] == ';')
      rows++;
  }

  char *first_row = strdup(copy);
  char *p = strchr(first_row, ';');
  if (p)
    *p = '\0';
  char *token_str = strdup(first_row);
  char *token = strtok(token_str, " ");
  while (token) {
    cols++;
    token = strtok(NULL, " ");
  }
  free(token_str);
  free(first_row);

  Matrix *mat = create_matrix(rows, cols);
  char *row_ptr;
  char *copy_for_tok = strdup(copy);
  char *row_str = strtok_r(copy_for_tok, ";", &row_ptr);
  unsigned r = 0;
  while (row_str && r < rows) {
    char *col_ptr;
    char *val_str = strtok_r(row_str, " ", &col_ptr);
    unsigned c = 0;
    while (val_str && c < cols) {
      mat->mtrx[r][c] = atof(val_str);
      val_str = strtok_r(NULL, " ", &col_ptr);
      c++;
    }
    row_str = strtok_r(NULL, ";", &row_ptr);
    r++;
  }
  free(copy_for_tok);
  free(copy);
  return mat;
}

static Matrix *eval_expression(char *expr) {
  trim(expr);
  if (expr[0] == '[')
    return parse_literal(expr);

  unsigned r, c;
  if (sscanf(expr, "losowa ( %u , %u )", &r, &c) == 2 ||
      sscanf(expr, "losowa(%u,%u)", &r, &c) == 2 ||
      sscanf(expr, "losowa (%u,%u)", &r, &c) == 2 ||
      sscanf(expr, "losowa(%u , %u)", &r, &c) == 2) {
    return create_random_matrix(r, c);
  }

  // losowa(nazwa_m) - tworzy losową macierz o wymiarach istniejącej macierzy
  char label[VARIABLE_LABEL_SIZE];
  if (sscanf(expr, "losowa ( %[^)] )", label) == 1 ||
      sscanf(expr, "losowa(%[^)])", label) == 1 ||
      sscanf(expr, "losowa (%[^)])", label) == 1) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    if (v && v->mtrx) {
      return create_random_matrix(v->mtrx->rows, v->mtrx->cols);
    }
    return NULL;
  }

  if (sscanf(expr, "zerowa ( %u , %u )", &r, &c) == 2 ||
      sscanf(expr, "zerowa(%u,%u)", &r, &c) == 2 ||
      sscanf(expr, "zerowa (%u,%u)", &r, &c) == 2 ||
      sscanf(expr, "zerowa(%u , %u)", &r, &c) == 2) {
    return create_zero_matrix(r, c);
  }

  // zerowa(nazwa_m) - tworzy zerową macierz o wymiarach istniejącej macierzy
  if (sscanf(expr, "zerowa ( %[^)] )", label) == 1 ||
      sscanf(expr, "zerowa(%[^)])", label) == 1 ||
      sscanf(expr, "zerowa (%[^)])", label) == 1) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    if (v && v->mtrx) {
      return create_zero_matrix(v->mtrx->rows, v->mtrx->cols);
    }
    return NULL;
  }

  if (sscanf(expr, "odwroc ( %[^)] )", label) == 1 ||
      sscanf(expr, "odwroc(%[^)])", label) == 1 ||
      sscanf(expr, "odwroc (%[^)])", label) == 1) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    return v ? invert_matrix(v->mtrx) : NULL;
  }

  char op = 0;
  char *op_pos = strpbrk(expr, "+-*");
  if (op_pos) {
    op = *op_pos;
    *op_pos = '\0';
    char *left = expr;
    char *right = op_pos + 1;
    trim(left);
    trim(right);
    Variable *v1 = find_variable(var_list, left);
    Variable *v2 = find_variable(var_list, right);
    if (v1 && v2) {
      if (op == '+')
        return add_matrices(v1->mtrx, v2->mtrx);
      if (op == '-')
        return subtract_matrices(v1->mtrx, v2->mtrx);
      if (op == '*')
        return multiply_matrices(v1->mtrx, v2->mtrx);
    }
    return NULL;
  }

  Variable *v = find_variable(var_list, expr);
  if (v) {
    // Zwracamy kopię, aby uniknąć problemów ze współdzieleniem wskaźnika na macierz
    Matrix *copy = create_matrix(v->mtrx->rows, v->mtrx->cols);
    for (unsigned i = 0; i < copy->rows; i++) {
      for (unsigned j = 0; j < copy->cols; j++) {
        copy->mtrx[i][j] = v->mtrx->mtrx[i][j];
      }
    }
    return copy;
  }

  return NULL;
}

// --- Funkcje obsługujące polecenia ---

static void handle_assignment(char *label, char *expr) {
  trim(label);
  Matrix *res = eval_expression(expr);
  if (res) {
    add_variable(&var_list, create_variable(label, res));
    print_matrix(res);
  } else {
    printf("Zle polecenie\n");
  }
}

static void handle_determinant(char *line) {
  char label[VARIABLE_LABEL_SIZE];
  if (sscanf(line, "wyzn ( %[^)] )", label) == 1 ||
      sscanf(line, "wyzn(%[^)])", label) == 1 ||
      sscanf(line, "wyzn (%[^)])", label) == 1) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    if (v) {
      double d = determinant(v->mtrx);
      if (isnan(d))
        printf("Nie można policzyć wyznacznika!\n");
      else
        printf("Wyznacznik: %lf\n", d);
    } else {
      printf("'%s' - Nieznane polecenia lub zmienna \n", label);
    }
  }
}

static void handle_save(char *line) {
  char label[VARIABLE_LABEL_SIZE];
  if (sscanf(line, "zapisz ( %[^)] )", label) == 1 ||
      sscanf(line, "zapisz(%[^)])", label) == 1 ||
      sscanf(line, "zapisz (%[^)])", label) == 1) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    if (v) {
      save_matrix(v->mtrx, label);
      printf("Zapisano macierz '%s' do pliku 'data/%s'\n", label, label);
    } else {
      printf("'%s' - Zle polecenie (zmienna nie istnieje)\n", label);
    }
  }
}

static void handle_load(char *line) {
  char label[VARIABLE_LABEL_SIZE];
  if (sscanf(line, "wczytaj ( %[^)] )", label) == 1 ||
      sscanf(line, "wczytaj(%[^)])", label) == 1 ||
      sscanf(line, "wczytaj (%[^)])", label) == 1) {
    trim(label);
    Matrix *m = load_matrix(label);
    if (m) {
      add_variable(&var_list, create_variable(label, m));
      printf("Wczytano macierz '%s'\n", label);
      print_matrix(m);
    } else {
      printf("Nie udało się wczytać macierzy z pliku 'data/%s'\n", label);
    }
  }
}

static int handle_element_access(char *line) {
  char label[VARIABLE_LABEL_SIZE];
  unsigned row, col;
  if (sscanf(line, "%[^(]( %u , %u )", label, &row, &col) == 3 ||
      sscanf(line, "%[^(](%u,%u)", label, &row, &col) == 3 ||
      sscanf(line, "%[^(] (%u,%u)", label, &row, &col) == 3 ||
      sscanf(line, "%[^(](%u , %u)", label, &row, &col) == 3) {
    trim(label);
    Variable *v = find_variable(var_list, label);
    if (v) {
      double val = get_element(v->mtrx, row, col);
      if (isnan(val)) {
        printf("Nieprawidłowe indeksy (%u,%u) dla macierzy '%s'\n", row, col, label);
      } else {
        printf("%s(%u,%u) = %lf\n", label, row, col, val);
      }
      return 1;
    }
  }
  return 0;
}

static void execute_command(char *line) {
  trim(line);
  if (strlen(line) == 0)
    return;

  if (strcmp(line, "exit") == 0) {
    cli_cleanup();
    exit(0);
  }

  if (strcmp(line, "pomoc") == 0) {
    load_help_file("demo/pomoc.txt");
    return;
  }

  char *eq = strchr(line, '=');
  if (eq) {
    *eq = '\0';
    handle_assignment(line, eq + 1);
    return;
  }

  if (strncmp(line, "wyzn", 4) == 0) {
    handle_determinant(line);
    return;
  }
  if (strncmp(line, "zapisz", 6) == 0) {
    handle_save(line);
    return;
  }
  if (strncmp(line, "wczytaj", 7) == 0) {
    handle_load(line);
    return;
  }

  if (handle_element_access(line)) {
    return;
  }

  Variable *v = find_variable(var_list, line);
  if (v) {
    print_matrix(v->mtrx);
    return;
  }

  printf("'%s' - Nieznane polecenia lub zmienna \n", line);
}

// --- Interfejs publiczny ---

void cli_init() { var_list = NULL; }

void cli_run() {
  char line[MAX_LINE];
  show_menu();
  while (1) {
    printf(">> ");
    if (fgets(line, MAX_LINE, stdin) == NULL)
      break;
    execute_command(line);
  }
}

void cli_cleanup() {
  free_variables(var_list);
  var_list = NULL;
}
