# Lab 6 - CS 332/532 Systems Programming

## Overview

This lab involves reading a CSV file containing various listings, parsing the data into a C structure, and then sorting the data based on two different fields: `host_name` and `price`. The sorted data is then written into two new CSV files: `sorted_by_name.csv` and `sorted_by_price.csv`.

## Files

- `Lab06.c`: The main C program that reads, parses, sorts, and writes the data.
- `listings.csv`: The input CSV file containing the listings data.
- `sorted_by_name.csv`: The output CSV file sorted by `host_name`.
- `sorted_by_price.csv`: The output CSV file sorted by `price`.
- `Makefile`: The makefile to compile the program.

## Compilation and Execution

### Compiling the Program

To compile the program, use the provided `Makefile`. Open a terminal in the directory containing the `Lab06.c` file and run the following command:

```sh
make
