#include <stdio.h>
#include <string.h>

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

    return 0;
}
