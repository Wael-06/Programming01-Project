#include "SortedPrint.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"

void sortedprint(Account *accounts, int accounts_number)
{
    if (accounts_number <= 0) {
        printf(RED "No accounts to display.\n" RESET);
        return;
    }

    char input[20];
    printf(CYAN "Select the sorting way for the accounts.\n" RESET);
    printf("1. Names\n");
    printf("2. Dates\n");
    printf("3. Balance\n");
    printf("4. Status\n");
    printf(YELLOW "Enter your choice (1-4): " RESET);
    clear_input_buffer();
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    // Sort based on choice
    if (strcmp(input, "1") == 0 || strcmp(input, "Names") == 0 || strcmp(input, "names") == 0 || strcmp(input, "1. Names") == 0 || strcmp(input, "1. names") == 0)
    {
        qsort(accounts, accounts_number, sizeof(Account), compare_by_name);
        printf(CYAN "\n=== Accounts Sorted by Name ===\n" RESET);
    }
    else if (strcmp(input, "2") == 0 || strcmp(input, "Dates") == 0 || strcmp(input, "dates") == 0 || strcmp(input, "2. Dates") == 0 || strcmp(input, "2. dates") == 0)
    {
        char order[20];
        int flag=3;
        while(flag--){
        printf(YELLOW "Order: (oldest/newest): " RESET);
        fgets(order, sizeof(order), stdin);
        order[strcspn(order, "\n")] = '\0';

        if (strcmp(order, "oldest")==0 || strcmp(order, "Oldest")==0 || strcmp(order, "O")==0 || strcmp(order, "o")==0) {
            qsort(accounts, accounts_number, sizeof(Account), compare_by_date_oldest);
            printf(CYAN "\n=== Accounts Sorted by Date (Oldest First) ===\n" RESET);
            break;
        } else if(strcmp(order, "newest") == 0 || strcmp(order, "Newest")==0 || strcmp(order, "n")==0 || strcmp(order, "N")==0){
            qsort(accounts, accounts_number, sizeof(Account), compare_by_date_newest);
            printf(CYAN "\n=== Accounts Sorted by Date (Newest First) ===\n" RESET);
            break;
        }
        else
            printf(RED "Invalid input please try again(attempt left:%d)\n" RESET,flag);
        }
    }
    else if (strcmp(input, "3") == 0 || strcmp(input, "Balance") == 0 || strcmp(input, "balance") == 0 || strcmp(input, "3. Balance") == 0 || strcmp(input, "3. balance") == 0)
    {
        char order[20];
        printf(YELLOW "Order: (asc/desc): " RESET);
        fgets(order, sizeof(order), stdin);
        order[strcspn(order, "\n")] = '\0';

        if (strcmp(order, "asc") == 0 || strcmp(order, "Asc") == 0 ) {
            qsort(accounts, accounts_number, sizeof(Account), compare_by_balance_asc);
            printf(CYAN "\n=== Accounts Sorted by Balance (Ascending) ===\n" RESET);
        } else {
            // For descending, we can create a wrapper or just reverse the logic
            qsort(accounts, accounts_number, sizeof(Account), compare_by_balance_asc);
            printf(CYAN "\n=== Accounts Sorted by Balance (Descending) ===\n" RESET);
            // Print in reverse order for descending
            for (int i = accounts_number - 1; i >= 0; i--) {
                print_account_formatted(&accounts[i]);
            }
            return;
        }
    }
    else if (strcmp(input, "4") == 0 || strcmp(input, "Status") == 0 || strcmp(input, "status") == 0 || strcmp(input, "4. Status") == 0 || strcmp(input, "4. status") == 0)
    {
        qsort(accounts, accounts_number, sizeof(Account), compare_by_status_active_first);
        printf(CYAN "\n=== Accounts Sorted by Status (Active First) ===\n" RESET);
    }
    else
    {
        printf(RED "Invalid choice!\n" RESET);
        return;
    }
    // Print all sorted accounts
        print_accounts_formatted(accounts,accounts_number);
}
