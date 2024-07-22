# Search

This is a file search program implemented in C, which mimics some functionalities of the UNIX `find` command. It can list files and directories, filter by size, pattern, and type, and execute commands on matching files.

## Features

- **-S**: Show detailed file information (size, permissions, last access time).
- **-s**: Filter files by maximum size.
- **-f**: Search for files matching a pattern and within a specified depth.
- **-t**: Filter by type (f for regular files, d for directories).
- **-e**: Execute a command on each matching file.
- **-E**: Execute a command on all matching files.

## Usage

```sh
./search [OPTIONS] [directory]

OPTIONS:
  -S                  Show detailed file information.
  -s size             Filter files by maximum size.
  -f pattern depth    Search for files matching the pattern within the specified depth.
  -t {f|d}            Filter by type (f for regular files, d for directories).
  -e command          Execute a command on each matching file.
  -E command          Execute a command on all matching files.
