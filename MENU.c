#ifndef BANK_SYSTEM_H
#define BANK_SYSTEM_H

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
int login()//byyoussef
{
    FILE *fptr = fopen("users.txt", "r");
    if (!fptr)
    {
        return -1;
    }

    char file_username[50], file_password[10];
    char input_username[50], input_password[10];
    char line[100];

    int attempts = 0;

    while (attempts < 3)
    {
        printf("Enter Username: ");
        fgets(input_username, sizeof(input_username), stdin);
        input_username[strcspn(input_username, "\n")] = '\0';
        
        printf("Enter Password: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")] = '\0';

        rewind(fptr);

        int success = 0;

        while (fgets(line, sizeof(line), fptr))
        {
            line[strcspn(line, "\n")] = 0;

            sscanf(line, "%49s %9s", file_username, file_password);

            if (strcmp(input_username, file_username) == 0 &&strcmp(input_password, file_password) == 0)
            {
                success = 1;
                break;
            }
        }

        if (success)
        {
            printf("You have logged in successfully\n");
            fclose(fptr);
            return 1;
        }

        attempts++;

        if (attempts == 2)
            printf("This is your last trial\n");
        else if (attempts < 3)
            printf("Incorrect, try again\n");
    }

    printf("Sorry, You failed login\n");
    fclose(fptr);
    return 0;
}
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

