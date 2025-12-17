#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ACCOUNTS 1000
void clear_input();//BUFFER 
int login();
void show_login_menu();
void show_main_menu();
void save_accounts(); 
void load_accounts();  
void modify_account();  
//YOUR REQUIRED TASKS YOUSSEF MOATTAZ ABDO
void add_account();   
int login();//YOUSSEF WILL MAKE IT BETTER
void delete_account();     
void search_account();      
void advanced_search();    
void change_status();      
void withdraw();           
void deposit();            
void transfer();           
void report();             
void print_sorted();       

#endif
