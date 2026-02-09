#include "Withdraw.h"
#include "helper1.h"
#include "helper2.h"
#include "Report.h"
#include "DailyLimit.h"
#include "Save.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"

void withdraw(Account* accounts,const int account_count){
    char acc_n[11];
    if(!Scan_acc_num(acc_n)){
        printf(RED "Account number to be withdrawn from scanned unsuccessfully\nOperation failed\n" RESET);
        return;
        }
    int acc_index = find_account_by_number(accounts,account_count,acc_n);
    if (acc_index == -1) {
        printf(RED "\nError: Account %s not found!\nOperation failed\n" RESET, acc_n);
        return;
    }
    if(!check_active(accounts,account_count,acc_n)){
        printf(YELLOW "Warning inactive user\nPlease try again\n" RESET);
        return;
        }
    float amount=0;
    int flag=3;
    float DailyLimit=daily_limit_check(acc_n);
    printf(BLUE "Amount withdrawn today: %.2f\n" RESET,DailyLimit);
    if(DailyLimit==50000){
                printf(RED "Withdrawal Daily limit Reached\nPlease try again tomorrow\n" RESET);
                return;
            }
    while(flag--){
        printf(YELLOW "Enter the amount to be withdrawn from %s (max:10000/withdrawal):" RESET,accounts[acc_index].name);
        scanf("%f",&amount);
        clear_input_buffer();
        if(compare(amount,10000)>0){
            printf(RED "Higher than 10000 (attempts left:%d)\n" RESET,3-flag);
            continue;}
        if(compare(amount,accounts[acc_index].balance)<=0){
            if(DailyLimit+amount>50000){
                    printf(RED "Withdrawal Daily limit OverReached(attempts left:%d)\nPlease Enter  less than or equal %.2f\n" RESET,3-flag,50000-DailyLimit);
                    continue;
            }
            break;}
        printf(RED "Insufficient balance in the account (attempts left:%d)\n" RESET,flag);
    }
    if(!confirm())
        return;
    accounts[acc_index].balance-=amount;
    quick_save_prompt(accounts,account_count);
    printf(GREEN "Withdrawal made successfully\n" RESET);
    add_daily_limit(acc_n,amount);
    add_transaction(acc_n,"Withdraw",amount,accounts[acc_index].balance,"Successful Withdrawal");
}
