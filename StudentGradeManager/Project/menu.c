#include <stdio.h>
#include "menu.h"

/* prints a simple line separator */
void menu_printSeparator(void)
{
    printf("--------------------------------------------------------\n");
}

/* prints program title */
void menu_printHeader(void)
{
    printf("\n========================================================\n");
    printf("           STUDENT GRADE MANAGER\n");
    printf("========================================================\n\n");
}

/* basic menu (will expand later) */
int menu_showMain(void)
{
    printf("\n  MENU\n");
    menu_printSeparator();
    printf("  [1] Add Student\n");
    printf("  [0] Quit\n");
    menu_printSeparator();

    return 0; // temporary return
}