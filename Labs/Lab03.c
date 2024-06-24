#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print an array of strings
void printArray(char** A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", A[i]);
    }
    printf("\n");
}

// Function to sort characters within a string using insertion sort
void sortCharacters(char* str) {
    int len = strlen(str);  // Get the length of the string
    for (int i = 1; i < len; i++) {
        char key = str[i];  // Current character to be compared
        int j = i - 1;
        // Shift characters greater than key to one position ahead
        while (j >= 0 && str[j] > key) {
            str[j + 1] = str[j];
            j--;
        }
        str[j + 1] = key;  // Place key in its correct position
    }
}

// Insertion Sort function for an array of strings
void insertionSort(char** A, int n) {
    char* key;
    int j;
    // Loop through each element of the array
    for (int i = 1; i < n; i++) {
        key = A[i];  // Current string to be compared
        j = i - 1;
        // Shift strings greater than key to one position ahead
        while (j >= 0 && strcmp(A[j], key) > 0) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;  // Place key in its correct position
    }
}

// Main function
int main() {
    int myArraySize;

    // Prompt user for the size of the array
    printf("Enter the size of the array: \n");
    scanf("%d", &myArraySize);

    // Allocate memory for an array of strings
    char** insertionSortArray = (char**)malloc(myArraySize * sizeof(char*));
    if (insertionSortArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Prompt user to enter the words
    printf("Enter the words that you want to sort: \n");

    // Take user input for each word
    for (int k = 0; k < myArraySize; k++) {
        insertionSortArray[k] = (char*)malloc(100 * sizeof(char));  // Assume max word length is 100
        if (insertionSortArray[k] == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }
        printf("word[%d] = ", k);
        scanf("%s", insertionSortArray[k]);
    }

    printf("\n");

    // Sort characters within each string
    for (int k = 0; k < myArraySize; k++) {
        sortCharacters(insertionSortArray[k]);
    }

    // Print the array after sorting characters within each string
    printf("Array after sorting characters within each string: \n");
    printArray(insertionSortArray, myArraySize);

    // Sort the array of strings
    insertionSort(insertionSortArray, myArraySize);

    // Print the array after sorting the strings
    printf("Array after sorting the strings: \n");
    printArray(insertionSortArray, myArraySize);

    // Free allocated memory
    for (int k = 0; k < myArraySize; k++) {
        free(insertionSortArray[k]);
    }
    free(insertionSortArray);

    return 0;
}