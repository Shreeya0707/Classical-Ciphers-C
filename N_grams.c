#include <stdio.h>
#include <string.h>

void findNGrams(char str[], int n) {
    int len = strlen(str);
    for (int i = 0; i <= len - n; i++) {
        printf("N-Gram: ");
        for (int j = 0; j < n; j++) {
            printf("%c", str[i + j]);
        }
        printf("\n");
    }
}

int main() {
    char text[100];
    int n;

    printf("Enter the text: ");
    scanf("%s", text);
    
    printf("Enter N for N-gram: ");
    scanf("%d", &n);

    findNGrams(text, n);
    return 0;
}
