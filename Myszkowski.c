#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encryptMyszkowski(char *text, char *key) {
    int len = strlen(text);
    int keyLen = strlen(key);
    int rows = (len + keyLen - 1) / keyLen;
    char matrix[rows][keyLen];

    // Fill matrix row-wise
    for (int i = 0; i < rows * keyLen; i++) {
        if (i < len)
            matrix[i / keyLen][i % keyLen] = text[i];
        else
            matrix[i / keyLen][i % keyLen] = '_'; // padding
    }

    // Process unique digits in order
    for (char ch = '1'; ch <= '9'; ch++) {
        for (int c = 0; c < keyLen; c++) {
            if (key[c] == ch) {
                for (int r = 0; r < rows; r++) {
                    printf("%c", matrix[r][c]);
                }
            }
        }
    }
    printf("\n");
}

int main() {
    char text[100], key[10];

    printf("Enter the text: ");
    scanf("%s", text);
    printf("Enter numeric key (e.g. 123112): ");
    scanf("%s", key);

    printf("Encrypted text: ");
    encryptMyszkowski(text, key);

    return 0;
}
