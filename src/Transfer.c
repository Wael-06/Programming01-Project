#include "Transfer.h"
#include "helper1.h"
#include "helper2.h"
#include "Report.h"
#include "Save.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"

void transfer(Account* accounts,const int account_count)
{
    char acc_from_n[11];
    char acc_to_n[11];
    printf(CYAN "Account to transfer from\n" RESET);
    if(!Scan_acc_num(acc_from_n)){
        printf(RED "Account number to transfer from scanned unsuccesfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
        }
    int account_from_index = find_account_by_number(accounts,account_count,acc_from_n);
    if (account_from_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, acc_from_n);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    if(!check_active(accounts,account_count,acc_from_n)){
        printf(YELLOW "Warning inactive sender\n" RESET);
        printf(YELLOW "Please try again\n" RESET);
        return;
        }
    printf(CYAN "Account to transfer to\n" RESET);
    if(!Scan_acc_num(acc_to_n)){
        printf(RED "Account number to transfer to scanned unsuccessfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
        }
        if(!strcmp(acc_from_n,acc_to_n)){
        printf(RED "Can't Transfer to and from the same account\n" RESET);
        return;
    }
    int account_to_index = find_account_by_number(accounts,account_count,acc_to_n);
    if (account_to_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, acc_to_n);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    if(!check_active(accounts,account_count,acc_to_n)){
        printf(YELLOW "Warning inactive receiver\n" RESET);
        printf(YELLOW "Please try again\n" RESET);
        return;
        }
    float amount=0;
    int flag=3;
    while(flag--){
        printf(YELLOW "Enter the amount to be transfered from %s to %s:" RESET,accounts[account_from_index].name,accounts[account_to_index].name);
        scanf("%f",&amount);
        clear_input_buffer();
        if(compare(amount,accounts[account_from_index].balance)<=0)
            break;
        printf(RED "Insufficient balance in sender account (attempts left:%d)\n" RESET,flag);
    }
    if(!confirm())
        return;
    accounts[account_from_index].balance-=amount;
    accounts[account_to_index].balance+=amount;
    quick_save_prompt(accounts,account_count);
    printf(GREEN "Transfer made successfully\n" RESET);
    char des_from[100];
    char des_to[100];
    sprintf(des_from,"transfered to %s",accounts[account_to_index].account_number);
    sprintf(des_to,"transfered from %s",accounts[account_from_index].account_number);
    add_transaction(acc_from_n,"Transfer",amount,accounts[account_from_index].balance,des_from);
    add_transaction(acc_to_n,"Transfer",amount,accounts[account_to_index].balance,des_to);
}
