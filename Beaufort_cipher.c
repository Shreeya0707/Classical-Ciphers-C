#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts plaintext using the Beaufort cipher with the given key.
 * The Beaufort cipher uses the formula: C = (K - P) mod 26
 * @param plaintext The text to encrypt
 * @param key The encryption key
 * @param result The buffer to store the encrypted text
 */
void beaufort_encrypt(const char *plaintext, const char *key, char *result) {
    int i, key_len, key_pos = 0;
    
    key_len = strlen(key);
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base_pt = isupper(plaintext[i]) ? 'A' : 'a';
            
            // Find the appropriate key character
            char key_char = key[key_pos % key_len];
            key_pos++;
            
            // Convert key to uppercase for consistent calculation
            key_char = toupper(key_char);
            
            // Apply Beaufort formula: (K - P) mod 26
            result[i] = (key_char - (plaintext[i] - base_pt) + 26) % 26 + 'A';
            
            // Preserve case
            if (islower(plaintext[i])) {
                result[i] = tolower(result[i]);
            }
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

/**
 * Decrypts ciphertext using the Beaufort cipher with the given key.
 * Since Beaufort is symmetric, the encryption function can be used.
 * @param ciphertext The text to decrypt
 * @param key The encryption key
 * @param result The buffer to store the decrypted text
 */
void beaufort_decrypt(const char *ciphertext, const char *key, char *result) {
    // The Beaufort cipher is its own inverse, so encryption is the same as decryption
    beaufort_encrypt(ciphertext, key, result);
}

// Test function
void test_beaufort_cipher() {
    char plaintext[] = "HELLOWORLD";
    char key[] = "KEY";
    char encrypted[100];
    char decrypted[100];
    
    beaufort_encrypt(plaintext, key, encrypted);
    beaufort_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
}