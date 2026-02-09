#include "Delete.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Color.h"


void delete_account(Account* accounts,int* account_count)
{
    char acc_num[11];
    if(!Scan_acc_num(acc_num)){
        printf(RED "Account number to delete account scanned unsuccesfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
        }
    int acc_index = find_account_by_number(accounts,*account_count,acc_num);
    if (acc_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, acc_num);
        printf(RED "Operation failed\n" RESET);
        return;
    }

        if (accounts[acc_index].balance)
        {
            printf(RED "\n Cannot delete account with non-zero balance (%.2f)\n" RESET,accounts[acc_index].balance);
            return;
        }

        if(!confirm()){
            printf(YELLOW "\nDeletion cancelled.\n" RESET);
            return;
        }
        for (int i = acc_index; i < *account_count - 1; i++) {
        accounts[i] = accounts[i + 1];
    }
    printf(GREEN "Account deleted successfully" RESET);
    (*account_count)--;
    save_to_disk(accounts,*account_count);
    }
