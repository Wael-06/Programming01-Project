#ifndef HELPER1_H
#define HELPER1_H
typedef struct
{
    int month;
    int year;
}Date;
typedef struct
{
    char account_number[12];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_openeing;
    char status[10];
}Account;

void clear_input_buffer();//byeyad
int filesize(char *fname);//byyoussef
Date* Create_Date(int month, int year);//bymoataz
void destroy_date(Date *date);//bymoataz
Account* Construct_Account(const char *account_number,const char *name,const char *email,float balance,const char *mobile,Date date_of_opening,const char *status);//bymoataz
void destroy_account(Account *account);//bymoataz
int compare_by_name(const void *a, const void *b);//bymoataz
int compare_by_date_oldest(const void *a, const void *b);//bymoataz
int compare_by_date_newest(const void *a, const void *b);//bymoataz
int compare_by_balance_asc(const void *a, const void *b);//bymoataz
int compare_by_status_active_first(const void *a, const void *b);//bymoataz

int count_valid_accounts();//byeyad

#endif
