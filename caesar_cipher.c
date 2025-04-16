#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts plaintext using the Caesar cipher with the given shift.
 * @param plaintext The text to encrypt
 * @param shift The number of positions to shift each character
 * @param result The buffer to store the encrypted text
 */
void caesar_encrypt(const char *plaintext, int shift, char *result) {
    int i;
    
    // Ensure shift is in range 0-25
    shift = shift % 26;
    if (shift < 0) {
        shift += 26;
    }
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            result[i] = (plaintext[i] - base + shift) % 26 + base;
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

/**
 * Decrypts ciphertext using the Caesar cipher with the given shift.
 * @param ciphertext The text to decrypt
 * @param shift The number of positions used for encryption
 * @param result The buffer to store the decrypted text
 */
void caesar_decrypt(const char *ciphertext, int shift, char *result) {
    // Decryption is just encryption with the negative shift
    caesar_encrypt(ciphertext, -shift, result);
}

// Test function
void test_caesar_cipher() {
    char plaintext[] = "HELLOWORLD";
    char encrypted[100];
    char decrypted[100];
    int shift = 3;
    
    caesar_encrypt(plaintext, shift, encrypted);
    caesar_decrypt(encrypted, shift, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Encrypted with shift %d: %s\n", shift, encrypted);
    printf("Decrypted: %s\n", decrypted);
}