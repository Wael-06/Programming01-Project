#include "Report.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define MAX_TRANSACTIONS 5
#include "Color.h"

typedef struct {
    char date[20];
    char type[20];
    float amount;
    float balance_after;
    char desc[100];
} Transaction;

void add_transaction(const char *account_number, const char *type, float amount, float balance_after, const char *desc)
{
    char filename[50];
    sprintf(filename, "%s.txt", account_number);

    Transaction transactions[MAX_TRANSACTIONS + 1]; // +1 for the new one
    int count = 0;

    // Read existing transactions if file exists
    FILE *file = fopen(filename, "r");
    if (file) {
        while (count < MAX_TRANSACTIONS && fscanf(file, " %19[^|]| %19[^|]| %f | %f | %99[^\n]",
                                                  transactions[count].date,
                                                  transactions[count].type,
                                                  &transactions[count].amount,
                                                  &transactions[count].balance_after,
                                                  transactions[count].desc) == 5) {
            count++;
        }
        fclose(file);
    }
    // Get today's date
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        printf(RED "Error getting current time\n" RESET);
        return;
    }
    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        printf(RED "Error converting time\n" RESET);
        return;
    }
    char today[20];
    if (strftime(today, sizeof(today), "%Y-%m-%d", tm_info) == 0) {
        printf(RED "Error formatting date\n" RESET);
        return;
    }

    // Shift transactions down if already 5
    if (count == MAX_TRANSACTIONS) {
        for (int i = MAX_TRANSACTIONS - 1; i > 0; i--) {
            transactions[i] = transactions[i - 1];
        }
        count = MAX_TRANSACTIONS; // keep it 5
    } else {
        for (int i = count; i > 0; i--) {
            transactions[i] = transactions[i - 1];
        }
        count++;
    }
    // Insert the new transaction at the top
    strncpy(transactions[0].date, today, sizeof(transactions[0].date)-1);
    strncpy(transactions[0].type, type, sizeof(transactions[0].type)-1);
    transactions[0].amount = amount;
    transactions[0].balance_after = balance_after;
    strncpy(transactions[0].desc, desc, sizeof(transactions[0].desc)-1);
    transactions[0].date[sizeof(transactions[0].date)-1] = '\0';
    transactions[0].type[sizeof(transactions[0].type)-1] = '\0';
    transactions[0].desc[sizeof(transactions[0].desc)-1] = '\0';
    // Write back all transactions to the file (overwrite)
    file = fopen(filename, "w");
    if (!file) {
        printf(RED "Error opening file %s for writing.\n" RESET, filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s|%s|%.2f|%.2f|%s\n",
                transactions[i].date,
                transactions[i].type,
                transactions[i].amount,
                transactions[i].balance_after,
                transactions[i].desc);
    }

    fclose(file);
}


void print_report(const Account * accounts,const int account_count)
{
    char account_number[11];
    int account_index;
        // Display header
    printf(CYAN "\n===================================================\n" RESET);
    printf(CYAN "               Accounts Reports\n" RESET);
    printf(CYAN "===================================================\n\n" RESET);

    // Get account number
    if(!Scan_acc_num(account_number)){
        printf(RED "Account Report failed\n" RESET);
        return;
    }
    // Find the account
    account_index = find_account_by_number(accounts,account_count,account_number);
    if (account_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, account_number);
        return;
    }
    char filename[50];
    sprintf(filename, "%s.txt", account_number);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf(YELLOW "No report found for account %s\n" RESET, account_number);
        return;
    }

    printf(CYAN "\n================ ACCOUNT REPORT =================\n" RESET);
    printf("Account Number: %s\n\n", account_number);
    printf(CYAN "%-12s  %-12s  %-10s  %-15s  %-20s\n" RESET,
           "Date", "Type", "Amount", "Balance After", "Description");
    printf(CYAN "---------------------------------------------------------------\n" RESET);

    char date[20], type[20], desc[100];
    float amount, balance_after;
    while (fscanf(file," %19[^|]| %19[^|]| %f | %f | %99[^\n]",
                  date, type, &amount, &balance_after, desc) == 5)
    {
        printf("%-12s  %-12s  %-10.2f  %-15.2f  %-20s\n",
               date, type, amount, balance_after, desc);
    }

    fclose(file);
    printf(CYAN "===============================================================\n\n" RESET);
}
