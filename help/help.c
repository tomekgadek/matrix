#include "help.h"
#include <stdio.h>

void load_help_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Nie można otworzyć pliku");
    return;
  }

  char buffer[1024];
  while (fgets(buffer, sizeof(buffer), file)) {
    printf("%s", buffer);
  }

  fclose(file);
}
