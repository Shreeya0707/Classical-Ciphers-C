#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2  // We'll implement a 2x2 Hill cipher

/**
 * Calculates determinant of a 2x2 matrix
 * @param matrix The 2x2 matrix
 * @return The determinant value
 */
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
}

/**
 * Calculates the modular multiplicative inverse
 * @param a The number to find inverse for
 * @param m The modulus
 * @return The modular multiplicative inverse of a mod m
 */
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No inverse exists
}

/**
 * Calculates the inverse of a 2x2 matrix (mod 26)
 * @param matrix The 2x2 matrix to invert
 * @param inverse The resulting inverse matrix
 * @return 1 if successful, 0 if the matrix is not invertible
 */
int matrix_inverse(int matrix[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    det = ((det % 26) + 26) % 26; // Ensure positive modulo
    
    // Calculate the modular multiplicative inverse of the determinant
    int det_inv = mod_inverse(det, 26);
    
    if (det_inv == -1) {
        return 0; // Matrix is not invertible modulo 26
    }
    
    // Calculate adjugate matrix and multiply by det_inv
    inverse[0][0] = (matrix[1][1] * det_inv) % 26;
    inverse[0][1] = ((-matrix[0][1] % 26 + 26) * det_inv) % 26;
    inverse[1][0] = ((-matrix[1][0] % 26 + 26) * det_inv) % 26;
    inverse[1][1] = (matrix[0][0] * det_inv) % 26;
    
    return 1;
}

/**
 * Encrypts plaintext using the Hill cipher with a 2x2 key matrix.
 * @param plaintext The text to encrypt
 * @param key_matrix The 2x2 key matrix
 * @param result The buffer to store the encrypted text
 * @return 1 if successful, 0 if the matrix is not invertible (for validation)
 */
int hill_encrypt(const char *plaintext, int key_matrix[MATRIX_SIZE][MATRIX_SIZE], char *result) {
    int i, j, k;
    int plain_len = strlen(plaintext);
    int padded_len = plain_len;
    
    // If length is odd, pad with 'X'
    if (padded_len % MATRIX_SIZE != 0) {
        padded_len += (MATRIX_SIZE - (padded_len % MATRIX_SIZE));
    }
    
    // Create padded plaintext
    char *padded_text = (char *)malloc(padded_len + 1);
    strcpy(padded_text, plaintext);
    
    // Fill padding
    for (i = plain_len; i < padded_len; i++) {
        padded_text[i] = 'X';
    }
    padded_text[padded_len] = '\0';
    
    // Process pairs of characters
    for (i = 0; i < padded_len; i += MATRIX_SIZE) {
        int vector[MATRIX_SIZE];
        int cipher_vector[MATRIX_SIZE];
        
        // Convert characters to numbers (A=0, B=1, ..., Z=25)
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (isalpha(padded_text[i+j])) {
                vector[j] = toupper(padded_text[i+j]) - 'A';
            } else {
                vector[j] = 0; // Use 0 for non-alphabetic (shouldn't happen with padding)
            }
        }
        
        // Multiply key matrix by vector
        for (j = 0; j < MATRIX_SIZE; j++) {
            cipher_vector[j] = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                cipher_vector[j] += key_matrix[j][k] * vector[k];
            }
            cipher_vector[j] = cipher_vector[j] % 26;
        }
        
        // Convert numbers back to characters
        for (j = 0; j < MATRIX_SIZE; j++) {
            result[i+j] = cipher_vector[j] + 'A';
        }
    }
    result[padded_len] = '\0';
    
    free(padded_text);
    
    // Verify the key matrix is invertible (just for validation)
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    return matrix_inverse(key_matrix, inverse);
}

/**
 * Decrypts ciphertext using the Hill cipher with a 2x2 key matrix.
 * @param ciphertext The text to decrypt
 * @param key_matrix The 2x2 key matrix
 * @param result The buffer to store the decrypted text
 * @return 1 if successful, 0 if the matrix is not invertible
 */
