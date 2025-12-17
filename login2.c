#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sizefile(char *fname)
{
    FILE *fptr = fopen(fname, "rb");
    if (fptr == NULL)
        return -1;
    fseek(fptr, 0, SEEK_END);
    int size = ftell(fptr);
    fclose(fptr);
    return size;
}

int login()
{
    FILE *fptr = fopen("users.txt", "r");
    if (!fptr)
    {
        return -1;
    }

    char file_username[50], file_password[10];
    char input_username[50], input_password[10];
    char line[100];

    int attempts = 0;

    while (attempts < 3)
    {
        printf("Enter Username: ");
        fgets(input_username, sizeof(input_username), stdin);
        input_username[strcspn(input_username, "\n")] = '\0';
        
        printf("Enter Password: ");
        fgets(input_password, sizeof(input_password), stdin);
        input_password[strcspn(input_password, "\n")] = '\0';

        rewind(fptr);

        int success = 0;

        while (fgets(line, sizeof(line), fptr))
        {
            line[strcspn(line, "\n")] = 0;

            sscanf(line, "%49s %9s", file_username, file_password);

            if (strcmp(input_username, file_username) == 0 &&strcmp(input_password, file_password) == 0)
            {
                success = 1;
                break;
            }
        }

        if (success)
        {
            printf("You have logged in successfully\n");
            fclose(fptr);
            return 1;
        }

        attempts++;

        if (attempts == 2)
            printf("This is your last trial\n");
        else if (attempts < 3)
            printf("Incorrect, try again\n");
    }

    printf("Sorry, You failed login\n");
    fclose(fptr);
    return 0;
}


int main()
{
    login();
    return 0;
}