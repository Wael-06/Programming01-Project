#include "helper1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAX_ACCOUNTS 1000
#include "Color.h"

void clear_input_buffer()//byeyad
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int compare_by_name(const void *a, const void *b)//bymoataz
{
    const Account *acc1 = (const Account *)a;
    const Account *acc2 = (const Account *)b;

    //+ve if acc1 name comes after acc2 name in dictionary
    //-ve if opposite
    return strcmp(acc1->name, acc2->name);
}

int compare_by_date_oldest(const void *a, const void *b)//bymoataz
{
    const Account *acc1 = (const Account *)a;
    const Account *acc2 = (const Account *)b;
    if (acc1->date_of_openeing.year != acc2->date_of_openeing.year) {
        return acc1->date_of_openeing.year - acc2->date_of_openeing.year;
    }
    return acc1->date_of_openeing.month - acc2->date_of_openeing.month;
}

int compare_by_date_newest(const void *a, const void *b)//bymoataz
{
    const Account *acc1 = (const Account *)a;
    const Account *acc2 = (const Account *)b;
    if (acc1->date_of_openeing.year != acc2->date_of_openeing.year) {
        return acc2->date_of_openeing.year - acc1->date_of_openeing.year;
        //if not in the same year will see the differnce
        //if acc2 older than acc1 -ve
        //else acc2 smaller than acc1 +ve
    }
    return acc2->date_of_openeing.month - acc1->date_of_openeing.month;
}

int compare_by_balance_asc(const void *a, const void *b)//bymoataz
{
    const Account *acc1 = (const Account *)a;
    const Account *acc2 = (const Account *)b;
    if (acc1->balance < acc2->balance) return -1;
    if (acc1->balance > acc2->balance) return 1;
    return 0;
}

int compare_by_status_active_first(const void *a, const void *b) //bymoataz
{
    const Account *acc1 = (const Account *)a;
    const Account *acc2 = (const Account *)b;

    // Compare strings: "active" vs "inactive"
    // strcmp returns: negative if str1 < str2, positive if str1 > str2, 0 if equal
    // "active" < "inactive" alphabetically
    // We want active FIRST, so we reverse the comparison

    return -strcmp(acc2->status, acc1->status);
    // If acc2 is "active" and acc1 is "inactive": negative (acc2 comes first)
    // If acc2 is "inactive" and acc1 is "active": positive (acc1 comes first)
}

int count_valid_accounts()//byeyad
{
    int account_count = 0;
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
        return 0;
    }

    char line[256];
    int line_number = 0;
    Account accounts[MAX_ACCOUNTS];
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

        if (parsed != 7)
            continue;

        // VALIDATION 1: Check account number is 10 digits
        if (strlen(acc_num) != 10)
            continue;

        // VALIDATION 2: Check all characters are digits
        int valid_acc = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(acc_num[i])) {
                valid_acc = 0;
                break;
            }
        }
        if (!valid_acc)
            continue;

        // VALIDATION 3: Check for duplicates
        int duplicate = 0;
        for (int i = 0; i < account_count; i++) {
            if (strcmp(accounts[i].account_number, acc_num) == 0) {
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;

        // VALIDATION 4: Check email has @ and .
        if (!strchr(email, '@') || !strchr(email, '.'))
            continue;

        // VALIDATION 5: Check mobile format (Egyptian: 01) as tyhe one in txt
        if (strlen(mobile) != 11 || mobile[0] != '0' || mobile[1] != '1')
            continue;

        // VALIDATION 6: Check balance is non-negative
        if (balance < 0)
            continue;

        // VALIDATION 7: Parse date (MM-YYYY)
        int month, year;
        if (sscanf(date_str, "%d-%d", &month, &year) != 2)
            continue;

        if (month < 1 || month > 12)
            continue;

        // VALIDATION 8: Check status
        if (strcmp(status, "active") != 0 && strcmp(status, "inactive") != 0)
            continue;

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

        return account_count;

}

int compare(float a, float b) {
    if (fabsf(a - b) < 0.00001f) return 0;
    if (a > b) return 1;
    return -1;
}

int confirm() {
    char answer;
    do{
    printf(YELLOW "Confirm? (y/n): " RESET);
    scanf(" %c", &answer);
    clear_input_buffer();
    }while(answer != 'y' && answer != 'Y'&& answer !='n' && answer !='N');
    return (answer == 'y' || answer == 'Y');
}
