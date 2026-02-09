#include "helper1.h"
#ifndef REPORT_H
#define REPORT_H
void add_transaction(const char *account_number, const char *type, float amount, float balance_after, const char *desc);
void print_report(const Account * accounts,const int account_count);
#endif
