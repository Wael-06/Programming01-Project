#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"delete.h"



    int find_account(const char *acc_num)
    {
        FILE *file = fopen(FILENAME, "r");
        if (file == NULL)
        {
            printf("Error: Cannot open accounts file!\n");
            return 0;
        }

        char line[256];
        int found = 0;

        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line,"\n")]='\0';

            if (strlen(line) == 0)
                continue;

            // copy the main string 
            char line_copy[256];
            strcpy(line_copy, line);

            // Get account number using strtok
            char *token = strtok(line_copy, ",");
            if (token != NULL && strcmp(token, acc_num) == 0)
            {
                found = 1;

                //  display account info
                printf("ACCOUNT FOUND\n");
            
                // Account number
                printf("Account Number: %s\n", token);

                // Name
                token = strtok(NULL, ",");
                if (token)
                    printf("Name: %s\n", token);

                // Email
                token = strtok(NULL, ",");
                if (token)
                    printf("Email: %s\n", token);

                // Balance
                token = strtok(NULL, ",");
                if (token)
                {
                    float balance = atof(token);
                    printf("Balance: $%.2f\n", balance);

                    // Check if balance is zero
                    if (balance > 0)
                    {
                        printf("\nWARNING: Account has balance of $%.2f!\n", balance);
                        printf("   account must have zero balance\n");
                        fclose(file);
                        return 2; // Account found but has balance
                    }
                }

                // Mobile
                token = strtok(NULL, ",");
                if (token)
                    printf("Mobile: %s\n", token);

                // Date
                token = strtok(NULL, ",");
                if (token)
                    printf("Date Opened: %s\n", token);

                // Status
                token = strtok(NULL, ",");
                if (token)
                    printf("Status: %s\n", token);

                break;
            }
        }

        fclose(file);
        return found; // 1 if found with zero balance, 0 if not found
    }


    void delete_account()
    {
        char acc_num[12];
        char confirm[10];
        printf("Enter Account Number to delete: ");
        fgets(acc_num, sizeof(acc_num), stdin);
        acc_num[strcspn(acc_num, "\n")] = '\0';
        int result = find_account(acc_num);
        if (result == 0)
        {
            printf("\n ERROR: Account '%s' not found!\n", acc_num);
            return;
        }

        if (result == 2)
        {
            printf("\n Cannot delete account with non-zero balance\n");
            return;
        }

        printf("\nAre you sure you want to DELETE this account? (y/n)(y=yes,n=no): ");
        fgets(confirm, sizeof(confirm), stdin);
        confirm[strcspn(confirm, "\n")] = '\0';
        if (confirm[0] != 'y' && confirm[0] != 'Y')
        {
            printf("\nDeletion cancelled.\n");
            return;
        }

        //delete account from file
        FILE *original = fopen(FILENAME, "r");
        FILE *temp = fopen(TEMP_FILE, "w");

        if (original == NULL || temp == NULL)
        {
            printf("Error: Cannot open files!\n");
            if (original)
                fclose(original);
            if (temp)
                fclose(temp);
            return;
        }
        char line[256];
        int deleted = 0;

        while (fgets(line, sizeof(line), original))
        {
            line[strcspn(line,"\n")]='\0';

            if (strlen(line) == 0)
            {
                fprintf(temp, "\n");
                continue;
            }

            // Check if this is the account to delete
            char line_copy[256];
            strcpy(line_copy, line);

            char *token = strtok(line_copy, ",");
            if (token != NULL && strcmp(token, acc_num) == 0)
            {
                // Skip this line (don't write it to temp file)
                deleted = 1;
                printf("\nAccount '%s' marked for deletion...\n", acc_num);
            }
            else
            {
                // Write other accounts to temp file
                fprintf(temp, "%s\n", line);
            }
        }

        fclose(original);
        fclose(temp);

        // Replace original file
        if (deleted)
        {
            remove(FILENAME);
            rename(TEMP_FILE, FILENAME);
            printf("\nSUCCESS Account '%s' deleted!\n", acc_num);
        }
        else
        {
            remove(TEMP_FILE);
            printf("\nERROR Failed to delete account!\n");
        }
    }
    
