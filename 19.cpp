#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8  
void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}
void encrypt_3des_ecb(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
}
void cbc_encrypt_3des(uint8_t *plaintext, uint8_t *key, uint8_t *iv, uint8_t *ciphertext, size_t length) {
    uint8_t block[BLOCK_SIZE];
    uint8_t xor_block[BLOCK_SIZE];
    memcpy(xor_block, iv, BLOCK_SIZE);  
    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        xor_blocks(&plaintext[i], xor_block, block);
        encrypt_3des_ecb(block, key, &ciphertext[i]);
        memcpy(xor_block, &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "This is a secret message.";
    uint8_t key[24] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF, 
                       0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF,
                       0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  
    uint8_t ciphertext[256];  
    size_t length = strlen((char *)plaintext);
    size_t padded_length = (length + BLOCK_SIZE - 1) / BLOCK_SIZE * BLOCK_SIZE;
    cbc_encrypt_3des(plaintext, key, iv, ciphertext, padded_length);
    printf("Ciphertext: ");
    for (size_t i = 0; i < padded_length; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
