#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    Date date_of_opening;
    char status[10];
} Account;

float stof(const char *str)
{
    float result = 0.0f, fraction = 0.0f;
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

void clean_status_string(char *status)
{
    int i = 0;
    while (status[i] == ' ')
        i++;
    if (i > 0)
    {
        int j = 0;
        while (status[i] != '\0')
            status[j++] = status[i++];
        status[j] = '\0';
    }
    int len = strlen(status);
    while (len > 0 && (status[len - 1] == ' ' || status[len - 1] == '\n' || status[len - 1] == '\r'))
        status[--len] = '\0';
}

void printwithlines(Account account)
{
    printf("Account Number:%10s\n", account.account_number);
    printf("Name: %s\n", account.name);
    printf("E-mail: %s\n", account.email);
    printf("Balance: %.2f$\n", account.balance);
    printf("Mobile: %s\n", account.mobile);
    printf("Date Opened: ");
    int m = account.date_of_opening.month;
    int y = account.date_of_opening.year;
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
    char clean_status[10];
    strcpy(clean_status, account.status);
    clean_status_string(clean_status);
    printf("Status: %s\n", clean_status);
}

int search(const char *input_search, int *line_number, Account *acc)
{
    FILE *fptr = fopen("accounts.txt", "r");
    if (!fptr)
        return 0;
    char buf[200];
    int found = 0;
    *line_number = 0;
    while (fgets(buf, sizeof(buf), fptr))
    {
        (*line_number)++;
        if (strlen(buf) < 5)
            continue;
        char line_copy[200];
        strcpy(line_copy, buf);
        char *token = strtok(line_copy, ",\n\r");
        if (!token)
            continue;
        if (strcmp(token, input_search) == 0)
        {
            strcpy(acc->account_number, token);
            token = strtok(NULL, ",\n\r");
            if (token)
                strcpy(acc->name, token);
            token = strtok(NULL, ",\n\r");
            if (token)
                strcpy(acc->email, token);
            token = strtok(NULL, ",\n\r");
            if (token)
                acc->balance = stof(token);
            token = strtok(NULL, ",\n\r");
            if (token)
                strcpy(acc->mobile, token);
            token = strtok(NULL, ",\n\r");
            if (token)
                sscanf(token, "%d-%d", &acc->date_of_opening.month, &acc->date_of_opening.year);
            token = strtok(NULL, ",\n\r");
            if (token)
            {
                strcpy(acc->status, token);
                clean_status_string(acc->status);
            }
            found = 1;
            break;
        }
    }
    fclose(fptr);
    return found;
}

void update_status_in_file(int line_number, const char *new_status)
{
    FILE *fptr = fopen("accounts.txt", "r");
    if (!fptr)
        return;
    char lines[100][200];
    int total_lines = 0;
    while (fgets(lines[total_lines], sizeof(lines[0]), fptr) && total_lines < 100)
        total_lines++;
    fclose(fptr);
    if (line_number > 0 && line_number <= total_lines)
    {
        char *tokens[7], line_copy[200];
        strcpy(line_copy, lines[line_number - 1]);
        int token_count = 0;
        char *token = strtok(line_copy, ",\n\r");
        while (token && token_count < 7)
        {
            tokens[token_count++] = token;
            token = strtok(NULL, ",\n\r");
        }
        if (token_count >= 7)
            sprintf(lines[line_number - 1], "%s,%s,%s,%s,%s,%s, %s\n", tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], new_status);
    }
    fptr = fopen("accounts.txt", "w");
    if (!fptr)
        return;
    for (int i = 0; i < total_lines; i++)
        fprintf(fptr, "%s", lines[i]);
    fclose(fptr);
}

void change_status()
{
    char input[12];
    int line_number;
    Account acc;
    printf("Input Account Number to Change Status: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';
    int found = search(input, &line_number, &acc);
    if (found)
    {
        printf("\nAccount Found:\n");
        printwithlines(acc);
        char selection[20];
        printf("\nPlease select the desired action:\n1. Activate\n2. Deactivate\nEnter Selection (1 or 2): ");
        fgets(selection, sizeof(selection), stdin);
        selection[strcspn(selection, "\n")] = '\0';
        clean_status_string(selection);
        char current_status_lower[10];
        strcpy(current_status_lower, acc.status);
        for (int i = 0; current_status_lower[i]; i++)
            current_status_lower[i] = tolower(current_status_lower[i]);
        int wants_activate = 0, wants_deactivate = 0;
        if (strcmp(selection, "1") == 0 || tolower(selection[0]) == 'a' || strcasecmp(selection, "activate") == 0)
            wants_activate = 1;
        else if (strcmp(selection, "2") == 0 || tolower(selection[0]) == 'd' || strcasecmp(selection, "deactivate") == 0)
            wants_deactivate = 1;
        else
        {
            printf("\nIncorrect input. Please enter 1 or 2.\n");
            return;
        }
        if (wants_activate)
        {
            if (strcmp(current_status_lower, "active") == 0)
            {
                printf("\nAttention: This account is already Active.\nNo changes made.\n");
            }
            else
            {
                update_status_in_file(line_number, "active");
                printf("\nAccount activated successfully!\n");
            }
        }
        else if (wants_deactivate)
        {
            if (strcmp(current_status_lower, "inactive") == 0)
            {
                printf("\nAttention: This account is already Inactive.\nNo changes made.\n");
            }
            else
            {
                update_status_in_file(line_number, "inactive");
                printf("\nAccount deactivated successfully!\nNote: Inactive accounts cannot make financial transactions.\n");
            }
        }
    }
    else
        printf("\nAccount not found.\n");
}

int main()
{
    change_status();
    return 0;
}
