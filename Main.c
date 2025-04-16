#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function declarations for all the test functions
void test_caesar_cipher();
void test_atbash_cipher();
void test_vigenere_cipher();
void test_autokey_cipher();
void test_affine_cipher();
void test_gronsfeld_cipher();
void test_beaufort_cipher();
void test_running_key_cipher();
void test_hill_cipher();
void test_playfair_cipher();

int main() {
    int choice;
    
    do {
        printf("\nClassical Cipher Implementations in C\n");
        printf("-----------------------------------\n");
        printf("1. Caesar Cipher\n");
        printf("2. Atbash Cipher\n");
        printf("3. Vigenere Cipher\n");
        printf("4. Autokey Cipher\n");
        printf("5. Affine Cipher\n");
        printf("6. Gronsfeld Cipher\n");
        printf("7. Beaufort Cipher\n");
        printf("8. Running Key (Autoclave) Cipher\n");
        printf("9. Hill Cipher\n");
        printf("10. Playfair Cipher\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                test_caesar_cipher();
                break;
            case 2:
                test_atbash_cipher();
                break;
            case 3:
                test_vigenere_cipher();
                break;
            case 4:
                test_autokey_cipher();
                break;
            case 5:
                test_affine_cipher();
                break;
            case 6:
                test_gronsfeld_cipher();
                break;
            case 7:
                test_beaufort_cipher();
                break;
            case 8:
                test_running_key_cipher();
                break;
            case 9:
                test_hill_cipher();
                break;
            case 10:
                test_playfair_cipher();
                break;
            case 0:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        
        if (choice > 0 && choice <= 10) {
            printf("\nPress Enter to continue...");
            getchar(); // Clear the newline character from previous input
            getchar(); // Wait for user to press Enter
        }
        
    } while (choice != 0);
    
    return 0;
}