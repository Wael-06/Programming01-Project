#include "Deposit.h"
#include "helper1.h"
#include "helper2.h"
#include "Report.h"
#include "Save.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"

void deposit(Account* accounts,const int account_count){
    char acc_n[11];
    if(!Scan_acc_num(acc_n)){
        printf(RED "Account number to be deposited to scanned unsuccesfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
        }
    int acc_index = find_account_by_number(accounts,account_count,acc_n);
    if (acc_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, acc_n);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    if(!check_active(accounts,account_count,acc_n)){
        printf(YELLOW "Warning inactive user\n" RESET);
        printf(YELLOW "Please try again\n" RESET);
        return;
        }
    float amount=0;
    int flag=3;
    while(flag--){
        printf(YELLOW "Enter the amount to be deposited to %s (max:10000/deposit):" RESET,accounts[acc_index].name);
        scanf("%f",&amount);
        clear_input_buffer();
        if(compare(amount,10000)>0){
            printf(RED "Higher than 10000 (attempts left:%d)\n" RESET,flag);
            continue;}
        else
            break;
    }
    if(!confirm())
        return;
    accounts[acc_index].balance+=amount;
    quick_save_prompt(accounts,account_count);
    printf(GREEN "\nDeposit made successfully\n" RESET);
    add_transaction(acc_n,"Deposit",amount,accounts[acc_index].balance,"Successful Deposit");
}
