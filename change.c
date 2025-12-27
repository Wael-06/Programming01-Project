#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "change.h"

// Convert string to float
float stof(const char *str) {
    float result = 0.0f, fraction = 0.0f;
    int divisor = 1;
    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }
    if (*str == '.') {
        str++;
        while (*str >= '0' && *str <= '9') {
            fraction = fraction * 10 + (*str - '0');
            divisor *= 10;
            str++;
        }
    }
    return result + fraction / divisor;
}

// Clean spaces and newlines from status string
void clean_status_string(char *status) {
    int i = 0;
    while (status[i] == ' ')
        i++;
    if (i > 0) {
        int j = 0;
        while (status[i] != '\0')
            status[j++] = status[i++];
        status[j] = '\0';
    }
    int len = strlen(status);
    while (len > 0 && (status[len - 1] == ' ' || status[len - 1] == '\n' || status[len - 1] == '\r'))
        status[--len] = '\0';
}

// Print account info neatly
void printwithlines(Account account) {
    printf("Account Number: %s\n", account.account_number);
    printf("Name: %s\n", account.name);
    printf("E-mail: %s\n", account.email);
    printf("Balance: %.2f$\n", account.balance);
    printf("Mobile: %s\n", account.mobile);

    int m = account.date_of_opening.month;
    int y = account.date_of_opening.year;
    if (m > 12) {
        while (m > 12) {
            m -= 12;
            y++;
        }
    } else if (m <= 0) {
        printf("Date Opened: Invalid month\n");
        return;
    }

    printf("Date Opened: ");
    const char *months[] = {"January","February","March","April","May","June",
                            "July","August","September","October","November","December"};
    printf("%s %d\n", months[m-1], y);

    char clean_status[10];
    strcpy(clean_status, account.status);
    clean_status_string(clean_status);
    printf("Status: %s\n", clean_status);
}

// Search for account by number
int search(const char *input_search, int *line_number, Account *acc) {
    FILE *fptr = fopen("accounts.txt", "r");
    if (!fptr) return 0;

    char buf[200];
    int found = 0;
    *line_number = 0;

    while (fgets(buf, sizeof(buf), fptr)) {
        (*line_number)++;
        if (strlen(buf) < 5) continue;

        char line_copy[200];
        strcpy(line_copy, buf);

        char *token = strtok(line_copy, ",\n\r");
        if (!token) continue;

        if (strcmp(token, input_search) == 0) {
            strcpy(acc->account_number, token);
            token = strtok(NULL, ",\n\r"); if (token) strcpy(acc->name, token);
            token = strtok(NULL, ",\n\r"); if (token) strcpy(acc->email, token);
            token = strtok(NULL, ",\n\r"); if (token) acc->balance = stof(token);
            token = strtok(NULL, ",\n\r"); if (token) strcpy(acc->mobile, token);
            token = strtok(NULL, ",\n\r"); if (token) sscanf(token, "%d-%d", &acc->date_of_opening.month, &acc->date_of_opening.year);
            token = strtok(NULL, ",\n\r"); if (token) { strcpy(acc->status, token); clean_status_string(acc->status); }

            found = 1;
            break;
        }
    }

    fclose(fptr);
    return found;
}

// Update account status in file
void update_status_in_file(int line_number, const char *new_status) {
    FILE *fptr = fopen("accounts.txt", "r");
    if (!fptr) return;

    char lines[100][200];
    int total_lines = 0;
    while (fgets(lines[total_lines], sizeof(lines[0]), fptr) && total_lines < 100)
        total_lines++;
    fclose(fptr);

    if (line_number > 0 && line_number <= total_lines) {
        char *tokens[7], line_copy[200];
        strcpy(line_copy, lines[line_number - 1]);
        int token_count = 0;

        char *token = strtok(line_copy, ",\n\r");
        while (token && token_count < 7) {
            tokens[token_count++] = token;
            token = strtok(NULL, ",\n\r");
        }

        if (token_count >= 7)
            sprintf(lines[line_number - 1], "%s,%s,%s,%s,%s,%s,%s\n",
                    tokens[0], tokens[1], tokens[2], tokens[3],
                    tokens[4], tokens[5], new_status);
    }

    fptr = fopen("accounts.txt", "w");
    if (!fptr) return;
    for (int i = 0; i < total_lines; i++)
        fprintf(fptr, "%s", lines[i]);
    fclose(fptr);
}

// Main function to change status
void change_status() {
    char input[12];
    int line_number;
    Account acc;

    printf("Input Account Number to Change Status: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    int found = search(input, &line_number, &acc);
    if (!found) {
        printf("\nAccount not found.\n");
        return;
    }

    printf("\nAccount Found:\n");
    printwithlines(acc);

    char selection[20];
    printf("\nSelect Action:\n1. Activate\n2. Deactivate\nEnter (1 or 2): ");
    fgets(selection, sizeof(selection), stdin);
    selection[strcspn(selection, "\n")] = '\0';
    clean_status_string(selection);

    char current_status_lower[10];
    strcpy(current_status_lower, acc.status);
    for (int i = 0; current_status_lower[i]; i++)
        current_status_lower[i] = tolower(current_status_lower[i]);

    int wants_activate = 0, wants_deactivate = 0;
    if (strcmp(selection, "1") == 0 || tolower(selection[0]) == 'a')
        wants_activate = 1;
    else if (strcmp(selection, "2") == 0 || tolower(selection[0]) == 'd')
        wants_deactivate = 1;
    else {
        printf("\nIncorrect input. Enter 1 or 2.\n");
        return;
    }

    if (wants_activate) {
        if (strcmp(current_status_lower, "active") == 0)
            printf("\nAlready Active. No changes made.\n");
        else {
            update_status_in_file(line_number, "active");
            printf("\nAccount activated successfully!\n");
        }
    } else if (wants_deactivate) {
        if (strcmp(current_status_lower, "inactive") == 0)
            printf("\nAlready Inactive. No changes made.\n");
        else {
            update_status_in_file(line_number, "inactive");
            printf("\nAccount deactivated successfully!\nNote: Inactive accounts cannot perform transactions.\n");
        }
    }
}
