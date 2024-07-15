# Lab 7: Process Management with Fork and Exec

This project demonstrates process management in C using `fork()` and `exec()` system calls. It reads commands from a file (`commands.txt`), executes them, and logs the execution times.

## Prerequisites

Ensure you have the following installed on your system:
- GCC compiler
- Linux environment (tested on Ubuntu)

## Compilation

Compile the program using GCC:
```bash
gcc -Wall -o lab07 lab07.c