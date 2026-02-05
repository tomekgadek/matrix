#ifndef CLI_H
#define CLI_H

/**
 * Initializes the CLI module and its resources (e.g., variable list).
 */
void cli_init();

/**
 * Runs the main interactive CLI loop.
 */
void cli_run();

/**
 * Cleans up CLI resources.
 */
void cli_cleanup();

#endif
