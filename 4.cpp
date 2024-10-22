#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generate_key(const char *plaintext, const char *keyword, char *key) {
    int text_len = strlen(plaintext);
    int key_len = strlen(keyword);
    int i, j;
    for (i = 0, j = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            key[i] = toupper(keyword[j % key_len]);
            j++;
        } else {
            key[i] = plaintext[i];  
        }
    }
    key[text_len] = '\0'; 
}
void encrypt(const char *plaintext, const char *key, char *ciphertext) {
    int text_len = strlen(plaintext);
    int shift, i;

    for (i = 0; i < text_len; i++) {
        if (isalpha(plaintext[i])) {
            shift = toupper(key[i]) - 'A';

            if (isupper(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'A' + shift) % 26 + 'A';
            } else if (islower(plaintext[i])) {
                ciphertext[i] = (plaintext[i] - 'a' + shift) % 26 + 'a';
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[text_len] = '\0';  
}

int main() {
    char plaintext[100], keyword[100], key[100], ciphertext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; 
    generate_key(plaintext, keyword, key);
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
