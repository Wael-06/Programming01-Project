//EYAD WORK
#include "Modify.h"
#include "helper1.h"
#include "helper2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// MODIFY FUNCTION THE MAIN ONE
void modify_account(Account * accounts,const int account_count) {
    char account_number[13];
    int account_index;
    char input[100];
    int changes_made = 0;

    // Display header
    printf("\n===================================================\n");
    printf("               MODIFY ACCOUNT DETAILS\n");
    printf("===================================================\n\n");

    // Get account number
    if(!Scan_acc_num(account_number)){
        printf("Account Modification failed\n");
        return;
    }
    // Find the account
    account_index = find_account_by_number(accounts,account_count,account_number);
    if (account_index == -1) {
        printf("\nError: Account %s not found!\n", account_number);
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
    if (changes_made)
        printf("\nModifications completed successfully!\n");
    else
        printf("\nNo changes were made to the account.\n");
}
