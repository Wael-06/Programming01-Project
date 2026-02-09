#include "Load.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_ACCOUNTS 1000
#include "Color.h"

Account* load_accounts()//byeyad
{
    FILE *file = fopen("accounts.txt", "r");

    if (file == NULL) {
        printf(RED " Error: Could not open file 'accounts.txt'.\n" RESET);
        printf(YELLOW "Creating new empty file\n" RESET);

        // Create empty file if it doesn't exist
        file = fopen("accounts.txt", "w");
        if (file) {
            fclose(file);
            printf(GREEN "Created new empty accounts file.\n" RESET);
        } else {
            printf(RED " Failed to create file.\n" RESET);
        }
        return NULL;
    }

    char line[256];
    int account_count = 0;
    int line_number = 0;
    Account* accounts = (Account*)malloc(1000* sizeof(Account));
    printf(CYAN "Loading accounts from 'accounts.txt'\n" RESET);
    while (fgets(line, sizeof(line), file) && account_count < MAX_ACCOUNTS) {
        line_number++;

        // Remove newline character
        line[strcspn(line, "\r\n")] = '\0';

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Parse the line: account_number,name,email,balance,mobile,date,status
        char acc_num[11], name[50], email[50], mobile[15], date_str[20], status[10];
        float balance;

        // Use sscanf to parse comma-separated values to seperate commas y3ny
        int parsed = sscanf(line, "%10[^,],%49[^,],%49[^,],%f,%14[^,],%19[^,],%9s",
                           acc_num, name, email, &balance, mobile, date_str, status);

        if (parsed != 7) {
            printf(YELLOW "Warning: Line %d has incorrect format (expected 7 fields, got %d)\n" RESET,
                   line_number, parsed);
            printf(YELLOW "   Line: %s\n" RESET, line);
            continue;
        }

        // VALIDATION 1: Check account number is 10 digits
        if (strlen(acc_num) != 10) {
            printf(YELLOW " Warning: Account number '%s' must be 10 digits (line %d)\n" RESET,
                   acc_num, line_number);
            continue;
        }

        // VALIDATION 2: Check all characters are digits
        int valid_acc = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(acc_num[i])) {
                valid_acc = 0;
                break;
            }
        }
        if (!valid_acc) {
            printf(YELLOW "Warning: Account number '%s' contains non-digits (line %d)\n" RESET,
                   acc_num, line_number);
            continue;
        }

        // VALIDATION 3: Check for duplicates
        int duplicate = 0;
        for (int i = 0; i < account_count; i++) {
            if (strcmp(accounts[i].account_number, acc_num) == 0) {
                printf(YELLOW "Warning: Duplicate account number '%s' (line %d)\n" RESET,
                       acc_num, line_number);
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        // VALIDATION 4: Check email has @ and .
        if (!strchr(email, '@') || !strchr(email, '.')) {
            printf(YELLOW "Warning: Invalid email format '%s' (line %d)\n" RESET,
                   email, line_number);
            continue;
        }

        // VALIDATION 5: Check mobile format (Egyptian: 01) as tyhe one in txt
        if (strlen(mobile) != 11 || mobile[0] != '0' || mobile[1] != '1') {
            printf(YELLOW "Warning: Invalid mobile format '%s' (line %d)\n" RESET,
                   mobile, line_number);
            continue;
        }

        // VALIDATION 6: Check balance is non-negative
        if (balance < 0) {
            printf(YELLOW "Warning: Negative balance %.2f (line %d)\n" RESET,
                   balance, line_number);
            continue;
        }

        // VALIDATION 7: Parse date (MM-YYYY)
        int month, year;
        if (sscanf(date_str, "%d-%d", &month, &year) != 2) {
            printf(YELLOW "Warning: Invalid date format '%s' (line %d)\n" RESET,
                   date_str, line_number);
            continue;
        }

        if (month < 1 || month > 12) {
            printf(YELLOW "Warning: Invalid month %d in date (line %d)\n" RESET,
                   month, line_number);
            continue;
        }

        // VALIDATION 8: Check status
        if (strcmp(status, "active") != 0 && strcmp(status, "inactive") != 0) {
            printf(YELLOW "Warning: Invalid status '%s' (line %d). Using 'active'\n" RESET,
                   status, line_number);
            strcpy(status, "active");
        }
        capitalize_words(name);

        // ALL VALIDATIONS PASSED! Store the account isa
        strcpy(accounts[account_count].account_number, acc_num);
        strcpy(accounts[account_count].name, name);
        strcpy(accounts[account_count].email, email);
        accounts[account_count].balance = balance;
        strcpy(accounts[account_count].mobile, mobile);
        accounts[account_count].date_of_openeing.month = month;
        accounts[account_count].date_of_openeing.year = year;
        strcpy(accounts[account_count].status, status);

        account_count++;
    }

    fclose(file);
    //final check is there account to be loaded wla NO??
    if (account_count == 0) {
        printf(YELLOW "No valid accounts loaded from file.\n" RESET);
    } else {
        printf(GREEN "Successfully loaded %d account(s).\n" RESET, account_count);
    }
    return accounts;
}
