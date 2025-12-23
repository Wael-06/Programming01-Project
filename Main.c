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
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//load account done el7 
void load_accounts() {
    FILE *file = fopen("accounts.txt", "r");
    
    if (file == NULL) {
        printf(" Error: Could not open file 'accounts.txt'.\n");
        printf("Creating new empty file\n");
        
        // Create empty file if it doesn't exist
        file = fopen("accounts.txt", "w");
        if (file) {
            fclose(file);
            account_count = 0;
            printf("Created new empty accounts file.\n");
        } else {
            printf(" Failed to create file.\n");
        }
        return;
    }
    
    char line[256];
    account_count = 0;
    int line_number = 0;
    int loaded_count = 0;
    
    printf("Loading accounts from 'accounts.txt'\n");
    
    while (fgets(line, sizeof(line), file) && account_count < MAX_ACCOUNTS) {
        line_number++;
        
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Parse the line: account_number,name,email,balance,mobile,date,status
        char acc_num[12], name[50], email[50], mobile[15], date_str[20], status[10];
        float balance;
        
        // Use sscanf to parse comma-separated values to seperate commas y3ny
        int parsed = sscanf(line, "%11[^,],%49[^,],%49[^,],%f,%14[^,],%19[^,],%9s",
                           acc_num, name, email, &balance, mobile, date_str, status);
        
        if (parsed != 7) {
            printf("Warning: Line %d has incorrect format (expected 7 fields, got %d)\n", 
                   line_number, parsed);
            printf("   Line: %s\n", line);
            continue;
        }
        
        // VALIDATION 1: Check account number is 10 digits
        if (strlen(acc_num) != 10) {
            printf(" Warning: Account number '%s' must be 10 digits (line %d)\n", 
                   acc_num, line_number);
            continue;
        }
        
        // VALIDATION 2: Check all characters are digits
        int valid_acc = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(acc_num[i])) {
                valid_acc = 0;
                break;
            }
        }
        if (!valid_acc) {
            printf("Warning: Account number '%s' contains non-digits (line %d)\n", 
                   acc_num, line_number);
            continue;
        }
        
        // VALIDATION 3: Check for duplicates
        int duplicate = 0;
        for (int i = 0; i < account_count; i++) {
            if (strcmp(accounts[i].account_number, acc_num) == 0) {
                printf("Warning: Duplicate account number '%s' (line %d)\n", 
                       acc_num, line_number);
                duplicate = 1;
                break;
            }
        }
        if (duplicate) continue;
        
        // VALIDATION 4: Check email has @ and .
        if (!strchr(email, '@') || !strchr(email, '.')) {
            printf("Warning: Invalid email format '%s' (line %d)\n", 
                   email, line_number);
            continue;
        }
        
        // VALIDATION 5: Check mobile format (Egyptian: 01) as tyhe one in txt
        if (strlen(mobile) != 11 || mobile[0] != '0' || mobile[1] != '1') {
            printf("Warning: Invalid mobile format '%s' (line %d)\n", 
                   mobile, line_number);
            continue;
        }
        
        // VALIDATION 6: Check balance is non-negative
        if (balance < 0) {
            printf("Warning: Negative balance %.2f (line %d)\n", 
                   balance, line_number);
            continue;
        }
        
        // VALIDATION 7: Parse date (MM-YYYY)
        int month, year;
        if (sscanf(date_str, "%d-%d", &month, &year) != 2) {
            printf("Warning: Invalid date format '%s' (line %d)\n", 
                   date_str, line_number);
            continue;
        }
        
        if (month < 1 || month > 12) {
            printf("Warning: Invalid month %d in date (line %d)\n", 
                   month, line_number);
            continue;
        }
        
        // VALIDATION 8: Check status
        if (strcmp(status, "active") != 0 && strcmp(status, "inactive") != 0) {
            printf("Warning: Invalid status '%s' (line %d). Using 'active'\n", 
                   status, line_number);
            strcpy(status, "active");
        }
        
        // ALL VALIDATIONS PASSED! Store the account isa
        strcpy(accounts[account_count].account_number, acc_num);
        strcpy(accounts[account_count].name, name);
        strcpy(accounts[account_count].email, email);
        accounts[account_count].balance = balance;
        strcpy(accounts[account_count].mobile, mobile);
        accounts[account_count].date_opened.month = month;
        accounts[account_count].date_opened.year = year;
        strcpy(accounts[account_count].status, status);
        
        account_count++;
        loaded_count++;
    }
    
    fclose(file);
    //final check is there account to be loaded wla NO??
    if (loaded_count == 0) {
        printf("No valid accounts loaded from file.\n");
    } else {
        printf("Successfully loaded %d account(s).\n", loaded_count);
    }
}
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







