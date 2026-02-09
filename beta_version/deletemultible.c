#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "delete_multible.h"

// Parse date string (format: MM-YYYY)
int parse_date_string(const char *date_str, Date *date)
{
    return sscanf(date_str, "%d-%d", &date->month, &date->year);
}

// Check if account is inactive for more than 90 days
int is_inactive_for_90_days(const Date *opening_date)
{
    time_t now = time(NULL);
    struct tm *current = localtime(&now);

    // Calculate days difference (simplified)
    int months_diff = ((current->tm_year + 1900) - opening_date->year) * 12;
    months_diff += (current->tm_mon + 1) - opening_date->month;

    // Approximate: 90 days ≈ 3 months
    return months_diff >= 3;
}

// Delete accounts by date
void delete_by_date()
{
    char date_str[20];
    Date target_date;
    int deleted_count = 0;

    printf("\n=== DELETE BY DATE ===\n");
    printf("Enter date (format: MM-YYYY): ");
    fgets(date_str, sizeof(date_str), stdin);
    date_str[strcspn(date_str, "\n")] = '\0';

    if (!parse_date_string(date_str, &target_date))
    {
        printf("Invalid date format! Use MM-YYYY\n");
        return;
    }

    // Open files
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("No accounts file found!\n");
        return;
    }

    FILE *temp = fopen(TEMP_FILE, "w");
    if (temp == NULL)
    {
        printf("Cannot create temp file!\n");
        fclose(file);
        return;
    }

    char line[256];
    printf("\nSearching for accounts created on: %02d-%04d\n",
           target_date.month, target_date.year);

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            fprintf(temp, "\n");
            continue;
        }

        // Parse account data using strtok
        char line_copy[256];
        strcpy(line_copy, line);

        char *token = strtok(line_copy, ",");
        if (token == NULL)
            continue;

        // Skip to date field (6th field: after account, name, email, balance, mobile)
        char acc_num[12], name[50], email[50], mobile[15], status[10];
        float balance;
        Date acc_date;

        strcpy(acc_num, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(name, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(email, token);

        token = strtok(NULL, ",");
        if (token)
            balance = atof(token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(mobile, token);

        token = strtok(NULL, ",");
        if (token)
            parse_date_string(token, &acc_date);

        token = strtok(NULL, ",");
        if (token)
            strcpy(status, token);

        // Check if date matches AND balance is zero
        if (acc_date.month == target_date.month &&
            acc_date.year == target_date.year &&
            balance == 0)
        {

            printf("Found: %s - %s (Balance: $%.2f)\n", acc_num, name, balance);
            printf("Delete this account? (y/n): ");

            char choice[3];
            fgets(choice, sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = '\0';

            if (choice[0] == 'y' || choice[0] == 'Y')
            {
                deleted_count++;
                printf("Marked for deletion.\n");
                // Don't write to temp file (skip it)
                continue;
            }
        }

        // Write account to temp file (keep it)
        fprintf(temp, "%s\n", line);
    }

    fclose(file);
    fclose(temp);

    // Replace file if any accounts were deleted
    if (deleted_count > 0)
    {
        remove(FILENAME);
        rename(TEMP_FILE, FILENAME);
        printf("\n Deleted %d account(s) created on %02d-%04d\n",
               deleted_count, target_date.month, target_date.year);
    }
    else
    {
        remove(TEMP_FILE);
        printf("\nNo accounts found with zero balance on that date.\n");
    }
}

// Delete inactive accounts (inactive for > 90 days with zero balance)
void delete_inactive_accounts()
{
    int deleted_count = 0;

    printf("\n=== DELETE INACTIVE ACCOUNTS ===\n");
    printf("Searching for inactive accounts (> 90 days) with zero balance...\n");

    // Open files
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL)
    {
        printf("No accounts file found!\n");
        return;
    }

    FILE *temp = fopen(TEMP_FILE, "w");
    if (temp == NULL)
    {
        printf("Cannot create temp file!\n");
        fclose(file);
        return;
    }

    char line[256];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            fprintf(temp, "\n");
            continue;
        }

        // Parse account data
        char line_copy[256];
        strcpy(line_copy, line);

        char *token = strtok(line_copy, ",");
        if (token == NULL)
            continue;

        // Extract fields
        char acc_num[12], name[50], email[50], mobile[15], status[10];
        float balance;
        Date acc_date;

        strcpy(acc_num, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(name, token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(email, token);

        token = strtok(NULL, ",");
        if (token)
            balance = atof(token);

        token = strtok(NULL, ",");
        if (token)
            strcpy(mobile, token);

        token = strtok(NULL, ",");
        if (token)
            parse_date_string(token, &acc_date);

        token = strtok(NULL, ",");
        if (token)
            strcpy(status, token);

        // Check conditions: inactive status, > 90 days, zero balance
        char status_lower[10];
        strcpy(status_lower, status);

        // Convert to lowercase manually
        for (int i = 0; status_lower[i]; i++)
        {
            if (status_lower[i] >= 'A' && status_lower[i] <= 'Z')
            {
                status_lower[i] = status_lower[i] + 32;
            }
        }

        int is_inactive = (strcmp(status_lower, "inactive") == 0);
        int old_enough = is_inactive_for_90_days(&acc_date);
        int zero_balance = (balance == 0);

        if (is_inactive && old_enough && zero_balance)
        {
            printf("\nFound: %s - %s\n", acc_num, name);
            printf("Status: %s | Balance: $%.2f | Date: %02d-%04d\n",
                   status, balance, acc_date.month, acc_date.year);
            printf("Delete this account? (y/n): ");

            char choice[3];
            fgets(choice, sizeof(choice), stdin);
            choice[strcspn(choice, "\n")] = '\0';

            if (choice[0] == 'y' || choice[0] == 'Y')
            {
                deleted_count++;
                printf("Marked for deletion.\n");
                // Don't write to temp file
                continue;
            }
        }

        // Write account to temp file
        fprintf(temp, "%s\n", line);
    }

    fclose(file);
    fclose(temp);

    // Replace file if any accounts were deleted
    if (deleted_count > 0)
    {
        remove(FILENAME);
        rename(TEMP_FILE, FILENAME);
        printf("\n Deleted %d inactive account(s) with zero balance\n", deleted_count);
    }
    else
    {
        remove(TEMP_FILE);
        printf("\n No inactive accounts (> 90 days) with zero balance found.\n");
    }
}

// subMenu for multiple delete options
void delete_multiple_menu()
{
    int choice;

    do
    {
        printf("\n=== MULTIPLE DELETE MENU ===\n");
        printf("1. Delete by Date\n");
        printf("2. Delete Inactive Accounts (> 90 days, zero balance)\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");

        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        // Convert to number 
        choice = 0;
        for (int i = 0; input[i] >= '0' && input[i] <= '9'; i++)
        {
            choice = choice * 10 + (input[i] - '0');
        }

        switch (choice)
        {
        case 1:
            delete_by_date();
            break;
        case 2:
            delete_inactive_accounts();
            break;
        case 3:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid choice! Please enter 1-3.\n");
        }
    } while (choice != 3);
}
