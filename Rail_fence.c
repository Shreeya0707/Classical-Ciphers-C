#include <stdio.h>
#include <string.h>

void encryptRailFence(char *text, char *cipher) {
    int len = strlen(text);
    int k = 0;

    // Even index characters
    for (int i = 0; i < len; i += 2) {
        cipher[k++] = text[i];
    }
    // Odd index characters
    for (int i = 1; i < len; i += 2) {
        cipher[k++] = text[i];
    }
    cipher[k] = '\0';
}

void decryptRailFence(char *cipher, char *text) {
    int len = strlen(cipher);
    int k = 0;
    int half = (len + 1) / 2;
    int i = 0, j = half;

    while (k < len) {
        if (i < half) text[k++] = cipher[i++];
        if (j < len)  text[k++] = cipher[j++];
    }
    text[k] = '\0';
}

int main() {
    char msg[100], cipher[100], decrypted[100];

    printf("Enter text: ");
    scanf("%s", msg);

    encryptRailFence(msg, cipher);
    printf("Encrypted: %s\n", cipher);

    decryptRailFence(cipher, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
