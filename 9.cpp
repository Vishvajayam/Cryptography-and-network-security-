#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decryptPlayfair(char *ciphertext, char *plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        char first = toupper(ciphertext[i]);
        char second = toupper(ciphertext[i + 1]);

        int row1, col1, row2, col2;
        findPosition(first, &row1, &col1);
        findPosition(second, &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = keyMatrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = keyMatrix[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = keyMatrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i + 1] = keyMatrix[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            plaintext[i] = keyMatrix[row1][col2];
            plaintext[i + 1] = keyMatrix[row2][col1];
        }
        i += 2;
    }
    plaintext[i] = '\0'; 
}

int main() {
    char ciphertext[] = "KXJEY UREBE ZWEHE WRYTU HEYFS";
    char plaintext[256];

    decryptPlayfair(ciphertext, plaintext);

    printf("Decrypted Message: %s\n", plaintext);
    return 0;
}
