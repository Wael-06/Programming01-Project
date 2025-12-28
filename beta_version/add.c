#include "add.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void add_acount()
{
    Account acc;
    char temp[100];

    /* ================= ACCOUNT NUMBER ================= */
    while (1)
    {
        printf("please enter account number (10 digits): ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if (strlen(temp) != 10)
        {
            printf("Account number must be exactly 10 digits\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; i < 10; i++)
        {
            if (temp[i] < '0' || temp[i] > '9')
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Account number must contain digits only\n");
            continue;
        }

        if (!account_unique(temp))
        {
            printf("Error: Account number already exists!\n");
            continue;
        }

        strcpy(acc.account_number, temp);
        break;
    }
    /* ================= NAME ================= */
    while (1)
    {
        printf("please enter name: ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';

        if (strlen(temp) == 0)
        {
            printf("Error: Name cannot be empty!\n");
            continue;
        }

        int valid = 1;
        for (int i = 0; temp[i] != '\0'; i++)
        {
            char c = temp[i];
            int is_alpha = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
            int is_space = (c == ' ');
            int is_hyphen = (c == '-');

            if (!is_alpha && !is_space && !is_hyphen)
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Error: Invalid characters in name\n");
            continue;
        }

        strcpy(acc.name, temp);
        break;
    }
    /* ================= EMAIL ================= */
    printf("please enter your E-mail: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strcpy(acc.email, temp);

    /* ================= BALANCE ================= */
    while (1)
    {
        printf("Enter Initial Balance: ");
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';

        int dot_count = 0;
        int valid = 1;

        for (int i = 0; temp[i] != '\0'; i++)
        {
            if (temp[i] < '0' || temp[i] > '9')
            {
                if (temp[i] == '.' && dot_count == 0)
                {
                    dot_count++;
                }
                else
                {
                    valid = 0;
                    break;
                }
            }
        }

        if (!valid || strlen(temp) == 0)
        {
            printf("Error: Invalid balance amount!\n");
            continue;
        }

        acc.balance = atof(temp);
        break;
    }

    /* ================= MOBILE ================= */
    printf("please enter mobile number: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strcpy(acc.mobile, temp);

    /* ================= DATE ================= */
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    acc.date_of_openeing.month = tm_info->tm_mon + 1;
    acc.date_of_openeing.year = tm_info->tm_year + 1900;

    /* ================= SAVE TO FILE ================= */
    FILE *fptr = fopen("accounts.txt", "a");
    if (fptr == NULL)
    {
        printf("Error opening accounts file!\n");
        return;
    }

    fprintf(fptr, "%s,%s,%s,%.2lf,%s,%02d-%d,active\n",
            acc.account_number,
            acc.name,
            acc.email,
            acc.balance,
            acc.mobile,
            acc.date_of_openeing.month,
            acc.date_of_openeing.year);

    fclose(fptr);
    printf("\nAccount added successfully\n");
}

/* ================= UNIQUE CHECK ================= */
int account_unique(const char *acc_num)
{
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL)
    {
        return 1; // file doesn't exist yet
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char line_copy[256];
        strcpy(line_copy, line);

        char *token = strtok(line_copy, ",");
        if (token != NULL && strcmp(token, acc_num) == 0)
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
