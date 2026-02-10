# AGENTS.md

This file provides guidance to WARP (warp.dev) when working with code in this repository.

## Project Overview

A MATLAB-like matrix calculator implemented in C with a Polish-language CLI interface. Users can create, manipulate, and perform operations on matrices through an interactive command-line prompt.

## Build Commands

```bash
# Compile the project
make

# Run the application
./macierze

# Clean build artifacts
make clean
```

## Architecture

### Module Structure

- **cli/** - Command-line interface and expression parser. Manages the REPL loop, parses user input, and dispatches to appropriate handlers. Contains the expression evaluator (`eval_expression`) which handles literals, function calls, and binary operations.

- **matrix/** - Core matrix data structure and operations. Provides dynamic memory allocation for matrices, arithmetic operations (add, subtract, multiply), determinant calculation (Laplace expansion), matrix inversion, and file I/O.

- **variables/** - Doubly-linked list for variable storage. Variables map string labels to Matrix pointers. Handles automatic replacement when reassigning existing variables.

- **gui/** - Simple menu display (startup banner and help prompt).

- **help/** - Loads and displays help text from files.

- **data/** - Directory for persistent matrix storage (files saved/loaded by `zapisz`/`wczytaj` commands).

### Key Data Structures

```c
struct matrix {
    double **mtrx;   // 2D dynamic array of values
    unsigned rows;
    unsigned cols;
};

struct variable {
    char label[10];         // variable name
    struct matrix *mtrx;    // owned matrix pointer
    struct variable *next;  // doubly-linked list
    struct variable *prev;
};
```

### CLI Commands (Polish)

- `a = losowa(3,3)` - Create random matrix
- `b = losowa(a)` - Create random matrix with same dimensions as `a`
- `a = zerowa(3,3)` - Create zero matrix
- `b = zerowa(a)` - Create zero matrix with same dimensions as `a`
- `b = odwroc(a)` - Invert matrix
- `c = a + b`, `c = a - b`, `c = a * b` - Arithmetic operations
- `a += b`, `a -= b`, `a *= b` - Compound operators (e.g. `a *= a`)
- `d = [1 2 3; 4 5 6]` - Matrix literal (semicolon separates rows)
- `a(1,2)` - Access element at row 1, column 2 (1-indexed)
- `wyzn(a)` - Calculate determinant
- `zapisz(a)` - Save matrix to `data/a`
- `wczytaj(a)` - Load matrix from `data/a`
- `pomoc` - Show help
- `exit` - Quit

## Code Conventions

- Memory ownership: Functions returning `Matrix*` transfer ownership to the caller (caller must call `free_matrix`)
- Variable storage: `add_variable` takes ownership of the Matrix pointer and will free existing matrices when overwriting
- Error handling: Functions return `NULL` on failure; determinant returns `NAN` for non-square matrices
