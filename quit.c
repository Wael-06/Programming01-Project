#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void quit() {
    printf("\nPress any key to exit...");
    _getch();
    exit(0);
}

int main() {
    quit();
    return 0;
}