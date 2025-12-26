#include "helper2.h"
#include "helper1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_account_formatted(const Account *account)//bymoataz
{
    const char *months[] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};

    printf("Account Number: %s\n", account->account_number);
    printf("Name: %s\n", account->name);
    printf("E-mail: %s\n", account->email);
    printf("Balance: %.0f $\n", account->balance);
    printf("Mobile: %s\n", account->mobile);
    printf("Date Opened: %s %d\n",
           months[account->date_of_openeing.month],
           account->date_of_openeing.year);
    printf("Status: %s\n",account->status);
    printf("\n");
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
