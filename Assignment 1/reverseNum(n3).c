#include <stdio.h>

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

int main() {
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
    
    return 0;
}