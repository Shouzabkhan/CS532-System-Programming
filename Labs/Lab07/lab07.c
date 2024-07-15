#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

void log_command(const char *command, const char *start_time, const char *end_time) {
    FILE *log_file = fopen("output.log", "a");
    if (log_file == NULL) {
        perror("Error opening log file");
        exit(EXIT_FAILURE);
    }
    fprintf(log_file, "%s\t%s\t%s\n", command, start_time, end_time);
    fclose(log_file);
}

void execute_command(const char *command) {
    char *args[MAX_LINE_LENGTH / 2 + 1];  // Assuming arguments are separated by spaces and each argument is at least one character
    char *cmd = strdup(command);          // Duplicate the command to avoid modifying the original
    char *token;
    int i = 0;

    token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;  // Null-terminate the array of arguments

    execvp(args[0], args);  // Execute the command
    perror("execvp");       // If execvp returns, an error occurred
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';  // Remove the newline character

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Child process
            execute_command(line);
        } else {  // Parent process
            time_t start_time, end_time;
            char start_time_str[26], end_time_str[26];
            
            time(&start_time);
            ctime_r(&start_time, start_time_str);
            start_time_str[strcspn(start_time_str, "\n")] = '\0';  // Remove the newline character

            int status;
            waitpid(pid, &status, 0);

            time(&end_time);
            ctime_r(&end_time, end_time_str);
            end_time_str[strcspn(end_time_str, "\n")] = '\0';  // Remove the newline character

            log_command(line, start_time_str, end_time_str);
        }
    }

    fclose(file);
    return 0;
}
