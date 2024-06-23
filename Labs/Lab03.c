#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to print array
void printArray(char** A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", A[i]);
    }
    printf("\n");
}

// Function to sort characters within a string using insertion sort
void sortCharacters(char* str) {
    int len = strlen(str);
    for (int i = 1; i < len; i++) {
        char key = str[i];
        int j = i - 1;
        while (j >= 0 && str[j] > key) {
            str[j + 1] = str[j];
            j--;
        }
        str[j + 1] = key;
    }
}

// Insertion Sort function for strings
void insertionSort(char** A, int n) {
    char* key;
    int j;
    // Loop for passes
    for (int i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        // Loop for each pass
        while (j >= 0 && strcmp(A[j], key) > 0) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

// Main function
int main() {
    // Declaration of size for the array and taking input from the user
    int myArraySize;
    printf("Enter the size of the array: \n");
    scanf("%d", &myArraySize);

    // Allocate memory for array of strings
    char** insertionSortArray = (char**)malloc(myArraySize * sizeof(char*));
    if (insertionSortArray == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Taking user input for the array elements
    printf("Enter the words that you want to sort: \n");

    // Using loop for this purpose
    for (int k = 0; k < myArraySize; k++) {
        insertionSortArray[k] = (char*)malloc(100 * sizeof(char));  // assuming max word length is 100
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

    // Calling printArray function to print all the values in the array after character sorting
    printf("Array after sorting characters within each string: \n");
    printArray(insertionSortArray, myArraySize);

    // Calling insertionSort function to sort the array of strings
    insertionSort(insertionSortArray, myArraySize);

    // Calling printArray function to print all the sorted values in the array
    printf("Array after sorting the strings: \n");
    printArray(insertionSortArray, myArraySize);

    // Free allocated memory
    for (int k = 0; k < myArraySize; k++) {
        free(insertionSortArray[k]);
    }
    free(insertionSortArray);

    return 0;
}