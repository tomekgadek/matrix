#ifndef CLI_H
#define CLI_H

/**
 * Inicjalizuje moduł CLI i jego zasoby (np. listę zmiennych).
 */
void cli_init();

/**
 * Uruchamia główną interaktywną pętlę CLI.
 */
void cli_run();

/**
 * Zwalnia zasoby modułu CLI.
 */
void cli_cleanup();

#endif
