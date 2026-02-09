#include "Save.h"
#include "helper1.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"


int save_to_disk(Account* accounts, int account_count) {
    FILE *file = fopen("accounts.txt", "w");
    if (file == NULL) {
            printf(RED "Opening file failed.\n" RESET);
            return 0;}

    for (int i = 0; i < account_count; i++) {
        fprintf(file, "%s,%s,%s,%.2f,%s,%02d-%d,%s\n",
                accounts[i].account_number,
                accounts[i].name,
                accounts[i].email,
                accounts[i].balance,
                accounts[i].mobile,
                accounts[i].date_of_openeing.month,
                accounts[i].date_of_openeing.year,
                accounts[i].status);
    }

    fclose(file);
    return 1;
}


void quick_save_prompt(Account* accounts, int account_count) {
    printf(YELLOW "\nSave changes? (y/n): " RESET);

    char choice;
    // Loop until valid input
    while (1) {
        scanf(" %c", &choice);
        clear_input_buffer();

        // Check if input is valid
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            break;  // Valid input, exit loop
        } else {
            printf(RED "Invalid input! Please enter 'y' or 'n': " RESET);
        }
    }

    if (choice == 'y' || choice == 'Y') {
        if (save_to_disk(accounts,account_count)) {
            printf(GREEN "SUCCESS: Changes saved.\n" RESET);
        } else {
            printf(RED "ERROR: Save failed!\n" RESET);
        }
    } else {
        printf(YELLOW "NOTE: Changes not saved.\n" RESET);
    }
}
