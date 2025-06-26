#include <stdio.h>

#include "matrix/matrix.h"
#include "gui/gui.h"
#include "help/help.h"
#include "variables/variables.h"

int main() {

    show_menu(); // gui module

    printf("\n\n");

    gui_message();
    help_message();
    matrix_message();
    variables_message();
    
    return 0;
}
