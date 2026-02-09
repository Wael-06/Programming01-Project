#include "helper1.h"
#ifndef HELPER2_H
#define HELPER2_H
void print_account_formatted(const Account *account);
void print_accounts_formatted(const Account *accounts, int accounts_number);
void print_account(const Account *account);
void print_accounts(const Account *accounts, int accounts_number);
void capitalize_words(char *str);
int validate_email(const char *email);
int find_account_by_number(const Account * accounts,const int account_count,const char *account_number);
int is_duplicate_account(const Account * accounts,const int account_count,const char *input);
int validate_mobile(const char *mobile);
int validate_name(const char *name);
void trim_string(char *str);
int ensure_file_exists(const char *filename);
int Scan_acc_num(char* accoun_number);
int check_active(Account* accounts,int account_count,char* account_number);
#endif
