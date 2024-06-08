#include <stdio.h>
#include <stdbool.h>

// Function to check if a number is prime
bool PrimeNotPrime(int number) {
    // A number less than or equal to 1 is not prime
    if (number <= 1) {
        return false;
    }
    // Loop from 2 to the square root of the number
    for (int i = 2; i * i <= number; i++) {
        // If number is divisible by i, it's not prime
        if (number % i == 0) {
            return false;
        }
    }
    // If no divisors were found, the number is prime
    return true;
}

int main() {
    int Given_Number;

    // Prompt the user to enter an integer
    printf("Enter a number: ");
    
    // Read the integer input from the user
    if (scanf("%d", &Given_Number) != 1) {
        // If the input is not a valid integer, print an error message
        printf("Invalid input. Please enter a valid integer.\n");
        return 1; // Exit the program with an error code
    }

    // Determine if the input number is prime or not
    if (PrimeNotPrime(Given_Number)) {
        // If the number is prime, print a corresponding message
        printf("The number is prime\n");
    } else {
        // If the number is not prime, print a corresponding message
        printf("The number is not prime\n");
    }

    return 0; // Exit the program successfully
}