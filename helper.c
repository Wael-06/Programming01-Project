#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Date
{
    int month;
    int year;
};

struct Account
{
    char account_number[12];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_openeing;
    unsigned int status:1;
};

int filesize(char *fname)//byyoussef
{
    FILE *fptr = fopen(fname, "rb");
    if (fptr == NULL)
        exit(-1);
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fclose(fptr);
    return size;
}

struct Date* Create_Date(int month, int year) //bymoataz
{
    struct Date *date = malloc(sizeof(struct Date));
    if (date == NULL) {
        return NULL;
    }

    date->month = month;
    date->year = year;

    return date;
}

void destroy_date(struct Date *date) //bymoataz
{
    if (date != NULL) {
        free(date);
    }
}

struct Account* Construct_Account(const char *account_number,const char *name,const char *email,float balance,const char *mobile,struct Date date_of_opening,unsigned int status)//bymoataz
{
    struct Account *account = malloc(sizeof(struct Account));
    if (account == NULL) {
        return NULL;
    }
    strncpy(account->account_number, account_number, sizeof(account->account_number) - 1);
    account->account_number[sizeof(account->account_number) - 1] = '\0';
    strncpy(account->name, name, sizeof(account->name) - 1);
    account->name[sizeof(account->name) - 1] = '\0';
    strncpy(account->email, email, sizeof(account->email) - 1);
    account->email[sizeof(account->email) - 1] = '\0';
    account->balance = balance;
    strncpy(account->mobile, mobile, sizeof(account->mobile) - 1);
    account->mobile[sizeof(account->mobile) - 1] = '\0';
    account->date_of_openeing.month = date_of_opening.month;
    account->date_of_openeing.year = date_of_opening.year;
    account->status = status & 1;
    return account;
}

void destroy_account(struct Account *account)//bymoataz
{
    if (account != NULL) {
        free(account);
    }
}
