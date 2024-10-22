#include <stdio.h>
#include <stdlib.h>
unsigned long long mod_exp(unsigned long long base, unsigned long long exp, unsigned long long modulus) {
    unsigned long long result = 1;
    base %= modulus;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % modulus;
        }
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
unsigned long long encrypt(unsigned long long character, unsigned long long e, unsigned long long n) {
    return mod_exp(character, e, n);
}

int main() {
    unsigned long long p, q, n, phi, e, character;
    char message[1000];
    p = 9973;  
    q = 9857;  
    n = p * q; 
    e = 65537; 

    
    printf("Enter the message (all uppercase letters without spaces): ");
    scanf("%s", message);

    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        character = message[i] - 'A'; 
        unsigned long long encrypted_char = encrypt(character, e, n);
        printf("%llu ", encrypted_char);
    }
    printf("\n");

    return 0;
}
