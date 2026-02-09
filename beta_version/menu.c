#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bank_system.h"
#include "menu.h"
#include "modify.h"
#include "Load.h"

// ==================== EXTERNAL FUNCTIONS ====================
extern Account* load_accounts();
extern void modify_account();
extern void quick_save_prompt();
extern void quit_program();

// Other functions your team will implement
extern void add_account();
extern void delete_account();
extern void search_account();
extern void advanced_search();
extern void change_status();
extern void withdraw();
extern void deposit();
extern void transfer();
extern void report();
extern void print_sorted();

// ==================== INITIAL MENU (LOGIN/QUIT ONLY) ====================

void show_initial_menu() {
    int choice;
    
    printf("\n=========================================\n");
    printf("     BANK MANAGEMENT SYSTEM\n");
    printf("=========================================\n");
    printf("1. LOGIN\n");
    printf("2. QUIT\n");
    printf("=========================================\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clear_input_buffer();
        show_initial_menu();
        return;
    }
    clear_input_buffer();
    
    switch(choice) {
        case 1:  // LOGIN
            if (login()) {
                // Load accounts by default after successful login
                printf("\nLoading account data...\n");
                accounts = load_accounts();
                
                if (accounts != NULL) {
                    show_main_menu();  // Go to main menu
                } else {
                    printf("Failed to load accounts.\n");
                    show_initial_menu();
                }
            } else {
                // Login failed
                handle_login_failed();
            }
            break;
            
        case 2:  // QUIT
            printf("\nThank you for using Bank Management System!\n");
            exit(0);
            break;
            
        default:
            printf("\nInvalid choice. Please enter 1 or 2.\n");
            show_initial_menu();
    }
}

// ==================== HANDLE LOGIN FAILED ====================

void handle_login_failed() {
    int choice;
    
    printf("\nLogin failed. What would you like to do?\n");
    printf("1. Go back to menu\n");
    printf("2. Exit\n");
    printf("Enter choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        clear_input_buffer();
        handle_login_failed();
        return;
    }
    clear_input_buffer();
    
    switch(choice) {
        case 1:
            show_initial_menu();  // Go back to initial menu
            break;
        case 2:
            printf("\nThank you for using Bank Management System!\n");
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            handle_login_failed();
    }
}

// ==================== MAIN MENU (EXACTLY AS REQUIRED) ====================

void show_main_menu() {
    int choice;
    
    do {
        printf("\n=========================================\n");
        printf("     MAIN MENU - Bank Management System\n");
        printf("=========================================\n");
        printf("1. ADD\n");
        printf("2. DELETE\n");
        printf("3. MODIFY\n");
        printf("4. SEARCH\n");
        printf("5. ADVANCED SEARCH\n");
        printf("6. CHANGE_STATUS\n");
        printf("7. WITHDRAW\n");
        printf("8. DEPOSIT\n");
        printf("9. TRANSFER\n");
        printf("10. REPORT\n");
        printf("11. PRINT\n");
        printf("12. QUIT\n");
        printf("=========================================\n");
        printf("Enter your choice (1-12): ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        
        // Handle the choice (EXACTLY 12 OPTIONS AS REQUIRED)
        switch(choice) {
            case 1:  // ADD
                if (add_account) {
                    add_account();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 2:  // DELETE
                if (delete_account) {
                    delete_account();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 3:  // MODIFY
                if (modify_account) {
                    modify_account();  // Already has quick_save_prompt() inside
                }
                break;
                
            case 4:  // SEARCH
                if (search_account) {
                    search_account();  // Read-only, no save needed
                }
                break;
                
            case 5:  // ADVANCED SEARCH
                if (advanced_search) {
                    advanced_search();  // Read-only, no save needed
                }
                break;
                
            case 6:  // CHANGE_STATUS
                if (change_status) {
                    change_status();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 7:  // WITHDRAW
                if (withdraw) {
                    withdraw();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 8:  // DEPOSIT
                if (deposit) {
                    deposit();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 9:  // TRANSFER
                if (transfer) {
                    transfer();
                    data_modified = 1;
                    quick_save_prompt();  // Ask to save AFTER function
                }
                break;
                
            case 10: // REPORT
                if (report) {
                    report();  // Read-only, no save needed
                }
                break;
                
            case 11: // PRINT
                if (print_sorted) {
                    print_sorted();  // Read-only, no save needed
                }
                break;
                
            case 12: // QUIT
                quit_program();  
                return;  // Exit menu loop
                
            default:
                printf("\nInvalid choice. Please enter 1-12.\n");
        }
        
    } while (choice != 12);
}
