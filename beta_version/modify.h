#ifndef MODIFY_H
#define MODIFY_H

#include "bank_system.h"

// Function prototypes
void modify_account();
int find_account_by_number(const char *account_number);
int validate_email(const char *email);
int validate_mobile(const char *mobile);

#endif
