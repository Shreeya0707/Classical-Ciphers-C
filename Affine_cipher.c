#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**
 * Calculate the greatest common divisor (GCD) of two numbers.
 * @param a First number
 * @param b Second number
 * @return The GCD of a and b
 */
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

/**
 * Calculate the modular multiplicative inverse of a number.
 * @param a The number to find the inverse for
 * @param m The modulus
 * @return The modular multiplicative inverse of a modulo m
 */
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return 1; // Should never reach here if a and m are coprime
}

/**
 * Encrypts plaintext using the Affine cipher with key (a, b).
 * @param plaintext The text to encrypt
 * @param a First part of the key (must be coprime to 26)
 * @param b Second part of the key
 * @param result The buffer to store the encrypted text
 * @return 1 if successful, 0 if a is not coprime to 26
 */
int affine_encrypt(const char *plaintext, int a, int b, char *result) {
    int i;
    
    // Check if a is coprime to 26
    if (gcd(a, 26) != 1) {
        return 0;
    }
    
    // Ensure b is in range 0-25
    b = ((b % 26) + 26) % 26;
    
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int x = plaintext[i] - base;
            
            // Apply Affine encryption formula: E(x) = (ax + b) mod 26
            result[i] = ((a * x + b) % 26) + base;
        } else {
            result[i] = plaintext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
    
    return 1;
}

/**
 * Decrypts ciphertext using the Affine cipher with key (a, b).
 * @param ciphertext The text to decrypt
 * @param a First part of the key (must be coprime to 26)
 * @param b Second part of the key
 * @param result The buffer to store the decrypted text
 * @return 1 if successful, 0 if a is not coprime to 26
 */
int affine_decrypt(const char *ciphertext, int a, int b, char *result) {
    int i, a_inv;
    
    // Check if a is coprime to 26
    if (gcd(a, 26) != 1) {
        return 0;
    }
    
    // Calculate modular multiplicative inverse of a
    a_inv = mod_inverse(a, 26);
    
    // Ensure b is in range 0-25
    b = ((b % 26) + 26) % 26;
    
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int y = ciphertext[i] - base;
            
            // Apply Affine decryption formula: D(y) = a^-1 * (y - b) mod 26
            int x = (a_inv * ((y - b + 26) % 26)) % 26;
            result[i] = x + base;
        } else {
            result[i] = ciphertext[i]; // Keep non-alphabetic characters unchanged
        }
    }
    result[i] = '\0';
    
    return 1;
}

// Test function
void test_affine_cipher() {
    char plaintext[] = "HELLOWORLD";
    char encrypted[100];
    char decrypted[100];
    int a = 5;
    int b = 8;
    
    if (affine_encrypt(plaintext, a, b, encrypted)) {
        if (affine_decrypt(encrypted, a, b, decrypted)) {
            printf("Original: %s\n", plaintext);
            printf("Keys: a=%d, b=%d\n", a, b);
            printf("Encrypted: %s\n", encrypted);
            printf("Decrypted: %s\n", decrypted);
        } else {
            printf("Decryption failed: 'a' must be coprime to 26\n");
        }
    } else {
        printf("Encryption failed: 'a' must be coprime to 26\n");
    }
}