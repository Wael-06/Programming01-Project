#ifndef DELETE_MULTIBLE_H
#define DELETE_MULTIBLE_H

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
    Date date_of_opening;
    char status[10];
} Account;

// Function prototypes
void delete_multiple_menu();
void delete_by_date();
void delete_inactive_accounts();
int parse_date_string(const char *date_str, Date *date);
int is_inactive_for_90_days(const Date *opening_date);

#endif
