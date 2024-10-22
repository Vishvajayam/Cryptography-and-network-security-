#include <stdio.h>
#include <ctype.h>

void encrypt(char text[], int key) {
    char ch;
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];
        if (isupper(ch)) {
            ch = (ch - 'A' + key) % 26 + 'A';
        }
        else if (islower(ch)) {
            ch = (ch - 'a' + key) % 26 + 'a';
        }
        text[i] = ch;
    }
}

int main() {
    char text[100];
    int key;
    printf("Enter a message to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter the shift key (1-25): ");
    scanf("%d", &key);
    if (key < 1 || key > 25) {
        printf("Invalid key! Please enter a key between 1 and 25.\n");
        return 1;
    }
    encrypt(text, key);
    printf("Encrypted message: %s\n", text);

    return 0;
}
