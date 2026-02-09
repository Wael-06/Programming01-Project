#include "AdvancedSearch.h"
#include "helper1.h"
#include "helper2.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Color.h"
void Advanced_Search(const Account* accounts,const int account_count)
{
    char keyword[50];
    printf(CYAN "\n=== ADVANCED SEARCH ===\n" RESET);
    printf(YELLOW "Enter keyword: " RESET);
    if (fgets(keyword, sizeof(keyword), stdin)) {
    keyword[strcspn(keyword, "\n")] = '\0';
    }
    capitalize_words(keyword);
    printf(CYAN "Search Results:\n" RESET);
    int found=0;
    for(int i=0;i<account_count;i++){
    char* result=strstr(accounts[i].name,keyword);
    if(result!=NULL){
            found = 1;
            print_account_formatted(accounts+i);
            }
    }
    if(!found)
        printf(YELLOW "No matches are found\n" RESET);

}
