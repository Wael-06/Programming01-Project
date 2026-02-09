#include <stdio.h>
#include <stdlib.h>
#include "helper1.h"
#include "Login.h"
#include "Load.h"
#include "Menu.h"
#include "Color.h"

int main()
{
    login();
    int accounts_count= count_valid_accounts();
    Account* accounts=load_accounts();
    show_main_menu(accounts,&accounts_count);
    return 0;
}
