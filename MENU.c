#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H
#ifndef LOGIN_H
#define LOGIN_H

#include "login.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ACCOUNTS 1000
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
/*to get size of any file was planning in the login func. but didn't needed,but will useful as we go on*/
int login();//byyoussef
/*The login function have a sscanf which (Dr.Saleh) said it isn't safe I will fix it later ,but other than that it is work is as a newly lubricated motor */
/*return 1 if successful,0 if failed,-1 if couldn't open the file*/
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
void search_account();
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

