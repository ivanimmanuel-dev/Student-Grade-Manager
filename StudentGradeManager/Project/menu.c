#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

/* final menu with all options */
int menu_showMain(void)
{
    printf("\n  MENU\n");
    menu_printSeparator();
    printf("  [1] Add Student\n"
        "  [2] Remove Student\n"
        "  [3] Display All\n"
        "  [4] Search Student\n"
        "  [5] Record Grade\n"
        "  [6] Update Student\n"
        "  [0] Quit\n");
    menu_printSeparator();

    return menu_getInt("Enter choice: ", 0, 6);
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

/* adds a student to database */
void menu_addStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN];
    int id = menu_getInt("Enter ID: ", 1, 999999);

    if (db_idExists(db, id))
    {
        printf("Error: ID already exists.\n");
        return;
    }

    menu_getString("Enter name: ", name, MAX_NAME_LEN);

    if (db_addStudent(db, id, name) == INVALID_VALUE)
        printf("Error adding student.\n");
    else
        printf("Student added successfully.\n");
}

/* removes a student */
void menu_removeStudent(StudentDB* db)
{
    int id = menu_getInt("Enter ID: ", 1, 999999);

    if (db_removeStudent(db, id) == INVALID_VALUE)
        printf("Student not found.\n");
    else
        printf("Student removed.\n");
}

/* displays all students */
void menu_displayAll(StudentDB* db)
{
    printf("\n-- All Students --\n");
    menu_showAllStudents(db);
}

/* search by ID or name */
void menu_searchStudent(StudentDB* db)
{
    printf("\n  -- Search Student --\n");
    printf("  [1] Search by ID\n  [2] Search by Name\n");

    int choice = menu_getInt("Choice: ", 1, 2);

    if (choice == 1)
    {
        int id = menu_getInt("Enter ID: ", 1, 999999);
        int index = db_findById(db, id);

        if (index == INVALID_VALUE)
            printf("Student not found.\n");
        else
            menu_showStudent(&db->students[index]);
    }
    else
    {
        char input[MAX_NAME_LEN];
        menu_getString("Enter name: ", input, MAX_NAME_LEN);

        int found = 0;

        for (int i = 0; i < db->count; i++)
        {
            char stored[MAX_NAME_LEN], search[MAX_NAME_LEN];
            int k;

            for (k = 0; db->students[i].name[k]; k++)
                stored[k] = (char)tolower(db->students[i].name[k]);
            stored[k] = '\0';

            for (k = 0; input[k]; k++)
                search[k] = (char)tolower(input[k]);
            search[k] = '\0';

            if (strstr(stored, search))
            {
                menu_showStudent(&db->students[i]);
                found = 1;
            }
        }

        if (!found)
            printf("No match found.\n");
    }
}

/* record a grade */
void menu_recordGrade(StudentDB* db)
{
    int id = menu_getInt("Enter ID: ", 1, 999999);
    int index = db_findById(db, id);

    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    float grade = menu_getFloat("Enter grade: ", 0, 100);
    db_recordGrade(db, id, grade);

    printf("Grade recorded. New average: %.2f\n", db->students[index].average);
}

/* update student name */
void menu_updateStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN];
    int id = menu_getInt("Enter ID: ", 1, 999999);
    int index = db_findById(db, id);

    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    menu_getString("Enter new name: ", name, MAX_NAME_LEN);
    db_updateName(db, id, name);

    printf("Student updated.\n");
}