int hill_decrypt(const char *ciphertext, int key_matrix[MATRIX_SIZE][MATRIX_SIZE], char *result) {
    int i, j, k;
    int cipher_len = strlen(ciphertext);
    
    // Calculate inverse of key matrix
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    if (!matrix_inverse(key_matrix, inverse)) {
        return 0;  // Matrix is not invertible
    }
    
    // Process pairs of characters
    for (i = 0; i < cipher_len; i += MATRIX_SIZE) {
        int vector[MATRIX_SIZE];
        int plain_vector[MATRIX_SIZE];
        
        // Convert characters to numbers (A=0, B=1, ..., Z=25)
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (i+j < cipher_len && isalpha(ciphertext[i+j])) {
                vector[j] = toupper(ciphertext[i+j]) - 'A';
            } else {
                vector[j] = 0; // Use 0 for non-alphabetic or out of bounds
            }
        }
        
        // Multiply inverse key matrix by vector
        for (j = 0; j < MATRIX_SIZE; j++) {
            plain_vector[j] = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                plain_vector[j] += inverse[j][k] * vector[k];
            }
            plain_vector[j] = ((plain_vector[j] % 26) + 26) % 26; // Ensure positive
        }
        
        // Convert numbers back to characters
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (i+j < cipher_len) {
                result[i+j] = plain_vector[j] + 'A';
            }
        }
    }
    result[cipher_len] = '\0';
    
    return 1;
}

/**
 * Create a key matrix from a key string
 * @param key The key string
 * @param key_matrix The output key matrix
 * @return 1 if successful, 0 if the matrix is not invertible
 */
int create_key_matrix(const char *key, int key_matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k = 0;
    int key_len = strlen(key);
    
    // Fill the matrix with the key (or with default values if key is too short)
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (k < key_len && isalpha(key[k])) {
                key_matrix[i][j] = toupper(key[k]) - 'A';
                k++;
            } else {
                // Default values if key is too short (this makes a valid invertible matrix)
                switch (i * MATRIX_SIZE + j) {
                    case 0: key_matrix[i][j] = 5; break;  // [0][0]
                    case 1: key_matrix[i][j] = 8; break;  // [0][1]
                    case 2: key_matrix[i][j] = 17; break; // [1][0]
                    case 3: key_matrix[i][j] = 3; break;  // [1][1]
                }
            }
        }
    }
    
    // Check if the matrix is invertible
    int inverse[MATRIX_SIZE][MATRIX_SIZE];
    return matrix_inverse(key_matrix, inverse);
}

/**
 * Main function to showcase the Hill cipher
 */
int main() {
    char plaintext[1000];
    char key[100];
    char encrypted[1000];
    char decrypted[1000];
    int key_matrix[MATRIX_SIZE][MATRIX_SIZE];
    
    printf("Hill Cipher Implementation (2x2 matrix)\n");
    printf("---------------------------------------\n");
    
    // Get plaintext from user
    printf("Enter plaintext (letters only): ");
    scanf("%s", plaintext);
    
    // Get key from user
    printf("Enter key (at least 4 letters, only first 4 will be used): ");
    scanf("%s", key);
    
    // Create key matrix
    if (!create_key_matrix(key, key_matrix)) {
        printf("The key does not produce an invertible matrix. Please try another key.\n");
        return 1;
    }
    
    // Display key matrix
    printf("\nKey Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%2d ", key_matrix[i][j]);
        }
        printf("\n");
    }
    
    // Encrypt
    if (hill_encrypt(plaintext, key_matrix, encrypted)) {
        printf("\nEncrypted text: %s\n", encrypted);
        
        // Decrypt
        if (hill_decrypt(encrypted, key_matrix, decrypted)) {
            printf("Decrypted text: %s\n", decrypted);
        } else {
            printf("Decryption failed: Matrix is not invertible.\n");
        }
    } else {
        printf("Encryption failed: Matrix is not invertible.\n");
    }
    
    return 0;
}