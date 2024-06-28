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

#define MAX_PATH 1024

typedef struct {
    int show_info;
    int max_size;
    int max_depth;
    const char *pattern;
    int type_filter; // 0 for no filter, 1 for regular files, 2 for directories
} options_t;

void print_file_info(const char *filename, struct stat *st) {
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&st->st_atime));
    printf("%s (size: %ld, permissions: %o, last access: %s)\n", filename, st->st_size, st->st_mode & 0777, time_str);
}

void list_directory(const char *dirpath, int depth, options_t *opts) {
    DIR *dir = opendir(dirpath);
    if (!dir) {
        perror("opendir");
        return;
    }

    struct dirent *entry;
    struct stat st;
    char path[MAX_PATH];
    char link_target[MAX_PATH];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, MAX_PATH, "%s/%s", dirpath, entry->d_name);
        if (lstat(path, &st) < 0) {
            perror("lstat");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (depth < opts->max_depth && (opts->type_filter == 0 || opts->type_filter == 2)) {
                printf("%*s%s/\n", depth * 4, "", entry->d_name);
                list_directory(path, depth + 1, opts);
            }
        } else if (S_ISLNK(st.st_mode)) {
            ssize_t len = readlink(path, link_target, sizeof(link_target) - 1);
            if (len != -1) {
                link_target[len] = '\0';
                printf("%*s%s -> %s\n", depth * 4, "", entry->d_name, link_target);
            }
        } else if ((opts->type_filter == 0 || opts->type_filter == 1)) {
            if ((opts->pattern == NULL || strstr(entry->d_name, opts->pattern)) &&
                (opts->max_size < 0 || st.st_size <= opts->max_size)) {
                printf("%*s%s", depth * 4, "", entry->d_name);
                if (opts->show_info) {
                    print_file_info(entry->d_name, &st);
                } else {
                    printf("\n");
                }
            }
        }
    }

    closedir(dir);
}

void usage(const char *progname) {
    fprintf(stderr, "Usage: %s [-S] [-s size] [-f pattern depth] [-t {f|d}] [directory]\n", progname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    options_t opts = {0, -1, INT_MAX, NULL, 0};
    int opt;
    char *progname = argv[0];

    while ((opt = getopt(argc, argv, "Ss:f:t:")) != -1) {
        switch (opt) {
            case 'S':
                opts.show_info = 1;
                break;
            case 's':
                opts.max_size = atoi(optarg);
                break;
            case 'f':
                opts.pattern = optarg;
                opts.max_depth = atoi(argv[optind]);
                break;
            case 't':
                if (strcmp(optarg, "f") == 0) {
                    opts.type_filter = 1;
                } else if (strcmp(optarg, "d") == 0) {
                    opts.type_filter = 2;
                } else {
                    usage(progname);
                }
                break;
            default:
                usage(progname);
        }
    }

    const char *dirpath = (optind < argc) ? argv[optind] : ".";
    list_directory(dirpath, 0, &opts);

    return 0;
}