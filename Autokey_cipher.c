#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Encrypts plaintext using the Autokey cipher with the given key.
 * @param plaintext The text to encrypt
 * @param key The initial encryption key
 * @param result The buffer to store the encrypted text
 */
void autokey_encrypt(const char *plaintext, const char *key, char *result) {
    int i, j, plaintext_len, key_len;
    char *full_key;
    
    plaintext_len = strlen(plaintext);
    key_len = strlen(key);
    
    // Create an extended key (initial key + plaintext)
    full_key = (char *)malloc(key_len + plaintext_len + 1);
    
    // Copy initial key
    strcpy(full_key, key);
    
    // Append plaintext characters to create full key
    j = 0;
    for (i = key_len; i < key_len + plaintext_len; i++) {
        if (isalpha(plaintext[j])) {
            full_key[i] = toupper(plaintext[j]);
        } else {
            // Skip non-alphabet characters in plaintext
            i--;
        }
        j++;
    }
    full_key[key_len + plaintext_len] = '\0';
    
    // Apply Vigenere-like encryption with the full key
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base_pt = isupper(plaintext[i]) ? 'A' : 'a';
            char key_char = toupper(full_key[i]) - 'A';
            
            result[i] = ((plaintext[i] - base_pt) + key_char) % 26 + base_pt;
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
    
    free(full_key);
}

/**
 * Decrypts ciphertext using the Autokey cipher with the given key.
 * @param ciphertext The text to decrypt
 * @param key The initial encryption key
 * @param result The buffer to store the decrypted text
 */
void autokey_decrypt(const char *ciphertext, const char *key, char *result) {
    int i, key_pos = 0, key_len;
    
    key_len = strlen(key);
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base_ct = isupper(ciphertext[i]) ? 'A' : 'a';
            char key_char;
            
            if (key_pos < key_len) {
                // Use initial key
                key_char = toupper(key[key_pos]) - 'A';
            } else {
                // Use previously decrypted character
                key_char = toupper(result[key_pos - key_len]) - 'A';
            }
            
            key_pos++;
            
            // Apply Autokey decryption formula
            result[i] = ((ciphertext[i] - base_ct) - key_char + 26) % 26 + base_ct;
        } else {
            result[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

// Test function
void test_autokey_cipher() {
    char plaintext[] = "HELLOWORLD";
    char key[] = "KEY";
    char encrypted[100];
    char decrypted[100];
    
    autokey_encrypt(plaintext, key, encrypted);
    autokey_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Initial Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
}