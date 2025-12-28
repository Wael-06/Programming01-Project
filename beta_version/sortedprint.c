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

int count(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return -1;

    int count = 0;
    char buffer[200];

    while (fgets(buffer, sizeof(buffer), fp))
        count++;

    fclose(fp);
    return count;
}

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

void printwithlines(Account account)
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
    printf(" %d\n", y);
    if (strcmp(account.status, " active") == 0)
        printf("Status: Active\n");
    else
        printf("Status: Inactive\n");

    printf("\n");
}

void reverese(Account arr[], int n)
{
    Account temp;
    int end = n - 1;
    for (int i = 0; i < n / 2; i++)
    {
        temp = arr[i];
        arr[i] = arr[end - i];
        arr[end - i] = temp;
    }
}

int load(Account **out)
{

    int NOA = count("accounts.txt"); // NOA:number of accounts
    if (NOA <= 0)
    {
        return -1;
        exit(-1);
    }
    FILE *fptr = fopen("accounts.txt", "r");

    if (fptr == NULL)
    {
        printf("couldn't open accounts files");
        return -1;
        exit(-1);
    }

    Account *acc;
    acc = malloc(NOA * sizeof(Account));
    if (acc == NULL)
    {
        printf("Memory allocation failed.\n");
        fclose(fptr);
        return -1;
    }

    char line[200];
    int counter = 0, i;

    while (counter < NOA && fgets(line, sizeof(line), fptr) != NULL)
    {
        char *token;

        token = strtok(line, ",\n\r");
        if (token == NULL)
            break;
        strncpy(acc[counter].account_number, token, sizeof(acc[counter].account_number));
        acc[counter].account_number[sizeof(acc[counter].account_number) - 1] = '\0';

        token = strtok(NULL, ",\n\r");
        strncpy(acc[counter].name, token, sizeof(acc[counter].name));
        acc[counter].name[sizeof(acc[counter].name) - 1] = '\0';

        token = strtok(NULL, ",\n\r");
        strncpy(acc[counter].email, token, sizeof(acc[counter].email));
        acc[counter].email[sizeof(acc[counter].email) - 1] = '\0';

        token = strtok(NULL, ",\n\r");
        acc[counter].balance = stof(token);

        token = strtok(NULL, ",\n\r");
        strncpy(acc[counter].mobile, token, sizeof(acc[counter].mobile));
        acc[counter].mobile[sizeof(acc[counter].mobile) - 1] = '\0';

        token = strtok(NULL, ",\n\r");
        sscanf(token, "%d-%d", &acc[counter].date_of_openeing.month, &acc[counter].date_of_openeing.year);

        token = strtok(NULL, ",\n\r");
        strncpy(acc[counter].status, token, sizeof(acc[counter].status));
        acc[counter].status[sizeof(acc[counter].status) - 1] = '\0';
        counter++;
    }
    fclose(fptr);
    *out = acc;
    return counter;
}

void mergeByName(Account arr[], int l, int m, int r)
{
    int i = l, j = m + 1, counter = 0;
    Account temp[r - l + 1];

    while (i <= m && j <= r)
    {
        if (strcmp(arr[i].name, arr[j].name) <= 0)
            temp[counter++] = arr[i++];
        else
            temp[counter++] = arr[j++];
    }
    while (i <= m)
        temp[counter++] = arr[i++];
    while (j <= r)
        temp[counter++] = arr[j++];

    for (i = l, counter = 0; i <= r; i++, counter++)
        arr[i] = temp[counter];
}

void sortByName(Account arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        sortByName(arr, l, m);
        sortByName(arr, m + 1, r);
        mergeByName(arr, l, m, r);
    }
}

void mergeByDate(Account arr[], int l, int m, int r)
{
    int i = l, j = m + 1, counter = 0;
    Account temp[r - l + 1];

    while (i <= m && j <= r)
    {
        if ((arr[i].date_of_openeing.year < arr[j].date_of_openeing.year) ||
            (arr[i].date_of_openeing.year == arr[j].date_of_openeing.year && arr[i].date_of_openeing.month <= arr[j].date_of_openeing.month))
            temp[counter++] = arr[i++];
        else
            temp[counter++] = arr[j++];
    }
    while (i <= m)
        temp[counter++] = arr[i++];
    while (j <= r)
        temp[counter++] = arr[j++];

    for (i = l, counter = 0; i <= r; i++, counter++)
        arr[i] = temp[counter];
}

void sortByDate(Account arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        sortByDate(arr, l, m);
        sortByDate(arr, m + 1, r);
        mergeByDate(arr, l, m, r);
    }
}

