#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define GRID_SIZE 5

/**
 * Generates the Playfair cipher key grid from a keyword.
 * @param keyword The keyword to use
 * @param grid The 5x5 grid to be filled
 */
void generate_grid(const char *keyword, char grid[GRID_SIZE][GRID_SIZE]) {
    char *alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Note: I and J are combined
    int i, j, k, len;
    char used[26] = {0}; // To track used letters
    
    // Convert keyword to uppercase
    char *upper_keyword = strdup(keyword);
    len = strlen(upper_keyword);
    for (i = 0; i < len; i++) {
        upper_keyword[i] = toupper(upper_keyword[i]);
        if (upper_keyword[i] == 'J') upper_keyword[i] = 'I'; // Replace J with I
    }
    
    // Fill the grid with the keyword first (ignoring duplicates)
    k = 0;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (k < len) {
                // Skip duplicates
                while (k < len && used[upper_keyword[k] - 'A']) {
                    k++;
                }
                
                if (k < len) {
                    grid[i][j] = upper_keyword[k];
                    used[upper_keyword[k] - 'A'] = 1;
                    k++;
                } else {
                    // Fill remaining with unused alphabet letters
                    for (int a = 0; a < 25; a++) {
                        if (!used[alphabet[a] - 'A']) {
                            grid[i][j] = alphabet[a];
                            used[alphabet[a] - 'A'] = 1;
                            break;
                        }
                    }
                }
            } else {
                // Fill remaining with unused alphabet letters
                for (int a = 0; a < 25; a++) {
                    if (!used[alphabet[a] - 'A']) {
                        grid[i][j] = alphabet[a];
                        used[alphabet[a] - 'A'] = 1;
                        break;
                    }
                }
            }
        }
    }
    
    free(upper_keyword);
}

/**
 * Prepares the plaintext for Playfair encryption (handles doubles, odd length, etc.)
 * @param text The input text
 * @param prepared The prepared text
 */
void prepare_text(const char *text, char *prepared) {
    int i, j = 0;
    int len = strlen(text);
    
    for (i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            prepared[j++] = toupper(text[i]);
            if (prepared[j-1] == 'J') prepared[j-1] = 'I'; // Replace J with I
        }
    }
    
    // Insert 'X' between double letters
    for (i = 0; i < j-1; i += 2) {
        if (prepared[i] == prepared[i+1]) {
            memmove(&prepared[i+2], &prepared[i+1], j-i);
            prepared[i+1] = 'X';
            j++;
        }
    }
    
    // Add a trailing 'X' if the length is odd
    if (j % 2 != 0) {
        prepared[j++] = 'X';
    }
    
    prepared[j] = '\0';
}

/**
 * Finds the position of a character in the key grid.
 * @param grid The 5x5 key grid
 * @param ch The character to find
 * @param row Output parameter for the row
 * @param col Output parameter for the column
 */
void find_position(char grid[GRID_SIZE][GRID_SIZE], char ch, int *row, int *col) {
    // Replace J with I
    if (ch == 'J') ch = 'I';
    
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/**
 * Encrypts plaintext using the Playfair cipher with a given keyword.
 * @param plaintext The text to encrypt
 * @param keyword The keyword for the cipher
 * @param result The buffer to store the encrypted text
 */
void playfair_encrypt(const char *plaintext, const char *keyword, char *result) {
    char grid[GRID_SIZE][GRID_SIZE];
    char prepared[1000]; // Enough space for the prepared text
    
    // Generate the key grid
    generate_grid(keyword, grid);
    
    // Prepare the plaintext
    prepare_text(plaintext, prepared);
    
    int len = strlen(prepared);
    int i, row1, col1, row2, col2;
    
    // Process digraphs (pairs of letters)
    for (i = 0; i < len; i += 2) {
        find_position(grid, prepared[i], &row1, &col1);
        find_position(grid, prepared[i+1], &row2, &col2);
        
        // Same row: take letter to the right (wrapping around)
        if (row1 == row2) {
            result[i] = grid[row1][(col1 + 1) % GRID_SIZE];
            result[i+1] = grid[row2][(col2 + 1) % GRID_SIZE];
        }
        // Same column: take letter below (wrapping around)
        else if (col1 == col2) {
            result[i] = grid[(row1 + 1) % GRID_SIZE][col1];
            result[i+1] = grid[(row2 + 1) % GRID_SIZE][col2];
        }
        // Rectangle: take letter in same row but at the column of the other letter
        else {
            result[i] = grid[row1][col2];
            result[i+1] = grid[row2][col1];
        }
    }
    
    result[len] = '\0';
}

/**
 * Decrypts ciphertext using the Playfair cipher with a given keyword.
 * @param ciphertext The text to decrypt
 * @param keyword The keyword for the cipher
 * @param result The buffer to store the decrypted text
 */
void playfair_decrypt(const char *ciphertext, const char *keyword, char *result) {
    char grid[GRID_SIZE][GRID_SIZE];
    int len = strlen(ciphertext);
    int i, row1, col1, row2, col2;
    
    // Generate the key grid
    generate_grid(keyword, grid);
    
    // Process digraphs (pairs of letters)
    for (i = 0; i < len; i += 2) {
        find_position(grid, ciphertext[i], &row1, &col1);
        find_position(grid, ciphertext[i+1], &row2, &col2);
        
        // Same row: take letter to the left (wrapping around)
        if (row1 == row2) {
            result[i] = grid[row1][(col1 + GRID_SIZE - 1) % GRID_SIZE];
            result[i+1] = grid[row2][(col2 + GRID_SIZE - 1) % GRID_SIZE];
        }
        // Same column: take letter above (wrapping around)
        else if (col1 == col2) {
            result[i] = grid[(row1 + GRID_SIZE - 1) % GRID_SIZE][col1];
            result[i+1] = grid[(row2 + GRID_SIZE - 1) % GRID_SIZE][col2];
        }
        // Rectangle: take letter in same row but at the column of the other letter
        else {
            result[i] = grid[row1][col2];
            result[i+1] = grid[row2][col1];
        }
    }
    
    result[len] = '\0';
    
    // Note: This doesn't remove padding 'X' characters as it's hard to determine
    // which ones were added during encryption
}

// Test function
void test_playfair_cipher() {
    char plaintext[] = "HELLOWORLD";
    char keyword[] = "MONARCHY";
    char encrypted[100];
    char decrypted[100];
    
    playfair_encrypt(plaintext, keyword, encrypted);
    playfair_decrypt(encrypted, keyword, decrypted);
    
    printf("Original: %s\n", plaintext);
    printf("Keyword: %s\n", keyword);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    printf("Note: Decrypted text may contain added 'X' characters from encryption.\n");
}