#ifndef HELPER_H
#define HELPER_H
typedef struct Date Date;
typedef struct Account Account;
int filesize(char *fname);//byyoussef
struct Date* Create_Date(int month, int year);//bymoataz
void destroy_date(struct Date *date);//bymoataz
struct Account* Construct_Account(const char *account_number,const char *name,const char *email,float balance,const char *mobile,struct Date date_of_opening,unsigned int status);//bymoataz
void destroy_account(struct Account *account);//bymoataz
int compare_by_name(const void *a, const void *b);//bymoataz
int compare_by_date_oldest(const void *a, const void *b);//bymoataz
int compare_by_date_newest(const void *a, const void *b);//bymoataz
int compare_by_balance_asc(const void *a, const void *b);//bymoataz
int compare_by_status_active_first(const void *a, const void *b);//bymoataz
#endif