void mergeByBalance(Account arr[], int l, int m, int r)
{
    int i = l, j = m + 1, counter = 0;
    Account temp[r - l + 1];

    while (i <= m && j <= r)
    {
        if (arr[i].balance <= arr[j].balance)
            temp[counter++] = arr[i++];
        else
            temp[counter++] = arr[j++];
    }
    while (i <= m)
        temp[counter++] = arr[i++];
    while (j <= r)
        temp[counter++] = arr[j++];

    for (i = l, counter = 0; i <= r; i++, counter++)
        arr[i] = temp[counter];
}

void sortByBalance(Account arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        sortByBalance(arr, l, m);
        sortByBalance(arr, m + 1, r);
        mergeByBalance(arr, l, m, r);
    }
}

void sortByStatus(Account arr[], int n)
{
    int i, j, minIndex;
    Account temp;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        for (j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j].status, arr[minIndex].status) < 0)
            {
                minIndex = j;
            }
        }

        if (minIndex != i)
        {
            temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void sortedprint()
{
    char input[9];

    printf("Select the sorting way for the accounts.\n");
    printf("1. Names\n");
    printf("2. Dates\n");
    printf("3. Balance\n");
    printf("4. Status\n");
    printf("Enter your choice (1-4): ");

    fgets(input, 8, stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "1") == 0 || strcmp(input, "Names") == 0 || strcmp(input, "names") == 0)
    {
        Account *accounts = NULL;
        int n = load(&accounts);
        if (n <= 0)
        {
            printf("Failed to load accounts\n");
        }
        sortByName(accounts, 0, n);
        for (int i = 0; i < n; i++)
            printwithlines(accounts[i]);
        free(accounts);
    }

    else if (strcmp(input, "2") == 0 || strcmp(input, "Dates") == 0 || strcmp(input, "dates") == 0)
    {
        Account *accounts = NULL;
        int n = load(&accounts);
        if (n <= 0)
        {
            printf("Failed to load accounts\n");
        }
        sortByDate(accounts, 0, n);
        char order[11];
        printf("Please specify whether the accounts should be sorted by date in: \n1.ascending order \n2.descending order\n");
        printf("Enter your choice (1-2): ");
        fgets(order, 10, stdin);
        order[strcspn(order, "\n")] = '\0';
        if (strcmp(order, "2") == 0 || strcmp(order, "descending") == 0 || strcmp(order, "descend") == 0 || strcmp(order, "Descending") == 0 || strcmp(order, "Descend") == 0)
        {
            reverese(accounts, n);
        }
        for (int i = 0; i < n; i++)
            printwithlines(accounts[i]);
        free(accounts);
    }

    else if (strcmp(input, "3") == 0 || strcmp(input, "Balance") == 0 || strcmp(input, "balance") == 0)
    {
        Account *accounts = NULL;
        int n = load(&accounts);
        if (n <= 0)
        {
            printf("Failed to load accounts\n");
        }
        sortByBalance(accounts, 0, n);
        char order[11];
        printf("Please specify whether the accounts should be sorted by balance in: \n1.ascending order \n2.descending order\n");
        printf("Enter your choice (1-2): ");
        fgets(order, 10, stdin);
        order[strcspn(order, "\n")] = '\0';
        if (strcmp(order, "2") == 0 || strcmp(order, "descending") == 0 || strcmp(order, "descend") == 0 || strcmp(order, "Descending") == 0 || strcmp(order, "Descend") == 0)
        {
            reverese(accounts, n);
        }
        for (int i = 0; i < n; i++)
            printwithlines(accounts[i]);
        free(accounts);
    }

    else if (strcmp(input, "4") == 0 || strcmp(input, "Status") == 0 || strcmp(input, "status") == 0)
    {
        Account *accounts = NULL;
        int n = load(&accounts);
        if (n <= 0)
        {
            printf("Failed to load accounts\n");
        }
        sortByStatus(accounts, n);
        char order[11];
        printf("Please specify which accounts to display: \n1.active accounts \n2.inactive accounts\n");
        printf("Enter your choice (1-3): ");
        fgets(order, 10, stdin);
        order[strcspn(order, "\n")] = '\0';
        if (strcmp(order, "2") == 0 || strcmp(order, "descending") == 0 || strcmp(order, "descend") == 0 || strcmp(order, "Descending") == 0 || strcmp(order, "Descend") == 0)
        {
            reverese(accounts, n);
        }
        for (int i = 0; i < n; i++)
            printwithlines(accounts[i]);
        free(accounts);
    }

    else
    {
        printf("Invalid Inputs");
    }
}

int main()
{
    sortedprint();
    return 0;
}