#include "Menu.h"
#include "helper1.h"
#include "helper2.h"
#include "Add.h"
#include "Delete.h"
#include "DeleteMultiple.h"
#include "Modify.h"
#include "Search.h"
#include "AdvancedSearch.h"
#include "ChangeStatus.h"
#include "Withdraw.h"
#include "Deposit.h"
#include "Transfer.h"
#include "Report.h"
#include "SortedPrint.h"
#include "Quit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Color.h"

void show_main_menu(Account* accounts,int* account_count) {
    int choice;
    do {
        printf(BLUE "\n=========================================\n" RESET);
        printf(CYAN "     MAIN MENU - Bank Management System\n" RESET);
        printf(BLUE "=========================================\n" RESET);
        printf(GREEN "1.  ADD\n" RESET);
        printf(GREEN "2.  DELETE\n" RESET);
        printf(GREEN "3.  DELETE Multiple\n" RESET);
        printf(GREEN "4.  MODIFY\n" RESET);
        printf(GREEN "5.  SEARCH\n" RESET);
        printf(GREEN "6.  ADVANCED SEARCH\n" RESET);
        printf(GREEN "7.  CHANGE_STATUS\n" RESET);
        printf(GREEN "8.  WITHDRAW\n" RESET);
        printf(GREEN "9.  DEPOSIT\n" RESET);
        printf(GREEN "10. TRANSFER\n" RESET);
        printf(GREEN "11. REPORT\n" RESET);
        printf(GREEN "12. PRINT\n" RESET);
        printf(RED "13. QUIT\n" RESET);
        printf(BLUE "=========================================\n" RESET);
        printf(YELLOW "Enter your choice (1-13): " RESET);

        if ( scanf("%d", &choice)!= 1) {
            printf(RED "Invalid input. Please enter a number.\n" RESET);
            clear_input_buffer();
            continue;
        }

        // Handle the choice (EXACTLY 13 OPTIONS AS REQUIRED)
        switch(choice) {
            case 1:  // ADD
                add_account(accounts,account_count);
                break;
            case 2:  // DELETE
                delete_account(accounts,account_count);
                break;
            case 3: //DELETE MULTIPLE
                clear_input_buffer();
                delete_multiple_menu(accounts,account_count);
                break;
            case 4:  // MODIFY
                modify_account(accounts,*account_count);
                break;
            case 5:  // SEARCH
                search_acc(accounts,*account_count);
                break;
            case 6:  // ADVANCED SEARCH
                clear_input_buffer();
                Advanced_Search(accounts,*account_count);
                break;
            case 7:  // CHANGE_STATUS
                change_status(accounts,*account_count);
                break;
            case 8:  // WITHDRAW
                withdraw(accounts,*account_count);
                break;
            case 9:  // DEPOSIT
                deposit(accounts,*account_count);
                break;
            case 10:  // TRANSFER
                transfer(accounts,*account_count);
                break;
            case 11: // REPORT
                print_report(accounts,*account_count);
                break;
            case 12: // PRINT
                sortedprint(accounts,*account_count);
                break;
            case 13: // QUIT
                quit(accounts,*account_count);
                break;  // Exit menu loop
            default:
                printf(RED "\nInvalid choice. Please enter 1-13.\n" RESET);
        }

    } while (1);
}
