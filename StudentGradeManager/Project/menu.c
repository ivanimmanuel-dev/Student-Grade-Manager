#include <stdio.h>
#include "menu.h"
#include <string.h>

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

/* shows a single student */
void menu_showStudent(const Student* s)
{
    printf("  ID      : %d\n", s->id);
    printf("  Name    : %s\n", s->name);
    printf("  Average : %.2f\n", s->average);
    menu_printSeparator();
}

/* shows all students */
void menu_showAllStudents(const StudentDB* db)
{
    if (db->count == 0)
    {
        printf("\n  No students on record.\n");
        return;
    }

    for (int i = 0; i < db->count; i++)
        menu_showStudent(&db->students[i]);
}

/* clears input buffer */
void menu_flushInput(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* gets valid integer */
int menu_getInt(const char* prompt, int min, int max)
{
    int value;
    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%d", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput();
            return value;
        }
        menu_flushInput();
        printf("Invalid input, try again.\n");
    }
}

/* gets valid float */
float menu_getFloat(const char* prompt, float min, float max)
{
    float value;
    while (1)
    {
        printf("%s", prompt);
        if (scanf_s("%f", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput();
            return value;
        }
        menu_flushInput();
        printf("Invalid input, try again.\n");
    }
}

/* gets string input */
void menu_getString(const char* prompt, char* buf, int size)
{
    printf("%s", prompt);
    if (fgets(buf, size, stdin))
        buf[strcspn(buf, "\n")] = '\0';
}