#include <stdio.h>
int mod_exp(int base, int exp, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % modulus;
        }
        exp = exp >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int prime = 23; 
    int base = 5;   

    int alicePrivateKey = 6; 
    int bobPrivateKey = 15; 
    int alicePublicKey = mod_exp(base, alicePrivateKey, prime);
    int bobPublicKey = mod_exp(base, bobPrivateKey, prime);
    printf("Alice's Public Key: %d\n", alicePublicKey);
    printf("Bob's Public Key: %d\n", bobPublicKey);
    int aliceSharedSecret = mod_exp(bobPublicKey, alicePrivateKey, prime);
    int bobSharedSecret = mod_exp(alicePublicKey, bobPrivateKey, prime);
    printf("Alice's Shared Secret: %d\n", aliceSharedSecret);
    printf("Bob's Shared Secret: %d\n", bobSharedSecret);

    return 0;
}
