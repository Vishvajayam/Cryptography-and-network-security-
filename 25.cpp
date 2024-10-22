#include <stdio.h>
int gcd(int a, int b) {
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int e, int phi) {
    for (int d = 1; d < phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}
int decryptWithCommonFactor(int n, int e, int blocks[], int len) {
    int commonFactor = 0;
    for (int i = 0; i < len; i++) {
        int currentGCD = gcd(blocks[i], n);
        if (currentGCD != 1 && currentGCD != n) {
            commonFactor = currentGCD;
            break;
        }
    }

    if (commonFactor) {
        int p = commonFactor;
        int q = n / p;
        int phi = (p - 1) * (q - 1);
        int d = modInverse(e, phi);

        if (d == -1) {
            printf("Modular inverse could not be found.\n");
            return 0;
        }
        printf("Decrypted plaintext blocks: ");
        for (int i = 0; i < len; i++) {
            int plaintext = 1;
            for (int j = 0; j < d; j++) {
                plaintext = (plaintext * blocks[i]) % n;
            }
            printf("%d ", plaintext);
        }
        printf("\n");
    } else {
        printf("No common factor found.\n");
    }
    return 0;
}

int main() {
    int n = 3233; 
    int e = 17;   
    int blocks[] = {1791, 123, 2509, 1281}; 
    int len = sizeof(blocks) / sizeof(blocks[0]);

    decryptWithCommonFactor(n, e, blocks, len);

    return 0;
}
