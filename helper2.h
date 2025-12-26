#include "helper1.h"
#ifndef HELPER2_H
#define HELPER2_H
void print_account_formatted(const Account *account);//by moataz
void print_account(const Account *account);//by moataz
void print_accounts(const Account *accounts, int accounts_number);//by moataz
void capitalize_words(char *str);//by moataz
int validate_email(const char *email);//by eyad
int find_account_by_number(const Account * accounts,const int account_count,const char *account_number);//by eyad
int validate_mobile(const char *mobile);//by eyad
int validate_name(const char *name);//by eyad
void trim_string(char *str);//by eyad
int ensure_file_exists(const char *filename);//by moataz
int Scan_acc_num(char* accoun_number);//by moataz but from eyad
int check_active(Account* accounts,int account_count,char* account_number);//by moataz
#endif
