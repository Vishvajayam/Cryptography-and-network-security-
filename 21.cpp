#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 16
#define SEGMENT_SIZE 8
void xorBlocks(char *a, char *b, char *result, int len) {
    for (int i = 0; i < len; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void padBlock(char *block, int blockSize, int dataSize, char *paddedBlock) {
    strncpy(paddedBlock, block, dataSize);
    for (int i = dataSize; i < blockSize - 1; i++) {
        paddedBlock[i] = 0x00;
    }
    paddedBlock[blockSize - 1] = 0x80; 
}
void ecbEncrypt(char *paddedPlaintext, char *ciphertext, int paddedSize) {
    for (int i = 0; i < paddedSize; i += BLOCK_SIZE) {
        strncpy(&ciphertext[i], &paddedPlaintext[i], BLOCK_SIZE);
    }
}
void cbcEncrypt(char *paddedPlaintext, char *ciphertext, char *iv, int paddedSize) {
    char previousBlock[BLOCK_SIZE];
    strncpy(previousBlock, iv, BLOCK_SIZE);

    for (int i = 0; i < paddedSize; i += BLOCK_SIZE) {
        char xorResult[BLOCK_SIZE];
        xorBlocks(&paddedPlaintext[i], previousBlock, xorResult, BLOCK_SIZE);
        strncpy(&ciphertext[i], xorResult, BLOCK_SIZE);
        strncpy(previousBlock, &ciphertext[i], BLOCK_SIZE);
    }
}
void cfbEncrypt(char *paddedPlaintext, char *ciphertext, char *iv, int paddedSize) {
    char shiftRegister[BLOCK_SIZE];
    strncpy(shiftRegister, iv, BLOCK_SIZE);

    for (int i = 0; i < paddedSize; i += SEGMENT_SIZE) {
        char xorResult[SEGMENT_SIZE];
        xorBlocks(&paddedPlaintext[i], shiftRegister, xorResult, SEGMENT_SIZE);
        strncpy(&ciphertext[i], xorResult, SEGMENT_SIZE);
        for (int j = SEGMENT_SIZE; j < BLOCK_SIZE; j++) {
            shiftRegister[j - SEGMENT_SIZE] = shiftRegister[j];
        }
        strncpy(&shiftRegister[BLOCK_SIZE - SEGMENT_SIZE], xorResult, SEGMENT_SIZE);
    }
}

int main() {
    char plaintext[] = "This is a test message for encryption.";
    int dataSize = strlen(plaintext);
    int paddedSize = ((dataSize + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE;
    char paddedPlaintext[paddedSize];
    padBlock(paddedPlaintext, BLOCK_SIZE, dataSize, paddedPlaintext);
    char ecbCiphertext[paddedSize];
    char cbcCiphertext[paddedSize];
    char cfbCiphertext[paddedSize];
    char iv[BLOCK_SIZE] = "InitializationV";
    printf("ECB Mode:\n");
    ecbEncrypt(paddedPlaintext, ecbCiphertext, paddedSize);
    printf("Ciphertext: %s\n", ecbCiphertext);
    printf("CBC Mode:\n");
    cbcEncrypt(paddedPlaintext, cbcCiphertext, iv, paddedSize);
    printf("Ciphertext: %s\n", cbcCiphertext);
    printf("CFB Mode:\n");
    cfbEncrypt(paddedPlaintext, cfbCiphertext, iv, paddedSize);
    printf("Ciphertext: %s\n", cfbCiphertext);

    return 0;
}
