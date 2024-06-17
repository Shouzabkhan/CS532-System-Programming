#include <stdio.h>
#include <string.h>

void reverseStr(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    char n3[100];
    
    // Prompt the user for input
    printf("Enter a positive integer: ");
    scanf("%s", n3);
    
    // Check if the input is positive
    if (n3[0] == '-') {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    
    // Reverse the string and print the result
    reverseStr(n3);
    printf("Reversed number: %s\n", n3);
    
    return 0;
}