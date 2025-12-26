#include "DailyLimit.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void daily_limit(int account_number, double withdrawal_amount)
{
    FILE *fp;
    char file_date[20];
    char today[20];

    /* Get today's date */
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(today, sizeof(today), "%Y-%m-%d", tm_info);

    /* Try to open file for reading */
    if(!ensure_file_exists("daily_limit.txt"))
    fp = fopen("daily_limit.txt", "r");

    if (fp == NULL)
    {
        /* File doesn't exist → create it */
        fp = fopen("daily_limit.txt", "w");
        if (fp == NULL)
            return;

        fprintf(fp, "%s\n", today);
        fprintf(fp, "%d %.2f\n", account_number, withdrawal_amount);
        fclose(fp);
        return;
    }

    /* Read the date stored in file */
    fgets(file_date, sizeof(file_date), fp);
    file_date[strcspn(file_date, "\r\n")] = '\0'; // remove '\n'
    fclose(fp);

    /* Compare dates */
    if (strcmp(today, file_date) == 0)
    {
        /* Same date → append */
        fp = fopen("daily_limit.txt", "a");
        fprintf(fp, "%d %.2f\n", account_number, withdrawal_amount);
    }
    else if (strcmp(today, file_date) > 0)
    {
        fp = fopen("daily_limit.txt", "w");
        fprintf(fp, "%s\n", today);
        fprintf(fp, "%d %.2f\n", account_number, withdrawal_amount);
    }
    else{
        printf("Error today's date older than the last date.");
    }

    fclose(fp);
}
