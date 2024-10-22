#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
int charToNum(char c) {
    return toupper(c) - 'A';
}
char numToChar(int num) {
    return num + 'A';
}
void encryptHill(char *text, int *keyMatrix, int keySize) {
    int i, j, k, textLen = strlen(text), encrypted[MAX_LEN] = {0};

    for (i = 0; i < textLen; i += keySize) {
        for (j = 0; j < keySize; j++) {
            int sum = 0;
            for (k = 0; k < keySize; k++) {
                sum += keyMatrix[j * keySize + k] * charToNum(text[i + k]);
            }
            encrypted[i + j] = sum % 26;
        }
    }

    for (i = 0; i < textLen; i++) {
        text[i] = numToChar(encrypted[i]);
    }
}
int main() {
    char plaintext[MAX_LEN] = "MEET ME AT THE USUAL PLACE AT TEN RATHER THAN EIGHT OCLOCK";
    int keySize = 2;  
    int keyMatrix[] = {9, 4, 5, 7};  
    char processedText[MAX_LEN] = {0};
    int index = 0;

    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {  
            processedText[index++] = toupper(plaintext[i]);
        }
    }
    processedText[index] = '\0'; 

    int textLen = strlen(processedText);
    int padding = keySize - (textLen % keySize);
    if (padding < keySize) {
        memset(processedText + textLen, 'X', padding);
        processedText[textLen + padding] = '\0';
    }
    encryptHill(processedText, keyMatrix, keySize);
    printf("Encrypted text: %s\n", processedText);

    return 0;
}
