#include "Transfer.h"
#include "helper1.h"
#include "helper2.h"
#include "Report.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void transfer(Account* accounts,const int account_count)
{
    char acc_from_n[20];
    char acc_to_n[20];
    if(!Scan_acc_num(acc_from_n)){
        printf("Account number to transfer from scanned unsuccesfully\nOperation failed\n");
        return;
        }
    int account_from_index = find_account_by_number(accounts,account_count,acc_from_n);
    if (account_from_index == -1) {
        printf("\nError: Account %s not found!\nOperation failed\n", acc_from_n);
        return;
    }
    if(!check_active(accounts,account_count,acc_from_n)){
        printf("Warning inactive sender\nPlease try again\n");
        return;
        }
    if(!Scan_acc_num(acc_to_n)){
        printf("Account number to transfer to scanned unsuccesfully\nOperation failed\n");
        return;
        }
    int account_to_index = find_account_by_number(accounts,account_count,acc_to_n);
    if (account_to_index == -1) {
        printf("\nError: Account %s not found!\nOperation failed\n", acc_to_n);
        return;
    }
    if(!check_active(accounts,account_count,acc_to_n)){
        printf("Warning inactive receiver\nPlease try again\n");
        return;
        }
    float amount=0;
    int flag=3;
    while(flag--){
        printf("Enter the amount to be transfered from %s to %s:",accounts[account_from_index].name,accounts[account_to_index].name);
        scanf("%f",&amount);
        if(compare(amount,accounts[account_from_index].balance)<=0)
            break;
        printf("Insufficient balance in sender account (attempts left:%d)",3-flag);
    }
    if(!confirm())
        return;
    accounts[account_from_index].balance-=amount;
    accounts[account_to_index].balance+=amount;
    char des_from[100];
    char des_to[100];
    sprintf(des_from,"transfered to %s",accounts[account_to_index].account_number);
    sprintf(des_to,"transfered from %s",accounts[account_from_index].account_number);
    add_transaction(acc_from_n,"Transfer",amount,accounts[account_from_index].balance,des_from);
    add_transaction(acc_to_n,"Transfer",amount,accounts[account_to_index].balance,des_to);
}
