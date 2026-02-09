#ifndef HELPER1_H
#define HELPER1_H
#include "Color.h"
typedef struct
{
    int month;
    int year;
}Date;
typedef struct
{
    char account_number[11];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_openeing;
    char status[10];
}Account;

void clear_input_buffer();//byeyad
int compare_by_name(const void *a, const void *b);//bymoataz
int compare_by_date_oldest(const void *a, const void *b);//bymoataz
int compare_by_date_newest(const void *a, const void *b);//bymoataz
int compare_by_balance_asc(const void *a, const void *b);//bymoataz
int compare_by_status_active_first(const void *a, const void *b);//bymoataz
int count_valid_accounts();//byeyad
int compare(float a, float b);
int confirm();

#endif
