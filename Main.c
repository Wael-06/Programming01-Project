#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H
#ifndef LOGIN_H
#define LOGIN_H
#ifndef SEARCH_H
#define SEARCH_H

#include "login.h"
#include "search.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ACCOUNTS 1000

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

void clear_input();//BUFFER 

int sizefile(char *fname)//byyoussef
{
    FILE *fptr = fopen(fname, "rb");
    if (fptr == NULL)
        return -1;
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fclose(fptr);
    return size;
}

void print(Account account)//byyoussef
{
    printf("Account Number:%10s\n", account.account_number);
    printf("Name: %s\n", account.name);
    printf("E-mail: %s\n", account.email);
    printf("Balance: %.2f$\n", account.balance);
    printf("Mobile: %s\n", account.mobile);
    printf("Date Opened: ");
    int m = account.date_of_openeing.month;
    int y = account.date_of_openeing.year;
    if (m > 0 && m < 13)
    {
    }
    else if (m > 12)
    {
        while (m > 12)
        {
            m -= 12;
            y++;
        }
    }
    if (m <= 0)
    {
        printf("Invalid month");
        exit(-1);
    }
    switch (m)
    {
    case 1:
        printf("January");
        break;
    case 2:
        printf("February");
        break;
    case 3:
        printf("March");
        break;
    case 4:
        printf("April");
        break;
    case 5:
        printf("May");
        break;
    case 6:
        printf("June");
        break;
    case 7:
        printf("July");
        break;
    case 8:
        printf("August");
        break;
    case 9:
        printf("September");
        break;
    case 10:
        printf("October");
        break;
    case 11:
        printf("November");
        break;
    case 12:
        printf("December");
        break;
    default:
        break;
    }
    printf("%d\n", y);
    if (strcmp(account.status, " active") == 0)
        printf("Status: Active\n");
    else
        printf("Status: Inactive\n");
}
/*to get size of any file was planning in the login func. but didn't needed,but will useful as we go on*/
//------------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------Eyad Requirements--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

//void show_login_menu();
//void show_main_menu();
void save_accounts(); 
void load_accounts();  
void modify_account();
//------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------Youssef Requirements--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
//int login();//YOUSSEF WILL MAKE IT BETTER
/*The login function have a sscanf which (Dr.Saleh) said it isn't safe I will fix it later ,but other than that it is work is as a newly lubricated motor */
/*return 1 if successful,0 if failed,-1 if couldn't open the file*/
//void search_account();DONE
/*it works*/
void print_sorted();
void daily_limit();
//------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------Moataz Requirements--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------

void withdraw();           
void deposit();            
void transfer();           
void report();    
void advanced_search();
//------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------Abdlrahman Requirements--------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------------
void add_account();
void delete_account();
void delete_multi();
void add_account();
void change_status();      

#endif
#endif
#endif





