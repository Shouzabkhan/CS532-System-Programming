#include <stdio.h>
#include <stdbool.h>

// Function to check if a number is prime
bool PrimeNotPrime(int number) {
    if (number <= 1) {
        return false;
    }
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int Given_Number;

    // Read the integer variable given_number
    printf("Enter a number: ");
    scanf("%d", &Given_Number);

    // Check if the given number is prime
    if (PrimeNotPrime(Given_Number)) {
        printf("The number is prime\n");
    } else {
        printf("The number is not prime\n");
    }

    return 0;
}