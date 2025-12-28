#ifndef CHANGE_H
#define CHANGE_H

#include <stdio.h>

typedef struct {
    int month;
    int year;
} Date;

typedef struct {
    char account_number[12];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_opening;
    char status[10];
} Account;

// Function declarations
float stof(const char *str);
void clean_status_string(char *status);
void printwithlines(Account account);
int search(const char *input_search, int *line_number, Account *acc);
void update_status_in_file(int line_number, const char *new_status);
void change_status();

#endif
