Name: Shouzab khan
BlazerId: Skhan6
Project #: HW 2

To compile:
$ make

To run:
$ ./search [options] [directory]

Options:
  -S               List all files with size, permissions, and last access time
  -s size          List all files with size less than or equal to the specified size
  -f pattern depth List all files with the specified pattern and depth
  -t f             List only regular files
  -t d             List only directories

Examples:
$ ./search
$ ./search -S
$ ./search -s 1024
$ ./search -f jpg 1
$ ./search -S -f jpg 1 -s 1024
$ ./search -t f
$ ./search -t d

Description:
This program traverses a file hierarchy starting from the specified directory or the current directory if no directory is specified. It lists files and directories with various options for additional information and filtering.

Testing:
Test the program with various combinations of options and directories to ensure correctness. Sample test cases are provided in the project description.
