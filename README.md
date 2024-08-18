# Grammar Left Factoring

This C++ program performs left factoring of context-free grammar productions. It reads a set of production rules, identifies common prefixes, and refactors the grammar to eliminate left recursion and factor out common prefixes.


## Features

- Splits production rules into individual productions.
- Identifies common prefixes among productions.
- Refactors productions by introducing new non-terminals for common prefixes.
- Outputs the factored grammar.

## Requirements

- A C++ compiler (e.g., g++, clang++)

## Compilation

To compile the program, use the following command:

g++ -o grammar_left_factoring grammar_left_factoring.cpp
