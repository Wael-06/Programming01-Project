//EYAD WORK  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bank_system.h"
#include "modify.h"

// External variables from main
extern Account accounts[MAX_ACCOUNTS];
extern int account_count;

// Function declarations
extern void quick_save_prompt();
extern void clear_input_buffer();

// Find account by number, returns index or -1 if not found
int find_account_by_number(const char *account_number) {
    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].account_number, account_number) == 0) {
            return i;
        }
    }
    return -1;
}

// Validate email format
//STRCHR SEARCHES FOR CHARACTER IN EMAIL 
int validate_email(const char *email) {
    if (strchr(email, '@') == NULL) {
        printf("Error: Email must contain @ symbol\n");
        return 0;
    }
    
    if (strchr(email, '.') == NULL) {
        printf("Error: Email must contain . (dot)\n");
        return 0;
    }
    
    if (strchr(email, ' ') != NULL) {
        printf("Error: Email cannot contain spaces\n");
        return 0;
    }
    
    if (strlen(email) < 5 || strlen(email) > 49) {
        printf("Error: Email must be 5-49 characters\n");
        return 0;
    }
    
    return 1;
}

// Validate mobile number format ( 11 digits starting with 01)
int validate_mobile(const char *mobile) {
    if (strlen(mobile) != 11) {
        printf("Error: Mobile must be 11 digits (e.g., 01000000000)\n");
        return 0;
    }
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(mobile[i])) {
            printf("Error: Mobile must be all digits\n");
            return 0;
        }
    }
    
    if (mobile[0] != '0' || mobile[1] != '1') {
        printf("Error: Mobile must start with 01 (Egyptian format)\n");
        return 0;
    }
    
    return 1;
}

// Validate name that thers name written there is letter not longg
int validate_name(const char *name) {
    if (strlen(name) == 0) {
        printf("Error: Name cannot be empty\n");
        return 0;
    }
    
    if (strlen(name) > 49) {
        printf("Error: Name too long (max 49 characters)\n");
        return 0;
    }
    
    // Check for at least one letter
    int has_letter = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (isalpha(name[i])) {
            has_letter = 1;
            break;
        }
    }
    
    if (!has_letter) {
        printf("Error: Name must contain at least one letter\n");
        return 0;
    }
    
    return 1;
}

// Trim leading and trailing spaces from a string
//see photo i will send on whats app 
void trim_string(char *str) {
    char *start = str;
    while (*start && isspace(*start)) start++;
    
    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) {
        *end = '\0';
        end--;
    }
    
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

// MODIFY FUNCTION THE MAIN ONE
void modify_account() {
    char account_number[12];
    int account_index;
    char input[100];
    int changes_made = 0;
    
    // Display header
    printf("\n===================================================\n");
    printf("               MODIFY ACCOUNT DETAILS\n");
    printf("===================================================\n\n");
    
    // Get account number
    printf("Enter Account Number (10 digits): ");
    if (scanf("%11s", account_number) != 1) {
        printf("Error reading account number\n");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    
    // Validate account number format
    if (strlen(account_number) != 10) {
        printf("\nError: Account number must be exactly 10 digits\n");
        return;
    }
    
    for (int i = 0; i < 10; i++) {
        if (!isdigit(account_number[i])) {
            printf("Error: Account number must be all digits\n");
            return;
        }
    }
    
    // Find the account
    account_index = find_account_by_number(account_number);
    
    if (account_index == -1) {
        printf("\nError: Account %s not found!\n", account_number);
        printf("Available accounts: 9700000000 to 9700000009\n");
        return;
    }
    
    // Display current account information
    printf("\n---------------------------------------------------\n");
    printf("CURRENT ACCOUNT #%s\n", accounts[account_index].account_number);
    printf("---------------------------------------------------\n");
    printf("1. Name    : %s\n", accounts[account_index].name);
    printf("2. Mobile  : %s\n", accounts[account_index].mobile);
    printf("3. Email   : %s\n", accounts[account_index].email);
    printf("---------------------------------------------------\n");
    
    // Field 1: Modify Name
    printf("\n--- MODIFY NAME ---\n");
    printf("Current: %s\n", accounts[account_index].name);
    printf("New name (press Enter to keep current): ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;  // Remove newline
        trim_string(input);
        
        if (strlen(input) > 0) {
            if (validate_name(input)) {
                strcpy(accounts[account_index].name, input);
                printf("Name updated to: %s\n", accounts[account_index].name);
                changes_made = 1;
            }
        } else {
            printf("Name unchanged\n");
        }
    }
    
    // Field 2: Modify Mobile
    printf("\n--- MODIFY MOBILE ---\n");
    printf("Current: %s\n", accounts[account_index].mobile);
    printf("Format: 11 digits starting with 01 (e.g., 01009700000)\n");
    printf("New mobile (press Enter to keep current): ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        trim_string(input);
        
        if (strlen(input) > 0) {
            if (validate_mobile(input)) {
                strcpy(accounts[account_index].mobile, input);
                printf("Mobile updated to: %s\n", accounts[account_index].mobile);
                changes_made = 1;
            }
        } else {
            printf("Mobile unchanged\n");
        }
    }
    
    // Field 3: Modify Email
    printf("\n--- MODIFY EMAIL ---\n");
    printf("Current: %s\n", accounts[account_index].email);
    printf("Examples: name@gmail.com, name@outlook.com\n");
    printf("New email (press Enter to keep current): ");
    
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        trim_string(input);
        
        if (strlen(input) > 0) {
            if (validate_email(input)) {
                strcpy(accounts[account_index].email, input);
                printf("Email updated to: %s\n", accounts[account_index].email);
                changes_made = 1;
            }
        } else {
            printf("Email unchanged\n");
        }
    }
    
    // Display updated information after ths modify
    printf("\n---------------------------------------------------\n");
    printf("UPDATED ACCOUNT #%s\n", accounts[account_index].account_number);
    printf("---------------------------------------------------\n");
    printf("Name    : %s\n", accounts[account_index].name);
    printf("Mobile  : %s\n", accounts[account_index].mobile);
    printf("Email   : %s\n", accounts[account_index].email);
    printf("---------------------------------------------------\n");
    
    // Prompt to save changes if any modifications were made
    if (changes_made) {
        printf("\nModifications completed successfully!\n");
        quick_save_prompt();  // ASK USER WANT TO SAVE the save function i made
    } else {
        printf("\nNo changes were made to the account.\n");
    }
}
