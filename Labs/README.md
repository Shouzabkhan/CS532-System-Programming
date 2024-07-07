# Lab 6: Sorting and Writing CSV Data in C

## Overview
This lab assignment focuses on reading a CSV file (`listings.csv`), parsing its data into a structured format using C, sorting the data based on specified criteria (host name and price), and writing the sorted data to new CSV files.

## Objectives
1. Utilize standard I/O operations in C to read from and write to files.
2. Implement sorting algorithms to sort data structures based on specific fields.
3. Demonstrate proficiency in memory management for dynamically allocated strings.
4. Create a Makefile for compiling and building the project.

## Files Included
- `Lab06.c`: Main source file containing the implementation of the CSV parsing, sorting, and file writing functionalities.
- `listings.csv`: Input CSV file containing listings data to be processed.

## Functionality
### Parsing CSV Data
The program reads each line from `listings.csv`, parses it using `strtok` to extract individual fields, and stores the parsed data into an array of `struct Listing`.

### Sorting
Two sorting functions (`sortByHostName` and `sortByPrice`) are implemented using bubble sort algorithm to sort the array of `struct Listing` based on host name and price fields respectively.

### Writing Sorted Data
After sorting, the sorted data is written to two separate CSV files:
- `sorted_by_name.csv`: Contains listings sorted by host name.
- `sorted_by_price.csv`: Contains listings sorted by price.

## Compilation and Execution
To compile the program, use the provided Makefile:
```bash
$ make