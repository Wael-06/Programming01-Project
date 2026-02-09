#include "add.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Color.h"

void add_account(Account* accounts, int* accounts_number)
{
    Account acc;
    if(*accounts_number==1000){
        printf(RED "Account limit reached\nNo further accounts can be added" RESET);
        return;
    }
    /* ================= ACCOUNT NUMBER ================= */
    printf(CYAN "\n=== ADD NEW ACCOUNT ===\n" RESET);
    if(!Scan_acc_num(acc.account_number))
    {
        printf(RED "Account number scanned unsuccesfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    if(is_duplicate_account(accounts, *accounts_number,acc.account_number))
    {
        printf(RED "Account number can't be a duplicate one\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    /* ================= NAME ================= */
    clear_input_buffer();
    int flag =3;
    while (flag--)
    {
        printf(YELLOW "please enter name: " RESET);
        fgets(acc.name, sizeof(acc.name), stdin);
        acc.name[strcspn(acc.name, "\n")] = '\0';

        if(validate_name(acc.name)){
            capitalize_words(acc.name);
            break;
        }
        printf(RED "Wrong Name Format (attempts left:%d)\n" RESET,flag);
        if(flag==0)
        {
            printf(RED "Account Name scanned unsuccesfully\n" RESET);
            printf(RED "Operation failed\n" RESET);
            return;
        }
    }
    /* ================= EMAIL ================= */
    flag=3;
    while(flag--)
    {
        printf(YELLOW "please enter your E-mail: " RESET);
        fgets(acc.email, sizeof(acc.email), stdin);
        acc.email[strcspn(acc.email, "\n")] = '\0';
        if(validate_email(acc.email))
            break;
        printf(RED "Wrong Email Format (attempts left:%d)\n" RESET,flag);
        if(flag==0)
        {
            printf(RED "Account Email scanned unsuccesfully\n" RESET);
            clear_input_buffer();
            printf(RED "Operation failed\n" RESET);
            return;
        }
    }
    /* ================= BALANCE ================= */

    flag = 3;
    while (flag--)
    {
        printf(YELLOW "Enter Initial Balance: " RESET);
        if (scanf("%f", &acc.balance) != 1)
        {
            printf(RED "Invalid number\n" RESET);
            clear_input_buffer();
            continue;
        }

        if (acc.balance >= 0)
            break;

        printf(RED "Wrong Balance (attempts left:%d)\n" RESET, flag);
        if (flag == 0)
        {
            printf(RED "Account Balance scanned unsuccessfully\n" RESET);
            clear_input_buffer();
            printf(RED "Operation failed\n" RESET);
            return;
        }
    }


    clear_input_buffer();
    /* ================= MOBILE ================= */
    flag=3;
    while(flag--)
    {
        printf(YELLOW "please enter mobile number: " RESET);
        fgets(acc.mobile, sizeof(acc.mobile), stdin);
        acc.mobile[strcspn(acc.mobile, "\n")] = '\0';
        if(validate_mobile(acc.mobile))
            break;
        printf(RED "Wrong Mobile Format (attempts left:%d)\n" RESET,flag);
        if(flag==0)
        {
            printf(RED "Account Mobile scanned unsuccesfully\n" RESET);
            printf(RED "Operation failed\n" RESET);
            return;
        }
    }
    /* ================= DATE ================= */
    time_t t = time(NULL);

    struct tm *tm_info = localtime(&t);
    acc.date_of_openeing.month = tm_info->tm_mon + 1;
    acc.date_of_openeing.year = tm_info->tm_year + 1900;

    /* ================= SAVE TO FILE ================= */

    FILE *fptr = fopen("accounts.txt", "a");
    if (fptr == NULL)
    {
        printf(RED "Error opening accounts file!\n" RESET);
        return;
    }
    strcpy(acc.status,"active");
    fprintf(fptr, "%s,%s,%s,%.2f,%s,%02d-%d,active\n",
            acc.account_number,
            acc.name,
            acc.email,
            acc.balance,
            acc.mobile,
            acc.date_of_openeing.month,
            acc.date_of_openeing.year);

    fclose(fptr);
    accounts[*accounts_number] = acc;
    (*accounts_number)++;
    printf(GREEN "\nAccount added successfully\n" RESET);
}
