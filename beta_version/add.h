#ifndef ADD_H // guard
#define ADD_H

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
void add_acount();
int account_unique(const char *acc_num);
#endif