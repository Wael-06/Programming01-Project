#include "Search.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"

void search_acc(Account* accounts,const int account_count)
{

    char input_search[11];
    if(!Scan_acc_num(input_search)){
        printf(RED "Account number to Search for Scanned unsuccessfully\nOperation failed\n" RESET);
        return;
        }
    int search_index = find_account_by_number(accounts,account_count,input_search);
    if (search_index == -1) {
        printf(RED "\nAccount %s not found!\n" RESET, input_search);
        return;
    }
    print_account_formatted(accounts+search_index);
}
