#include <stdio.h>
#include <string.h>

void encryptBlock(char *plaintext, char *ciphertext) {
    strcpy(ciphertext, plaintext); 
}

void decryptBlock(char *ciphertext, char *plaintext) {
    strcpy(plaintext, ciphertext); 
}

void simulateTransmittedCiphertextError(char *ciphertext, int blockIndex) {
    ciphertext[blockIndex] ^= 0x01;  
}

int main() {
    char P1[] = "Hello, this is P1.", P2[] = "And this is P2.";
    char C1[20], C2[20], C1_error[20], P1_error[20], P2_decrypted[20];

    encryptBlock(P1, C1);
    encryptBlock(P2, C2);

    printf("ECB Mode:\nOriginal C1: %s\nOriginal C2: %s\n", C1, C2);

    strcpy(C1_error, C1);  
    simulateTransmittedCiphertextError(C1_error, 5);

    printf("Transmitted C1 with error: %s\n", C1_error);

    decryptBlock(C1_error, P1_error);  
    printf("Decrypted P1 (with error): %s\n", P1_error);

    decryptBlock(C2, P2_decrypted);  
    printf("Decrypted P2: %s\n", P2_decrypted);

    return 0;
}
