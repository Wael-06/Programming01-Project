//EYAD WORK
#include "Modify.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Color.h"

// MODIFY FUNCTION THE MAIN ONE
void modify_account(Account * accounts,const int account_count) {
    char account_number[11];
    int account_index;
    char input[100];
    int changes_made = 0;

    // Display header
    printf(CYAN "\n===================================================\n" RESET);
    printf(CYAN "               MODIFY ACCOUNT DETAILS\n" RESET);
    printf(CYAN "===================================================\n\n" RESET);

    // Get account number
    if(!Scan_acc_num(account_number)){
        printf(RED "Account Modification failed\n" RESET);
        return;
    }
    // Find the account
    account_index = find_account_by_number(accounts,account_count,account_number);
    if (account_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, account_number);
        return;
    }

    // Display current account information
    printf(CYAN "\n---------------------------------------------------\n" RESET);
    printf(CYAN "CURRENT ACCOUNT #%s\n" RESET, accounts[account_index].account_number);
    printf(CYAN "---------------------------------------------------\n" RESET);
    printf("1. Name    : %s\n", accounts[account_index].name);
    printf("2. Mobile  : %s\n", accounts[account_index].mobile);
    printf("3. Email   : %s\n", accounts[account_index].email);
    printf(CYAN "---------------------------------------------------\n" RESET);
    // Field 1: Modify Name
    printf(YELLOW "\n--- MODIFY NAME ---\n" RESET);
    printf("Current: %s\n", accounts[account_index].name);
    printf(YELLOW "New name (press Enter to keep current): " RESET);
    clear_input_buffer();
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;  // Remove newline
        trim_string(input);

        if (strlen(input) > 0) {
            if (validate_name(input)) {
                capitalize_words(input);
                strcpy(accounts[account_index].name, input);
                printf(GREEN "Name updated to: %s\n" RESET, accounts[account_index].name);
                changes_made = 1;
            }
        } else {
            printf("Name unchanged\n");
        }

    }

    // Field 2: Modify Mobile
    printf(YELLOW "\n--- MODIFY MOBILE ---\n" RESET);
    printf("Current: %s\n", accounts[account_index].mobile);
    printf(YELLOW "Format: 11 digits starting with 01 (e.g., 01009700000)\n" RESET);
    printf(YELLOW "New mobile (press Enter to keep current): " RESET);

    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        trim_string(input);

        if (strlen(input) > 0) {
            if (validate_mobile(input)) {
                strcpy(accounts[account_index].mobile, input);
                printf(GREEN "Mobile updated to: %s\n" RESET, accounts[account_index].mobile);
                changes_made = 1;
            }
        } else {
            printf("Mobile unchanged\n");
        }
    }

    // Field 3: Modify Email
    printf(YELLOW "\n--- MODIFY EMAIL ---\n" RESET);
    printf("Current: %s\n", accounts[account_index].email);
    printf(YELLOW "Examples: name@gmail.com, name@outlook.com\n" RESET);
    printf(YELLOW "New email (press Enter to keep current): " RESET);

    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = 0;
        trim_string(input);

        if (strlen(input) > 0) {
            if (validate_email(input)) {
                strcpy(accounts[account_index].email, input);
                printf(GREEN "Email updated to: %s\n" RESET, accounts[account_index].email);
                changes_made = 1;
            }
        } else {
            printf("Email unchanged\n");
        }
    }

    // Display updated information after ths modify
    printf(CYAN "\n---------------------------------------------------\n" RESET);
    printf(CYAN "UPDATED ACCOUNT #%s\n" RESET, accounts[account_index].account_number);
    printf(CYAN "---------------------------------------------------\n" RESET);
    printf("Name    : %s\n", accounts[account_index].name);
    printf("Mobile  : %s\n", accounts[account_index].mobile);
    printf("Email   : %s\n", accounts[account_index].email);
    printf(CYAN "---------------------------------------------------\n" RESET);

    // Prompt to save changes if any modifications were made
    if (changes_made){
        printf(GREEN "\nModifications completed successfully!\n" RESET);
        save_to_disk(accounts,account_count);
        }
    else
        printf(YELLOW "\nNo changes were made to the account.\n" RESET);
}
