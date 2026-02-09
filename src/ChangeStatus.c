#include "ChangeStatus.h"
#include "helper1.h"
#include "ChangeStatus.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Color.h"

void change_status(Account *accounts, int accounts_number) {
    char input[11];
    if(!Scan_acc_num(input)){
        printf(RED "Account number to change status scanned unsuccesfully\n" RESET);
        printf(RED "Operation failed\n" RESET);
        return;
        }
    int input_index = find_account_by_number(accounts,accounts_number,input);
    if (input_index == -1) {
        printf(RED "\nError: Account %s not found!\n" RESET, input);
        printf(RED "Operation failed\n" RESET);
        return;
    }
    clear_input_buffer();
    char selection[20];
    int flag = 3;
    while(flag--){
    printf(YELLOW "\nSelect Action:\n1. Activate\n2. Deactivate\nEnter (1 or 2): " RESET);
    fgets(selection, sizeof(selection), stdin);
    selection[strcspn(selection, "\n")] = '\0';
    trim_string(selection);
    if (strcmp(selection, "1") == 0 || tolower(selection[0]) == 'a'){
        if(check_active(accounts,accounts_number,input)){
            printf(YELLOW "Already active\n" RESET);
            return;
        }
        strcpy(accounts[input_index].status,"active");
        printf(GREEN "Account status changed to active successfully\n" RESET);
        save_to_disk(accounts,accounts_number);
        return;
    }
    else if (strcmp(selection, "2") == 0 || tolower(selection[0]) == 'd'){
            if(!check_active(accounts,accounts_number,input)){
            printf(YELLOW "Already inactive\n" RESET);
            return;
        }
        strcpy(accounts[input_index].status,"inactive");
        printf(GREEN "Account status changed to inactive successfully\n" RESET);
        save_to_disk(accounts,accounts_number);
        return;
    }
    else {
        printf(RED "\nIncorrect input (attempts left:%d)\n" RESET,flag);
        }
    if(flag==0){
        printf(RED "Operation Failed\nPlease try again\n" RESET);
        return;
        }
    }
}
