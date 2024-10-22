#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26
void encrypt(char text[], char key[]) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            text[i] = toupper(key[ch - 'A']);
        }
        else if (islower(ch)) {
            text[i] = tolower(key[ch - 'a']);
        }
    }
}

int main() {
    char text[100];
    char key[ALPHABET_SIZE + 1]; 
    char alphabet[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the 26-letter substitution key (cipher alphabet): ");
    scanf("%s", key);
    if (strlen(key) != ALPHABET_SIZE) {
        printf("Invalid key! The key must contain exactly 26 letters.\n");
        return 1;
    }
    encrypt(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}
