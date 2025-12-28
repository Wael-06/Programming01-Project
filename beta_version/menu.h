#ifndef MENU_H
#define MENU_H

#include "bank_system.h"


// Main menu functions
void show_initial_menu();        // Shows Login/Quit menu
void show_main_menu();           // Shows all functions after login

// Helper functions for menu flow
void handle_login_failed();      // Handles failed login attempt

#endif
