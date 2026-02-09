#include "DailyLimit.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


void daily_limit_add(char* account_number, double withdrawal_amount)
{
    FILE *fp;
    char line[256];
    char today[20];
    char file_date[20];

    /* Get today's date */
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        printf("Error getting current time\n");
        return;
    }
    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        printf("Error converting time\n");
        return;
    }
    if (strftime(today, sizeof(today), "%Y-%m-%d", tm_info) == 0) {
        printf("Error formatting date\n");
        return;
    }
    /* Open file for reading and writing */
    fp = fopen("daily_limit.txt", "r");
    if (fp == NULL) {
        fp = fopen("daily_limit.txt", "w");
        if (fp == NULL) {
            printf("Error creating daily limit file\n");
            return;
        }
        if (fp) {
            fprintf(fp, "%s\n", today);
            fprintf(fp, "%-12s %.2f\n", account_number, withdrawal_amount);
            fclose(fp);
        }
        return;
    }

    /* Read and check date */
    if (fgets(line, sizeof(line), fp) == NULL) {
        // Handle empty file...
        fclose(fp);
        fp = fopen("daily_limit.txt", "w");
        if (fp == NULL) {
            printf("Error creating daily limit file\n");
            return;
        }
        fprintf(fp, "%s\n", today);
        fprintf(fp, "%-12s %.2f\n", account_number, withdrawal_amount);
        fclose(fp);
        return;
    }

    line[strcspn(line, "\r\n")] = '\0';
    strncpy(file_date, line, sizeof(file_date) - 1);
    file_date[sizeof(file_date) - 1] = '\0';

    if (strcmp(today, file_date) != 0) {
        // Different date - recreate file...
        fclose(fp);
        fp = fopen("daily_limit.txt", "w");
        if (fp == NULL) {
            printf("Error creating daily limit file\n");
            return;
        }
        fprintf(fp, "%s\n", today);
        fprintf(fp, "%-12s %.2f\n", account_number, withdrawal_amount);
        fclose(fp);
        return;
    }

    char acc_num[1000][13];
    double amount[1000];
    int i = 0;
    int index = -1;

    while (i < 1000 && fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%12s %lf", acc_num[i], &amount[i]) == 2) {
            if (strcmp(acc_num[i], account_number) == 0) {
                index = i;
                amount[i] += withdrawal_amount;
            }
        }
        i++;
    }

/* close read file before rewriting/appending */
    fclose(fp);

    fp = fopen("daily_limit.txt", "w");
    if (fp == NULL) {
        printf("Error writing daily limit file\n");
        return;
    }

    fprintf(fp, "%s\n", today);

    for (int j = 0; j < i; j++) {
        fprintf(fp, "%-12s %.2f\n", acc_num[j], amount[j]);
    }

/* if account not found, add it */
    if (index == -1) {
        fprintf(fp, "%-12s %.2f\n", account_number, withdrawal_amount);
    }

    fclose(fp);

}

double daily_limit_check(char* account_number)
{
    FILE *fp;
    char line[256];
    char today[20];
    char file_date[20];
    /* Get today's date */
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        printf("Error getting current time\n");
        return -1;
    }
    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        printf("Error converting time\n");
        return -1;
    }
    if (strftime(today, sizeof(today), "%Y-%m-%d", tm_info) == 0) {
        printf("Error formatting date\n");
        return -1;
    }
    fp = fopen("daily_limit.txt", "r");
        if (fp == NULL) {
            printf("Error reading daily limit file\n");
            return -1;
        }
        if (fgets(line, sizeof(line), fp) == NULL) {
        // Handle empty file...
        fclose(fp);
        return 0;
    }
    line[strcspn(line, "\r\n")] = '\0';
    strncpy(file_date, line, sizeof(file_date) - 1);
    file_date[sizeof(file_date) - 1] = '\0';
    if (strcmp(today, file_date) != 0){
        fclose(fp);
        return 0;}
        while (fgets(line, sizeof(line), fp) != NULL) {
        char acc_num[13];  // 12 digits + null terminator!
        double amount;
        /* Parse the line */
        if (sscanf(line, "%12s %lf", acc_num, &amount) == 2) {
            if (strcmp(acc_num, account_number) == 0){
                fclose(fp);
                return amount;}
        }
    }
    fclose(fp);
    return 0;

}
