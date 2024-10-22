#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}
char affineEncrypt(char plaintext, int a, int b) {
    if (plaintext >= 'A' && plaintext <= 'Z') {
        int p = plaintext - 'A';  
        int c = (a * p + b) % 26; 
        return (c + 'A');         
    }
    return plaintext; 
}
char affineDecrypt(char ciphertext, int a, int b) {
    if (ciphertext >= 'A' && ciphertext <= 'Z') {
        int c = ciphertext - 'A';  
        int a_inv = modInverse(a, 26);  
        if (a_inv == -1) {
            printf("Inverse doesn't exist for a = %d\n", a);
            exit(1);
        }
        int p = (a_inv * (c - b + 26)) % 26; 
        return (p + 'A');  
    }
    return ciphertext;  
}

int main() {
    char plaintext[100], ciphertext[100];
    int a, b;
    printf("Enter values for a and b (for the cipher C = (a * P + b) mod 26): ");
    scanf("%d %d", &a, &b);
    if (gcd(a, 26) != 1) {
        printf("'a' must be coprime with 26. Invalid value for a.\n");
        return 1;
    }
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affineEncrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';  
    printf("Encrypted message: %s\n", ciphertext);
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = affineDecrypt(ciphertext[i], a, b);
    }
    plaintext[strlen(ciphertext)] = '\0';  
    printf("Decrypted message: %s\n", plaintext);

    return 0;
}
