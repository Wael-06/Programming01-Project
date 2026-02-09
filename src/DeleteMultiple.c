#include "DeleteMultiple.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Color.h"


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
void delete_by_date(Account* accounts,int* account_count)
{
    char date_str[20];
    Date target_date;
    int deleted_count = 0;
    int flag = 3;

    printf(RED "\n=== DELETE BY DATE ===\n" RESET);
    do{
    printf(YELLOW "Enter date (format: MM-YYYY): " RESET);
    fgets(date_str, sizeof(date_str), stdin);
    date_str[strcspn(date_str, "\n")] = '\0';

    if (parse_date_string(date_str, &target_date)!=2)
        printf(RED "Invalid date format! Use MM-YYYY (attempts left:%d)\n" RESET,--flag);
    else
        break;
    }while(flag);
    if(flag==0)
    {
        printf(RED "Operation Failed\n" RESET);
        return;
    }
        // Check if date matches AND balance is zero
    if(!confirm())
        return;
    for(int i=0;i<*account_count;i++){
        if (accounts[i].date_of_openeing.month == target_date.month &&
            accounts[i].date_of_openeing.year == target_date.year)
        {
            printf(RED "\nFound: %s - %s\nDeleted...\n" RESET, accounts[i].account_number, accounts[i].name);
            for (int j = i; j < *account_count - 1; j++) {
                    accounts[j] = accounts[j + 1];
            }
            (*account_count)--;
            i--;
            deleted_count++;
            }
        }
        if(deleted_count){
            printf(GREEN "Accounts deleted successfully\n" RESET);
            save_to_disk(accounts, *account_count);}
        else
            printf(YELLOW "No accounts created in %s were found\n" RESET,date_str);
}

// Delete inactive accounts (inactive for > 90 days with zero balance)
void delete_inactive_accounts(Account* accounts,int* account_count)
{
    int deleted_count = 0;
    printf(RED "\n=== DELETE INACTIVE ACCOUNTS ===\n" RESET);
    printf(YELLOW "Searching for inactive accounts (> 90 days) with zero balance...\n" RESET);
    if(!confirm())
        return;
    for(int i=0;i<*account_count;i++){
        int is_inactive = (strcmp(accounts[i].status, "inactive") == 0);
        int old_enough = is_inactive_for_90_days(&accounts[i].date_of_openeing);
        int zero_balance = (accounts[i].balance == 0);
        if (is_inactive && old_enough && zero_balance)
        {
            printf(RED "\nFound: %s - %s\nDeleted\n" RESET, accounts[i].account_number, accounts[i].name);
            for (int j = i; j < *account_count - 1; j++)
                    accounts[j] = accounts[j + 1];
            (*account_count)--;
            i--;
            deleted_count++;
            }
        }
        if(deleted_count){
            printf(GREEN "Accounts deleted successfully\n" RESET);
            save_to_disk(accounts, *account_count);}
        else
            printf(YELLOW "No inactive accounts for more than 90 days and with zero balance were found\n" RESET);
}

// subMenu for multiple delete options
void delete_multiple_menu(Account* accounts,int* account_count)
{
    int choice;
    int flag=3;
    printf(RED "\n=== MULTIPLE DELETE MENU ===\n" RESET);
    printf("1. Delete by Date\n");
    printf("2. Delete Inactive Accounts (> 90 days, zero balance)\n");
    printf("3. Back to Main Menu\n");
    do
    {
        printf(YELLOW "Enter your choice: " RESET);
        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        // Convert to number
        choice = 0;
        for (int i = 0; input[i] >= '0' && input[i] <= '9'; i++)
        {
            choice = choice * 10 + (input[i] - '0');
        }

        if(choice==1){
            delete_by_date(accounts,account_count);
            return;}
         else if(choice==2){
            delete_inactive_accounts(accounts,account_count);
            return;}
        else if(choice==3){
            printf(CYAN "Returning to main menu...\n" RESET);
            return;}
        else
            printf(RED "Invalid choice! Please enter 1-3(attempts left:%d)\n" RESET,--flag);
    } while (choice != 3&&flag);
    if(flag==0)
        printf(RED "Operation failed\n" RESET);
}
