#include <stdio.h>
#include <math.h>

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

int main() {
    int n;
    printf("Enter a positive integer n: ");
    scanf("%d", &n);
    printf("Output: %s\n", numberTransformer(n));
    return 0;
}