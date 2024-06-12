#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

void arrayDetails(int *arr, int size) {
    if (size == 0) {
        printf("Array is empty.\n");
        return;
    }

    int minValue = INT_MAX;
    int minIndex = -1;
    int maxValue = INT_MIN;
    int maxIndex = -1;
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        if (arr[i] < minValue) {
            minValue = arr[i];
            minIndex = i;
        }
        if (arr[i] > maxValue) {
            maxValue = arr[i];
            maxIndex = i;
        }
        sum += arr[i];
    }

    // Calculate mean and round to the nearest whole number
    int mean = round(sum / size);

    // Print the result
    printf("Result: [%d, %d, %d, %d, %d, %d]\n", size, minValue, minIndex, mean, maxValue, maxIndex);
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
    int *arr = (int *)malloc(sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int size = 0;
    char *token = strtok(start, ",");
    while (token != NULL) {
        arr[size] = atoi(token);
        size++;
        arr = (int *)realloc(arr, (size + 1) * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
        token = strtok(NULL, ",");
    }

    // Call the function to print array details
    arrayDetails(arr, size);

    // Free the allocated memory
    free(arr);

    return 0;
}