#include <stdio.h>
#include <stdint.h>
uint8_t xorBlocks(uint8_t a, uint8_t b) {
    return a ^ b;
}
void generateKeys(uint8_t key, uint8_t *K1, uint8_t *K2) {
    *K1 = (key & 0xF0) >> 1 | (key & 0x0F);
    *K2 = ((key & 0x0F) << 3) | ((key & 0xF0) >> 4);
}
uint8_t sdesEncrypt(uint8_t plaintext, uint8_t K1, uint8_t K2) {
    uint8_t temp = plaintext ^ K1; 
    temp = (temp << 2) | (temp >> 6); 
    return temp ^ K2; 
}
uint8_t sdesDecrypt(uint8_t ciphertext, uint8_t K1, uint8_t K2) {
    uint8_t temp = ciphertext ^ K2; 
    temp = (temp >> 2) | (temp << 6); 
    return temp ^ K1; 
}
void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t iv, int size, uint8_t K1, uint8_t K2) {
    uint8_t previousBlock = iv;

    for (int i = 0; i < size; i++) {
        uint8_t xorResult = xorBlocks(plaintext[i], previousBlock);
        ciphertext[i] = sdesEncrypt(xorResult, K1, K2);
        previousBlock = ciphertext[i];
    }
}
void cbcDecrypt(uint8_t *ciphertext, uint8_t *decrypted, uint8_t iv, int size, uint8_t K1, uint8_t K2) {
    uint8_t previousBlock = iv;

    for (int i = 0; i < size; i++) {
        uint8_t decryptedBlock = sdesDecrypt(ciphertext[i], K1, K2);
        decrypted[i] = xorBlocks(decryptedBlock, previousBlock);
        previousBlock = ciphertext[i];
    }
}

int main() {
    uint8_t plaintext[] = {0x00, 0x01, 0x02, 0x03}; 
    uint8_t ciphertext[4], decrypted[4];
    uint8_t key = 0x1F; 
    uint8_t iv = 0xAA;  
    uint8_t K1, K2;
    generateKeys(key, &K1, &K2);
    cbcEncrypt(plaintext, ciphertext, iv, 4, K1, K2);
    printf("Ciphertext:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    cbcDecrypt(ciphertext, decrypted, iv, 4, K1, K2);
    printf("Decrypted Plaintext:\n");
    for (int i = 0; i < 4; i++) {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    return 0;
}
