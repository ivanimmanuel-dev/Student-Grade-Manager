#include <stdio.h>      // for input/output functions like printf, scanf
#include <string.h>     // for string handling functions like strlen, strstr
#include <ctype.h>      // for character functions like tolower
#include "menu.h"       // custom header for menu-related declarations

// prints a simple line separator
void menu_printSeparator(void)
{
    // prints a horizontal line to visually separate sections
    printf("--------------------------------------------------------\n");
}

// prints program title
void menu_printHeader(void)
{
    // prints formatted header for the program
    printf("\n========================================================\n");
    printf("           STUDENT GRADE MANAGER\n"); // title
    printf("========================================================\n\n");
}

// final menu with all options
int menu_showMain(void)
{
    // display menu options to user
    printf("\n  MENU\n");

    // print separator line
    menu_printSeparator();

    // print all available options
    printf("  [1] Add Student\n"
        "  [2] Remove Student\n"
        "  [3] Display All\n"
        "  [4] Search Student\n"
        "  [5] Record Grade\n"
        "  [6] Update Student\n"
        "  [0] Quit\n");

    // print separator again
    menu_printSeparator();

    // get user input between 0 and 6
    return menu_getInt("Enter choice: ", 0, 6);
}

// shows a single student
void menu_showStudent(const Student* s)
{
    // display student details
    printf("  ID      : %d\n", s->id);        // student ID
    printf("  Name    : %s\n", s->name);      // student name
    printf("  Average : %.2f\n", s->average); // student average grade

    // separator after each student
    menu_printSeparator();
}

// shows all students
void menu_showAllStudents(const StudentDB* db)
{
    // check if database is empty
    if (db->count == 0)
    {
        printf("\n  No students on record.\n"); // message if no students
        return;
    }

    // loop through all students and display each
    for (int i = 0; i < db->count; i++)
        menu_showStudent(&db->students[i]);
}

// clears input buffer
void menu_flushInput(void)
{
    int c;

    // keep reading characters until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

// gets valid integer
int menu_getInt(const char* prompt, int min, int max)
{
    int value;

    // infinite loop until valid input
    while (1)
    {
        printf("%s", prompt); // display prompt

        // check if input is valid integer AND within range
        if (scanf_s("%d", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput(); // clear leftover input
            return value;      // return valid value
        }

        // if invalid input
        menu_flushInput(); // clear buffer
        printf("Invalid input, try again.\n"); // error message
    }
}

// gets valid float
float menu_getFloat(const char* prompt, float min, float max)
{
    float value;

    // loop until valid float input
    while (1)
    {
        printf("%s", prompt); // display prompt

        // validate float and range
        if (scanf_s("%f", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput(); // clear buffer
            return value;      // return valid float
        }

        // invalid case
        menu_flushInput();
        printf("Invalid input, try again.\n");
    }
}

// gets string input
void menu_getString(const char* prompt, char* buf, int size)
{
    printf("%s", prompt); // display prompt

    // read string using fgets (safe input)
    if (fgets(buf, size, stdin))
        buf[strcspn(buf, "\n")] = '\0'; // remove newline character
}

// adds a student to database
void menu_addStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN]; // buffer for student name

    // get student ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // check if ID already exists
    if (db_idExists(db, id))
    {
        printf("Error: ID already exists.\n");
        return; // stop function
    }

    // get student name
    menu_getString("Enter name: ", name, MAX_NAME_LEN);

    // attempt to add student
    if (db_addStudent(db, id, name) == INVALID_VALUE)
        printf("Error adding student.\n"); // failed
    else
        printf("Student added successfully.\n"); // success
}

// removes a student
void menu_removeStudent(StudentDB* db)
{
    // get ID to remove
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // try removing student
    if (db_removeStudent(db, id) == INVALID_VALUE)
        printf("Student not found.\n"); // not found
    else
        printf("Student removed.\n");   // success
}

// displays all students
void menu_displayAll(StudentDB* db)
{
    printf("\n-- All Students --\n"); // header

    // call helper to show all students
    menu_showAllStudents(db);
}

// search by ID or name
void menu_searchStudent(StudentDB* db)
{
    printf("\n  -- Search Student --\n");

    // search options
    printf("  [1] Search by ID\n  [2] Search by Name\n");

    // get choice
    int choice = menu_getInt("Choice: ", 1, 2);

    // search by ID
    if (choice == 1)
    {
        int id = menu_getInt("Enter ID: ", 1, 999999);

        // find index
        int index = db_findById(db, id);

        // check result
        if (index == INVALID_VALUE)
            printf("Student not found.\n");
        else
            menu_showStudent(&db->students[index]);
    }
    else // search by name
    {
        char input[MAX_NAME_LEN];

        // get search string
        menu_getString("Enter name: ", input, MAX_NAME_LEN);

        int found = 0; // flag to track matches

        // loop through all students
        for (int i = 0; i < db->count; i++)
        {
            char stored[MAX_NAME_LEN], search[MAX_NAME_LEN];
            int k;

            // convert stored name to lowercase
            for (k = 0; db->students[i].name[k]; k++)
                stored[k] = (char)tolower(db->students[i].name[k]);
            stored[k] = '\0';

            // convert input to lowercase
            for (k = 0; input[k]; k++)
                search[k] = (char)tolower(input[k]);
            search[k] = '\0';

            // check if substring exists
            if (strstr(stored, search))
            {
                menu_showStudent(&db->students[i]); // display match
                found = 1;
            }
        }

        // if no match found
        if (!found)
            printf("No match found.\n");
    }
}

// record a grade
void menu_recordGrade(StudentDB* db)
{
    // get student ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // find student index
    int index = db_findById(db, id);

    // if not found
    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    // get grade input
    float grade = menu_getFloat("Enter grade: ", 0, 100);

    // record grade in database
    db_recordGrade(db, id, grade);

    // display updated average
    printf("Grade recorded. New average: %.2f\n", db->students[index].average);
}

// update student name
void menu_updateStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN]; // buffer for new name

    // get ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // find student
    int index = db_findById(db, id);

    // if not found
    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    // get new name
    menu_getString("Enter new name: ", name, MAX_NAME_LEN);

    // update name in database
    db_updateName(db, id, name);

    // confirmation message
    printf("Student updated.\n");
}