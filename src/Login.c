#include "Login.h"
#include "helper1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Color.h"
int login()
{
    FILE *fptr = fopen("users.txt", "r");
    if (!fptr)
    {
        printf(RED "Opening file failed" RESET);
        exit(-1);
    }

    char file_username[50], file_password[10];
    char input_username[50], input_password[10];
    char line[100];

    int attempts = 0;

    // Add login header
    printf(CYAN "\n=== BANK LOGIN ===\n" RESET);

    while (attempts < 3)
    {
        printf(YELLOW "Enter Username: " RESET);
        scanf("%s",input_username);
        input_username[strcspn(input_username, "\n")] = '\0';

        printf(YELLOW "Enter Password: " RESET);
        scanf("%s",input_password);
        input_password[strcspn(input_password, "\n")] = '\0';
        clear_input_buffer();
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
            printf(GREEN "\nYou have logged in successfully\n" RESET);
            fclose(fptr);
            return 1;
        }

        attempts++;

        if (attempts == 2)
            printf(YELLOW "This is your last trial\n" RESET);
        else if (attempts < 3)
            printf(RED "Incorrect, try again\n" RESET);
    }

    printf(RED "Sorry, You failed login\n" RESET);
    fclose(fptr);
    exit(-1);
}
