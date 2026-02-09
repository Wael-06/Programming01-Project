#include "Quit.h"
#include "helper1.h"
#include "helper2.h"
#include "Save.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"
void quit(Account* accounts,const int account_count){
    if(!confirm())
        return;
    if(!save_to_disk(accounts,account_count)){
     printf(RED "Saving Accounts Unsuccessful\nPlease Try again\n" RESET);
     return;
    }
    printf(GREEN "Accounts Saved Successfully\n" RESET);
        free(accounts);
    exit(0);
}
