#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts plaintext using the Vigenere cipher with the given key.
 * @param plaintext The text to encrypt
 * @param key The encryption key
 * @param result The buffer to store the encrypted text
 */
void vigenere_encrypt(const char *plaintext, const char *key, char *result) {
    int i, key_len, key_pos = 0;
    
    key_len = strlen(key);
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base_pt = isupper(plaintext[i]) ? 'A' : 'a';
            
            // Find the appropriate key character
            char key_char = key[key_pos % key_len];
            key_pos++;
            
            // Convert key to uppercase for consistent calculation
            key_char = toupper(key_char) - 'A';
            
            // Apply Vigenere encryption formula: (P + K) mod 26
            result[i] = ((plaintext[i] - base_pt) + key_char) % 26 + base_pt;
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
            // Don't increment key position for non-alphabetic characters
        }
    }
    result[i] = '\0';
}

/**
 * Decrypts ciphertext using the Vigenere cipher with the given key.
 * @param ciphertext The text to decrypt
 * @param key The encryption key
 * @param result The buffer to store the decrypted text
 */
void vigenere_decrypt(const char *ciphertext, const char *key, char *result) {
    int i, key_len, key_pos = 0;
    
    key_len = strlen(key);
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base_ct = isupper(ciphertext[i]) ? 'A' : 'a';
            
            // Find the appropriate key character
            char key_char = key[key_pos % key_len];
            key_pos++;
            
            // Convert key to uppercase for consistent calculation
            key_char = toupper(key_char) - 'A';
            
            // Apply Vigenere decryption formula: (C - K + 26) mod 26
            result[i] = ((ciphertext[i] - base_ct) - key_char + 26) % 26 + base_ct;
        } else {
            result[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
            // Don't increment key position for non-alphabetic characters
        }
    }
    result[i] = '\0';
}

// Test function
void test_vigenere_cipher() {
    char plaintext[] = "HELLOWORLD";
    char key[] = "KEY";
    char encrypted[100];
    char decrypted[100];
    
    vigenere_encrypt(plaintext, key, encrypted);
    vigenere_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
}