#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts or decrypts text using the Atbash cipher.
 * Since Atbash is its own inverse, the same function is used for both.
 * @param text The text to encrypt/decrypt
 * @param result The buffer to store the result
 */
void atbash_cipher(const char *text, char *result) {
    int i;
    
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i])) {
                result[i] = 'Z' - (text[i] - 'A');
            } else {
                result[i] = 'z' - (text[i] - 'a');
            }
        } else {
            result[i] = text[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

// Test function
void test_atbash_cipher() {
    char plaintext[] = "HELLOWORLD";
    char encrypted[100];
    char decrypted[100];
    
    atbash_cipher(plaintext, encrypted);
    atbash_cipher(encrypted, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
}