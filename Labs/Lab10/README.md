# Lab 10 - Process Management and Command Execution

## Description

Lab 10 involves creating a C program that executes a series of commands listed in a file, logs the start and end times of each command, and redirects the output and error streams of each command to separate files.

## Files

- `lab10.c`: The source code for the program.
- `commands.txt`: A text file containing the commands to be executed.
- `output.log`: A log file that records the start and end times of each command execution.
- `Makefile` (if applicable): To build the `lab10` executable.

## Compilation

To compile the program, use the following command:

```bash
gcc -Wall -o lab10 lab10.c
