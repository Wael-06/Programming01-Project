#include "helper2.h"
#include "helper1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Color.h"

void print_account_formatted(const Account *account)//bymoataz
{
    const char *months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};

    printf(CYAN "Account Number: %s\n" RESET, account->account_number);
    printf("Name: %s\n", account->name);
    printf("E-mail: %s\n", account->email);
    printf(GREEN "Balance: %.0f $\n" RESET, account->balance);
    printf("Mobile: %s\n", account->mobile);
    printf("Date Opened: %s %d\n",
           months[account->date_of_openeing.month],
           account->date_of_openeing.year);
    printf("Status: %s\n",account->status);
    printf("\n");
}

void print_accounts_formatted(const Account *accounts, int accounts_number)//bymoataz
{
    for (int i = 0; i < accounts_number; i++)
        print_account_formatted(&accounts[i]);
}

void print_account(const Account *account)//bymoataz
{
    printf("%s,%s,%s,%.2f,%s,%02d-%04d,%s\n",
           account->account_number,
           account->name,
           account->email,
           account->balance,
           account->mobile,
           account->date_of_openeing.month,
           account->date_of_openeing.year,
           account->status);
}

void print_accounts(const Account *accounts, int accounts_number)//bymoataz
{
    for (int i = 0; i < accounts_number; i++)
        print_account(&accounts[i]);
}

void capitalize_words(char *str)
{
    int capitalize_next = 1;  // Flag to capitalize next letter

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ')// Space - next letter should be capitalized
            capitalize_next = 1;
        else if (capitalize_next) {// Capitalize this letter if it's lowercase
            if (str[i] >= 'a' && str[i] <= 'z')
                str[i] = str[i] - 32;  // Convert to uppercase using ASCII
            capitalize_next = 0;  // Don't capitalize next letter
        }
        else// Make sure rest of letters are lowercase
            if (str[i] >= 'A' && str[i] <= 'Z')
                str[i] = str[i] + 32;  // Convert to lowercase using ASCII
    }
}

// Validate email format
//STRCHR SEARCHES FOR CHARACTER IN EMAIL
int validate_email(const char *email)
{
    if (strchr(email, '@') == NULL) {
        printf(RED "Error: Email must contain @ symbol\n" RESET);
        return 0;
    }

    if (strchr(email, '.') == NULL) {
        printf(RED "Error: Email must contain . (dot)\n" RESET);
        return 0;
    }

    if (strchr(email, ' ') != NULL) {
        printf(RED "Error: Email cannot contain spaces\n" RESET);
        return 0;
    }

    if (strlen(email) < 5 || strlen(email) > 49) {
        printf(RED "Error: Email must be 5-49 characters\n" RESET);
        return 0;
    }

    return 1;
}

// Find account by number, returns index or -1 if not found
int find_account_by_number(const Account * accounts,const int account_count,const char *account_number)//by eyad
{
    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].account_number, account_number) == 0) {
            return i;
        }
    }
    return -1;
}

int is_duplicate_account(const Account * accounts,const int account_count,const char *input)
{
    for(int i=0;i<account_count;i++){
        if (strcmp(accounts[i].account_number, input) == 0)
        {
            return 1; // duplicate found
        }
    }
    return 0; // no duplicate
}


// Validate mobile number format ( 11 digits starting with 01)
int validate_mobile(const char *mobile)//by eyad
{
    if (strlen(mobile) != 11) {
        printf(RED "Error: Mobile must be 11 digits (e.g., 01000000000)\n" RESET);
        return 0;
    }

    for (int i = 0; i < 11; i++) {
        if (!isdigit(mobile[i])) {
            printf(RED "Error: Mobile must be all digits\n" RESET);
            return 0;
        }
    }

    if (mobile[0] != '0' || mobile[1] != '1') {
        printf(RED "Error: Mobile must start with 01 (Egyptian format)\n" RESET);
        return 0;
    }

    return 1;
}

// Validate name that thers name written there is letter not longg
int validate_name(const char *name)
{
    if (strlen(name) == 0) {
        printf(RED "Error: Name cannot be empty\n" RESET);
        return 0;
    }

    if (strlen(name) > 49) {
        printf(RED "Error: Name too long (max 49 characters)\n" RESET);
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
        printf(RED "Error: Name must contain at least one letter\n" RESET);
        return 0;
    }

    return 1;
}

// Trim leading and trailing spaces from a string
void trim_string(char *str)
{
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

int ensure_file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        fclose(fp);          // File exists
        return 1;
    }

    /* File created */
    fp = fopen(filename, "w");
    if (fp == NULL) {
        return 0;            // Failed to create
    }
    fclose(fp);
    return 1;
}
int Scan_acc_num(char* account_number){
    clear_input_buffer();
    for(int j=0;;j++)
    {
    if(j==2)printf(YELLOW "This is your last attempt to enter a valid account number\n" RESET);
    if(j==3){printf(RED "Operation unsuccessful\n" RESET);return 0;}
    printf(YELLOW "Enter Account Number (10 digits): " RESET);
    if (fgets(account_number, 11, stdin) == NULL) {
            clear_input_buffer();
            printf(RED "Error reading account number\n" RESET);
            clear_input_buffer();  // Clear any remaining input
            continue;
        }
        // Remove newline and trim
    account_number[strcspn(account_number, "\n")] = 0;
    trim_string(account_number);
    // Validate account number format
    if (strlen(account_number) != 10) {
        printf(RED "\nError: Account number must be exactly 10 digits\n" RESET);
        continue;
    }
    int valid=1;
    for (int i = 0; i < 10; i++){
        if (!isdigit(account_number[i])) {
            printf(RED "Error: Account number must be all digits\n" RESET);
            valid=0;
            break;
            }
        }
    if(!valid) continue;
    break;
    }
    return 1;
}

int check_active(Account* accounts,int account_count,char* account_number)
{
    int index=find_account_by_number(accounts,account_count,account_number);
    if(index == -1)
        return -1;
    return strcmp(accounts[index].status, "inactive");

}
