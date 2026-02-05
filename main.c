#include "cli/cli.h"

int main() {
  cli_init();
  cli_run();
  cli_cleanup();
  return 0;
}
