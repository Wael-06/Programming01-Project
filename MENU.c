#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Clear input buffer to make ez
void clear_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Simple login
int login() {
    char username[50];
    char password[50];

    printf("\n=== LOGIN ===\n");

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);
    clear_input();

    // im just comparing each username and password they should be equal
    if ((strcmp(username, "aaa") == 0 && strcmp(password, "123a") == 0) ||
        (strcmp(username, "bbb") == 0 && strcmp(password, "123b") == 0) ||
        (strcmp(username, "ccc") == 0 && strcmp(password, "123c") == 0) ||
        (strcmp(username, "ddd") == 0 && strcmp(password, "123d") == 0) ||
        (strcmp(username, "eee") == 0 && strcmp(password, "123e") == 0)) {
        printf("\nLogin successful! Welcome %s.\n", username);
        return 1;
    } else {
        printf("\nLogin failed!\n");
        return 0;
    }
}

// displaying the login menu (take care different form the MAIN ONE)
void show_login_menu() {
    printf("\n===========================\n");
    printf("  BANK MANAGEMENT SYSTEM\n");
    printf("===========================\n");
    printf("1. LOGIN\n");
    printf("2. QUIT\n");
    printf("\nEnter choice (1-2): ");
}

// Display main menu
void show_main_menu() {
    printf("\n===========================\n");
    printf("      MAIN MENU\n");
    printf("===========================\n");
    printf(" 1. ADD Account\n");
    printf(" 2. DELETE Account\n");
    printf(" 3. MODIFY Account\n");
    printf(" 4. SEARCH Account\n");
    printf(" 5. ADVANCED SEARCH\n");
    printf(" 6. CHANGE STATUS\n");
    printf(" 7. WITHDRAW\n");
    printf(" 8. DEPOSIT\n");
    printf(" 9. TRANSFER\n");
    printf("10. REPORT\n");
    printf("11. PRINT (Sort)\n");
    printf("12. SAVE\n");
    printf("13. LOAD\n");
    printf("14. QUIT\n");
    printf("\n===========================\n");
    printf("Enter choice (1-14): ");
}

// Main function
int main() {
    printf("++++++++++++++++++++++++++\n");
    printf(" WELCOME TO BANK SYSTEM\n");
    printf("+++++++++++++++++++++++++++\n");

    int logged_in = 0;
    int running = 1;

    while (running) {
        if (!logged_in) {
            show_login_menu();

            int choice;
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input!\n");
                clear_input();
                continue;
            }
            clear_input();

            if (choice == 1) {
                logged_in = login();
            } else if (choice == 2) {
                printf("\nGoodbye!\n");
                running = 0;
            } else {
                printf("Invalid choice! Enter 1 or 2.\n");
            }
        } else {
            show_main_menu();

            int choice;
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input!\n");
                clear_input();
                continue;
            }
            clear_input();

            switch (choice) {
                case 1: printf("\n--- ADD ACCOUNT ---\n(To be implemented)\n"); break;
                case 2: printf("\n--- DELETE ACCOUNT ---\n(To be implemented)\n"); break;
                case 3: printf("\n--- MODIFY ACCOUNT ---\n(To be implemented)\n"); break;
                case 4: printf("\n--- SEARCH ACCOUNT ---\n(To be implemented)\n"); break;
                case 5: printf("\n--- ADVANCED SEARCH ---\n(To be implemented)\n"); break;
                case 6: printf("\n--- CHANGE STATUS ---\n(To be implemented)\n"); break;
                case 7: printf("\n--- WITHDRAW ---\n(To be implemented)\n"); break;
                case 8: printf("\n--- DEPOSIT ---\n(To be implemented)\n"); break;
                case 9: printf("\n--- TRANSFER ---\n(To be implemented)\n"); break;
                case 10: printf("\n--- REPORT ---\n(To be implemented)\n"); break;
                case 11: printf("\n--- PRINT/SORT ---\n(To be implemented)\n"); break;
                case 12: printf("\n--- SAVE ---\n(To be implemented)\n"); break;
                case 13: printf("\n--- LOAD ---\n(To be implemented)\n"); break;
                case 14:
                    printf("\nAre you sure? (y/n): ");
                    char confirm;
                    scanf("%c", &confirm);
                    clear_input();
                    if (confirm == 'y' || confirm == 'Y') {
                        printf("Goodbye!\n");
                        running = 0;
                    } else {
                        printf("Returning to menu...\n");
                    }
                    break;
                default: printf("Invalid choice! Enter 1-14.\n");
            }

            if (choice != 14 || running) {
                printf("\nPress Enter to continue...");
                clear_input();
            }
        }
    }

    return 0;
}
