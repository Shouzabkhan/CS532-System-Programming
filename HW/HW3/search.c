#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <sys/wait.h>

#define MAX_PATH 1024

typedef struct {
    int show_info;
    int max_size;
    int max_depth;
    const char *pattern;
    int type_filter; // 0 for no filter, 1 for regular files, 2 for directories
    const char *exec_command; // Command to execute
} options_t;


typedef void (*file_handler)(const char *dirpath, const struct dirent *entry, const struct stat *st, int depth, options_t *opts);

// Function prototypes
void list_directory(const char *dirpath, int depth, options_t *opts);
void handle_file(const char *dirpath, const struct dirent *entry, const struct stat *st, int depth, options_t *opts);
void handle_directory(const char *dirpath, const struct dirent *entry, const struct stat *st, int depth, options_t *opts);
void handle_symlink(const char *dirpath, const struct dirent *entry, const struct stat *st, int depth, options_t *opts);

void print_file_info(const char *filename, const struct stat *st) {
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&st->st_atime));
    printf("%s (size: %ld, permissions: %o, last access: %s)\n", filename, st->st_size, st->st_mode & 0777, time_str);
}

// Function to handle regular files
void handle_file(const char *dirpath, const struct dirent *entry, const struct stat *st, int depth, options_t *opts) {
    if ((opts->pattern == NULL || strstr(entry->d_name, opts->pattern)) &&
        (opts->max_size < 0 || st->st_size <= opts->max_size)) {
        // Print file details
        printf("%*s%s", depth * 4, "", entry->d_name);
        if (opts->show_info) {
            print_file_info(entry->d_name, st);
        } else {
            printf("\n");
        }
        
        // Execute the command if specified
        if (opts->exec_command) {
            pid_t pid = fork();
            if (pid == 0) { // Child process
                char cmd[PATH_MAX];
                snprintf(cmd, sizeof(cmd), "%s %s/%s", opts->exec_command, dirpath, entry->d_name);
                printf("Executing command: %s\n", cmd); // Debugging line
                execlp("/bin/sh", "sh", "-c", cmd, (char *)NULL);
                perror("execlp"); // Handle exec error
                exit(EXIT_FAILURE);
            } else if (pid > 0) {
                wait(NULL); // Wait for child process to finish
            } else {
                perror("fork"); // Handle fork error
            }
        }
    }
}


// Function to handle directories
void handle_directory(const char *dirpath, const struct dirent *entry, const struct stat *st __attribute__((unused)), int depth, options_t *opts) {
    if (depth < opts->max_depth) {
        char new_dirpath[MAX_PATH];
        snprintf(new_dirpath, MAX_PATH, "%s/%s", dirpath, entry->d_name);

        printf("%*s%s/\n", depth * 4, "", entry->d_name);
        list_directory(new_dirpath, depth + 1, opts);
    }
}


// Function to handle symbolic links
void handle_symlink(const char *dirpath, const struct dirent *entry, const struct stat *st __attribute__((unused)), int depth, options_t *opts __attribute__((unused))) {
    char link_target[MAX_PATH];
    ssize_t len = readlink(dirpath, link_target, sizeof(link_target) - 1);
    if (len != -1) {
        link_target[len] = '\0';
        printf("%*s%s -> %s\n", depth * 4, "", entry->d_name, link_target);
    }
}

// Function to list directory contents
void list_directory(const char *dirpath, int depth, options_t *opts) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    struct stat st;
    char path[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, MAX_PATH, "%s/%s", dirpath, entry->d_name);
        if (lstat(path, &st) < 0) {
            perror("lstat");
            continue;
        }

        file_handler handler = NULL;

        if (S_ISDIR(st.st_mode)) {
            if (opts->type_filter == 0 || opts->type_filter == 2) {
                handler = handle_directory;
            }
        } else if (S_ISLNK(st.st_mode)) {
            handler = handle_symlink;
        } else {
            if (opts->type_filter == 0 || opts->type_filter == 1) {
                handler = handle_file;
            }
        }

        if (handler) {
            handler(dirpath, entry, &st, depth, opts);
        }
    }

    closedir(dir);
}

// Function to print usage information
void usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-S] [-s size] [-f pattern depth] [-t {f|d}] [-e command] [directory]\n", progname);
    exit(EXIT_FAILURE);
}

// Main function
int main(int argc, char *argv[]) {
    options_t opts = {0, -1, INT_MAX, NULL, 0, NULL};
    int opt;
    int long_index = 0;
    char *progname = argv[0];

    static struct option long_options[] = {{"size", required_argument, 0, 's'}, {"find", required_argument, 0, 'f'}, {"execute", required_argument, 0, 'e'}, {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "Ss:f:e:", long_options, &long_index)) != -1) {
        switch (opt) {
            case 's':
                opts.max_size = atoi(optarg);
                break;
            case 'f':
                opts.pattern = optarg;
                if (optind < argc && argv[optind][0] != '-') {
                    opts.max_depth = atoi(argv[optind]);
                    optind++;
                } else {
                    opts.max_depth = INT_MAX;
                }
                break;
            case 'S':
                opts.show_info = 1;
                break;
            case 'e':
                opts.exec_command = optarg;
                break;
            default:
                usage(progname);
        }
    }

    const char *dirpath = (optind < argc) ? argv[optind] : ".";
    list_directory(dirpath, 0, &opts);

    return 0;
}
