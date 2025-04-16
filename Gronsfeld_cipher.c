#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Encrypts plaintext using the Gronsfeld cipher with the given numeric key.
 * @param plaintext The text to encrypt
 * @param key The numeric key (as a string of digits)
 * @param result The buffer to store the encrypted text
 */
void gronsfeld_encrypt(const char *plaintext, const char *key, char *result) {
    int i, key_len, key_pos = 0;
    
    key_len = strlen(key);
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base_pt = isupper(plaintext[i]) ? 'A' : 'a';
            
            // Get the current digit from the key (as an integer)
            int shift = key[key_pos % key_len] - '0';
            key_pos++;
            
            // Apply the shift (similar to Caesar cipher but with varying shifts)
            result[i] = ((plaintext[i] - base_pt) + shift) % 26 + base_pt;
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

/**
 * Decrypts ciphertext using the Gronsfeld cipher with the given numeric key.
 * @param ciphertext The text to decrypt
 * @param key The numeric key (as a string of digits)
 * @param result The buffer to store the decrypted text
 */
void gronsfeld_decrypt(const char *ciphertext, const char *key, char *result) {
    int i, key_len, key_pos = 0;
    
    key_len = strlen(key);
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base_ct = isupper(ciphertext[i]) ? 'A' : 'a';
            
            // Get the current digit from the key (as an integer)
            int shift = key[key_pos % key_len] - '0';
            key_pos++;
            
            // Apply the reverse shift
            result[i] = ((ciphertext[i] - base_ct) - shift + 26) % 26 + base_ct;
        } else {
            result[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
}

// Test function
void test_gronsfeld_cipher() {
    char plaintext[] = "HELLOWORLD";
    char key[] = "2019";
    char encrypted[100];
    char decrypted[100];
    
    gronsfeld_encrypt(plaintext, key, encrypted);
    gronsfeld_decrypt(encrypted, key, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Key: %s\n", key);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
}