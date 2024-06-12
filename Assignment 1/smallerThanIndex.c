#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int smallerThanIndex(int *numbers, int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (*(numbers + i) < i) {
            count++;
        }
    }

    return count;
}

int main() {
    char input[1000];
    printf("Enter the array elements separated by commas (e.g., [1,2,3,4]): ");
    fgets(input, sizeof(input), stdin);

    // Remove square brackets if present
    char *start = strchr(input, '[');
    char *end = strchr(input, ']');
    if (start && end && end > start) {
        start++;
        *end = '\0';
    } else {
        start = input;
    }

    // Initialize dynamic array
    int *numbers = (int *)malloc(sizeof(int));
    if (numbers == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int size = 0;
    char *token = strtok(start, ",");
    while (token != NULL) {
        numbers[size] = atoi(token);
        size++;
        numbers = (int *)realloc(numbers, (size + 1) * sizeof(int));
        if (numbers == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        token = strtok(NULL, ",");
    }

    // Call the function and print the result
    int result = smallerThanIndex(numbers, size);
    printf("Count of numbers smaller than their index: %d\n", result);

    // Free the allocated memory
    free(numbers);

    return 0;
}