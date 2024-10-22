#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void createCipherAlphabet(char* keyword, char* cipherAlphabet) {
    int used[ALPHABET_SIZE] = {0};  
    int index = 0;
    for (int i = 0; i < strlen(keyword); i++) {
        char c = toupper(keyword[i]);  
        if (isalpha(c) && !used[c - 'A']) {  
            cipherAlphabet[index++] = c;
            used[c - 'A'] = 1;  
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipherAlphabet[index++] = c;  
        }
    }
    
    cipherAlphabet[index] = '\0'; 
}
void encrypt(char* plaintext, char* cipherAlphabet, char* encryptedText) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char c = toupper(plaintext[i]);  
        if (isalpha(c)) {
            int pos = c - 'A';  
            encryptedText[i] = cipherAlphabet[pos];  
        } else {
            encryptedText[i] = plaintext[i];  
        }
    }
    encryptedText[strlen(plaintext)] = '\0'; 
}

int main() {
    char keyword[100], plaintext[100], cipherAlphabet[ALPHABET_SIZE + 1], encryptedText[100];
    printf("Enter the keyword: ");
    scanf("%s", keyword);
    createCipherAlphabet(keyword, cipherAlphabet);
    printf("Cipher Alphabet: %s\n", cipherAlphabet);
    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);  
    encrypt(plaintext, cipherAlphabet, encryptedText);
    printf("Encrypted Text: %s\n", encryptedText);

    return 0;
}
