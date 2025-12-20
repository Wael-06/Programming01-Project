#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int month;
    int year;
} Date;

typedef struct
{
    char account_number[12];
    char name[50];
    char email[50];
    float balance;
    char mobile[15];
    Date date_of_openeing;
    char status[10];
} Account;

float stof(const char *str)
{
    float result = 0.0f;
    float fraction = 0.0f;
    int divisor = 1;

    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }

    if (*str == '.')
    {
        str++;
        while (*str >= '0' && *str <= '9')
        {
            fraction = fraction * 10 + (*str - '0');
            divisor *= 10;
            str++;
        }
    }

    return result + fraction / divisor;
}

void print(Account account)
{
    printf("Account Number:%10s\n", account.account_number);
    printf("Name: %s\n", account.name);
    printf("E-mail: %s\n", account.email);
    printf("Balance: %.2f$\n", account.balance);
    printf("Mobile: %s\n", account.mobile);
    printf("Date Opened: ");
    int m = account.date_of_openeing.month;
    int y = account.date_of_openeing.year;
    if (m > 0 && m < 13)
    {
    }
    else if (m > 12)
    {
        while (m > 12)
        {
            m -= 12;
            y++;
        }
    }
    if (m <= 0)
    {
        printf("Invalid month");
        exit(-1);
    }
    switch (m)
    {
    case 1:
        printf("January");
        break;
    case 2:
        printf("February");
        break;
    case 3:
        printf("March");
        break;
    case 4:
        printf("April");
        break;
    case 5:
        printf("May");
        break;
    case 6:
        printf("June");
        break;
    case 7:
        printf("July");
        break;
    case 8:
        printf("August");
        break;
    case 9:
        printf("September");
        break;
    case 10:
        printf("October");
        break;
    case 11:
        printf("November");
        break;
    case 12:
        printf("December");
        break;
    default:
        break;
    }
    printf("%d\n", y);
    if (strcmp(account.status, " active") == 0)
        printf("Status: Active\n");
    else
        printf("Status: Inactive\n");
}

void search()
{

    FILE *fptr = fopen("accounts.txt", "r");
    if (fptr == NULL)
    {
        printf("file not found");
        exit(-1);
    }

    char input_search[12];

    printf("Enter the account number you want to search: ");
    fgets(input_search, 12, stdin);
    input_search[strcspn(input_search, "\n")] = '\0';

    char buf[200];
    int found = 0;
    Account acc;
    while (fgets(buf, 199, fptr))
    {
        /*if (feof(fptr))
        {
            printf("test");
            break;
        }*//*The last account can't be accessed*/
        char *token;

        token = strtok(buf, ",\n\r");
        if (token == NULL) break;
        strncpy(acc.account_number, token, sizeof(acc.account_number));
        acc.account_number[sizeof(acc.account_number)-1] = '\0';

        token = strtok(NULL, ",\n\r");
        strncpy(acc.name, token, sizeof(acc.name));
        acc.name[sizeof(acc.name)-1] = '\0';

        token = strtok(NULL, ",\n\r");
        strncpy(acc.email, token, sizeof(acc.email));
        acc.email[sizeof(acc.email)-1] = '\0';

        token = strtok(NULL, ",\n\r");
        acc.balance = stof(token);

        token = strtok(NULL, ",\n\r");
        strncpy(acc.mobile, token, sizeof(acc.mobile));
        acc.mobile[sizeof(acc.mobile)-1] = '\0';

        token = strtok(NULL, ",\n\r");
        sscanf(token, "%d-%d", &acc.date_of_openeing.month, &acc.date_of_openeing.year);

        token = strtok(NULL, ",\n\r");
        strncpy(acc.status, token, sizeof(acc.status));
        acc.status[sizeof(acc.status)-1] = '\0';


        if(strcmp(acc.account_number,input_search)==0)
        {
            print(acc);
            found=1;
            break;
        }
    }
    if(!found)
    {
        printf("Account not found.\n");
    }
    fclose(fptr);
}

int main()
{

    search();
    return 0;
}
