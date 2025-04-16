#include <stdio.h>
#include <string.h>
#include <math.h>

void fillGrid(char grid[10][10], char *text, int rows, int cols) {
    int k = 0;
    for (int i = 0; i < rows && text[k]; i++) {
        for (int j = 0; j < cols && text[k]; j++) {
            grid[i][j] = text[k++];
        }
    }
}

void encryptRouteCipher(char *text, char *cipher, int rows, int cols) {
    char grid[10][10];
    fillGrid(grid, text, rows, cols);

    int top = 0, bottom = rows-1, left = 0, right = cols-1, k = 0;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) cipher[k++] = grid[top][i];
        top++;
        for (int i = top; i <= bottom; i++) cipher[k++] = grid[i][right];
        right--;
        for (int i = right; i >= left && top <= bottom; i--) cipher[k++] = grid[bottom][i];
        bottom--;
        for (int i = bottom; i >= top && left <= right; i--) cipher[k++] = grid[i][left];
        left++;
    }
    cipher[k] = '\0';
}

int main() {
    char text[100], cipher[100];
    int rows = 3, cols = 3;

    printf("Enter text (max 9 letters for 3x3): ");
    scanf("%s", text);

    encryptRouteCipher(text, cipher, rows, cols);
    printf("Encrypted (Route Cipher): %s\n", cipher);

    return 0;
}
