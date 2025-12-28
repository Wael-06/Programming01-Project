#ifndef DELETE_H // guard
#define DELETE_H
#define FILENAME "accounts.txt"
#define TEMP_FILE "temp_accounts.txt"

typedef struct
{
    int month;
    int year;
} Date;

typedef struct
{
    char account_number[12];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_openeing;
    char status[10];
} Account;

// Function prototypes
void delete_acount();
int find_account(const char *acc_num);
#endif
