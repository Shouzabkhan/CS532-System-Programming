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

    // Record start time
    time_t start_time;
    time(&start_time);

    // Execute the command
    int status = execvp(args[0], args);

    if (status == -1) {
        perror("execvp");       // If execvp returns, an error occurred
        exit(EXIT_FAILURE);
    }

    // Record end time if execution completes (though this won't be reached if execvp succeeds)
    time_t end_time;
    time(&end_time);

    // Log command execution with timestamps
    char start_time_str[26], end_time_str[26];
    ctime_r(&start_time, start_time_str);
    ctime_r(&end_time, end_time_str);
    start_time_str[strcspn(start_time_str, "\n")] = '\0';  // Remove the newline character
    end_time_str[strcspn(end_time_str, "\n")] = '\0';      // Remove the newline character

    printf("%s %s %s\n", command, start_time_str, end_time_str);

    exit(EXIT_SUCCESS);  // Ensure child process exits
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
            int status;
            waitpid(pid, &status, 0);
        }
    }

    fclose(file);
    return 0;
}

