#include <stdio.h>

// Function to check if a number is a UABNumber
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

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    // Calling the UABNumber function and printing the result
    if (UABNumber(n)) {
        printf("%d TRUE.\n", n);
    } else {
        printf("%d FALSE.\n", n);
    }

    return 0;
} 