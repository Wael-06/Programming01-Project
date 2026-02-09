#include "DailyLimit.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Color.h"

void add_daily_limit(char* account_number, float withdrawal_amount)
{
    FILE *fp;
    char line[256];
    char today[20];
    char file_date[20];

    /* Get today's date */
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        printf(RED "Error getting current time\n" RESET);
        return;
    }
    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        printf(RED "Error converting time\n" RESET);
        return;
    }
    if (strftime(today, sizeof(today), "%Y-%m-%d", tm_info) == 0) {
        printf(RED "Error formatting date\n" RESET);
        return;
    }
    /* Open file for reading and writing */
    fp = fopen("daily_limit.txt", "r");
    if (fp == NULL) {
        fp = fopen("daily_limit.txt", "w");
        if (fp == NULL) {
            printf(RED "Error creating daily limit file\n" RESET);
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
            printf(RED "Error creating daily limit file\n" RESET);
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
            printf(RED "Error creating daily limit file\n" RESET);
            return;
        }
        fprintf(fp, "%s\n", today);
        fprintf(fp, "%-12s %.2f\n", account_number, withdrawal_amount);
        fclose(fp);
        return;
    }

    char acc_num[1000][13];
    float amount[1000];
    int i = 0;
    int index = -1;

    while (i < 1000 && fgets(line, sizeof(line), fp) != NULL) {
        if (sscanf(line, "%12s %f", acc_num[i], &amount[i]) == 2) {
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
        printf(RED "Error writing daily limit file\n" RESET);
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

float daily_limit_check(char* account_number)
{
    FILE *fp;
    char line[256];
    char today[20];
    char file_date[20];
    /* Get today's date */
    time_t t = time(NULL);
    if (t == (time_t)-1) {
        printf(RED "Error getting current time\n" RESET);
        return -1;
    }
    struct tm *tm_info = localtime(&t);
    if (tm_info == NULL) {
        printf(RED "Error converting time\n" RESET);
        return -1;
    }
    if (strftime(today, sizeof(today), "%Y-%m-%d", tm_info) == 0) {
        printf(RED "Error formatting date\n" RESET);
        return -1;
    }
    fp = fopen("daily_limit.txt", "r");
        if (fp == NULL) {
            printf(YELLOW "Error reading daily limit file\n" RESET);
            return 0;
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
        char acc_num[11];  // 12 digits + null terminator!
        float amount;
        /* Parse the line */
        if (sscanf(line, "%10s %f", acc_num, &amount) == 2) {
            if (strcmp(acc_num, account_number) == 0){
                fclose(fp);
                if(amount<0||amount>50000){
                    printf(RED "Error Daily limit invalid" RESET);
                    return -1;
                }
                return amount;}
        }
    }
    fclose(fp);
    return 0;

}
