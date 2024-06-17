#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// Function prototypes
void arrayDetails(int *arr, int size);
int is_prime(int n);
int nearest_prime_below(int n);
int sum_of_digits(int n);
char* numberTransformer(int n);
int reverseNum(int n3);
int smallerThanIndex(int *numbers, int size);
int UABNumber(int n);

int main() {
    int choice;
    printf("Choose a function to execute:\n");
    printf("1. Array Details\n");
    printf("2. Number Transformer\n");
    printf("3. Reverse Number\n");
    printf("4. Count of Numbers Smaller Than Their Index\n");
    printf("5. UAB Number\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // To consume the newline character after scanf

    switch(choice) {
        case 1: {
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
            break;
        }
        case 2: {
            int n;
            printf("Enter a positive integer n: ");
            scanf("%d", &n);
            printf("Output: %s\n", numberTransformer(n));
            break;
        }
        case 3: {
            int n3;
            // Prompt the user for input
            printf("Enter a positive integer: ");
            scanf("%d", &n3);
            // Check if the input is positive
            if (n3 <= 0) {
                printf("Please enter a positive integer.\n");
                return 1;
            }
            // Reverse the number and print the result
            int result = reverseNum(n3);
            printf("Reversed number: %d\n", result);
            break;
        }
        case 4: {
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
            break;
        }
        case 5: {
            int n;
            printf("Enter an integer: ");
            scanf("%d", &n);
            // Calling the UABNumber function and printing the result
            if (UABNumber(n)) {
                printf("%d TRUE.\n", n);
            } else {
                printf("%d FALSE.\n", n);
            }
            break;
        }
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

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

int is_prime(int n) {
    if (n <= 1) return 0; // 0 and 1 are not primes
    if (n <= 3) return 1; // 2 and 3 are primes
    if (n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes

    // check divisibility by numbers of the form 6k ± 1 up to sqrt(n)
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1; // if no divisor found, n is prime
}

int nearest_prime_below(int n) {
    for (int i = n - 1; i >= 2; i--) {
        if (is_prime(i)) {
            return i;
        }
    }
    return 0; // no prime found below n
}

int sum_of_digits(int n) {
    int sum = 0;
    while (n != 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

char* numberTransformer(int n) {
    static char result[20]; // assuming the result won't exceed 20 characters

    if (is_prime(n) && n != 3 && n != 5) {
        sprintf(result, "Go Blazers");
    } else if (pow(2, (int)(log(n) / log(2))) == n) {
        int nearest_prime = nearest_prime_below(n);
        sprintf(result, "%d", n + nearest_prime);
    } else if (sum_of_digits(n) % 3 == 0) {
        sprintf(result, "CS");
    } else if (n % 3 == 0 && n % 5 == 0) {
        sprintf(result, "UAB CS 332&532");
    } else {
        int sum = sum_of_digits(n);
        sprintf(result, "%d", sum * sum);
    }

    return result;
}

int reverseNum(int n3) {
    int reversed = 0;
    
    while (n3 > 0) {
        // Get the last digit of n3
        int lastDigit = n3 % 10;
        
        // Append lastDigit to reversed
        reversed = (reversed * 10) + lastDigit;
        
        // Remove the last digit from n3
        n3 = n3 / 10;
    }
    
    return reversed;
}

int smallerThanIndex(int *numbers, int size) {
    int count = 0;

    for (int i = 0; i < size; i++) {
        if (*(numbers + i) < i) {
            count++;
        }
    }

    return count;
}

int UABNumber(int n) {
    int sum = 0;
    
    // Finding the sum of positive divisors
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) {
            sum += i;
        }
    }

    // Comparing the sum with the number itself
    if (sum == n) {
        return 1; // True, the number is a UABNumber
    } else {
        return 0; // False, the number is not a UABNumber
    }
}