/*==========================================================================================
 *              MENU: Functions for displaying menu and handling user input
 *                              Author: Keshav Kumar Markan
 *==========================================================================================*/


#include <stdio.h>      // for input/output functions like printf, scanf
#include <string.h>     // for string handling functions like strlen, strstr
#include <ctype.h>      // for character functions like tolower
#include "student.h"    // custom header for student database declarations
#include "menu.h"       // custom header for menu-related declarations

// prints a simple line separator
void menu_printSeparator(void)
{
    printf("--------------------------------------------------------\n");
}

// prints program title
void menu_printHeader(void)
{
    printf("\n========================================================\n");
    printf("           STUDENT GRADE MANAGER\n");
    printf("========================================================\n\n");
}

// final menu with all options
int menu_showMain(void)
{
    printf("\n  MENU\n");

    // prints a separator line for better readability
	menu_printSeparator();

    // prints all available options
    printf("  [1] Add Student\n""  [2] Remove Student\n""  [3] Display All\n""  [4] Search Student\n""  [5] Record Grade\n""  [6] Update Student\n""  [0] Quit\n");

    // prints another separator line after the options
	menu_printSeparator(); 

    // gets and returns user's choice, ensuring it's between 0 and 6
	return menu_getInt("Enter choice: ", 0, 6); 
}

// displays details of a single student
void menu_showStudent(const Student* s)
{
    // prints a separator line for better readability
    menu_printSeparator();

    // displays student details
    printf("  ID      : %d\n", s->id);        // student ID
    printf("  Name    : %s\n", s->name);      // student name
    printf("  Average : %.2f\n", s->average); // student average grade
    printf("  Grades  : ");
	if (s->gradeCount == 0)                             // if no grades recorded, print "none"
    {
        printf("none\n");
    }
	else                                                // if grades exist, print them separated by commas
    {
        for (int i = 0; i < s->gradeCount; i++)
        {
            printf("%.2f", s->grades[i]);
            if (i < s->gradeCount - 1) printf(", ");
        }
        printf("\n");
    }

	// prints a separator after each student for better readability
    menu_printSeparator();
}

// displays all students in the database
void menu_showAllStudents(const StudentDB* db)
{
    // checks if database is empty
    if (db->count == 0)
    {
        printf("\n  No students on record.\n"); // message if no students
        return;
    }

    // loops through all students and display each
    for (int i = 0; i < db->count; i++)
    {
        menu_showStudent(&db->students[i]);
    }
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
        printf("%s", prompt); // displays prompt

        // checks if input is valid integer AND within range
        if (scanf_s("%d", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput(); // clears leftover input
            return value;      // returns valid value
        }

		menu_flushInput();  // clears invalid input
        printf("Invalid input, try again.\n"); // error message
    }
}

// gets valid float
float menu_getFloat(const char* prompt, float min, float max)
{
    float value;

    // loops until valid float input
    while (1)
    {
        printf("%s", prompt); // displays prompt

        // validates float and range
        if (scanf_s("%f", &value) == 1 && value >= min && value <= max)
        {
            menu_flushInput(); // clears buffer
            return value;      // returns valid float
        }

        // invalid case
        menu_flushInput();
        printf("Invalid input, try again.\n");
    }
}

// gets string input
void menu_getString(const char* prompt, char* buf, int size)
{
    printf("%s", prompt);               // displays prompt

    // reads string using fgets (safe input)
    if (fgets(buf, size, stdin))
    {
        buf[strcspn(buf, "\n")] = '\0'; // remove newline character
    }
}

// adds a student to database
void menu_addStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN]; // buffer for student name

    // get student ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // checks if ID already exists
    if (db_idExists(db, id))
    {
        printf("Error: ID already exists.\n");
        return; // stop function
    }

    // gets student name
    menu_getString("Enter name: ", name, MAX_NAME_LEN);

    // attempts to add student
    if (db_addStudent(db, id, name) == INVALID_VALUE)
    {
        printf("Error adding student.\n");          // failed
    }
    else
    {
        printf("Student added successfully.\n");    // success
    }
}

// removes a student
void menu_removeStudent(StudentDB* db)
{
    // gets ID to remove
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // tries removing student
    if (db_removeStudent(db, id) == INVALID_VALUE)
    {
        printf("Student not found.\n"); // not found
    }
    else
    {
        printf("Student removed.\n");   // success
    }
}

// displays all students
void menu_displayAll(StudentDB* db)
{
    printf("\n-- All Students --\n"); // header

    // calls helper to show all students
    menu_showAllStudents(db);
}

// search by ID or name
void menu_searchStudent(StudentDB* db)
{
    printf("\n  -- Search Student --\n");

    // prints a separator line for better readability
    menu_printSeparator();

    // search options
    printf("  [1] Search by ID\n  [2] Search by Name\n");

    // gets choice
    int choice = menu_getInt("Choice: ", 1, 2);

    // search by ID
    if (choice == 1)
    {
        int id = menu_getInt("Enter ID: ", 1, 999999);

        // finds index
        int index = db_findById(db, id);

        // checks result
        if (index == INVALID_VALUE)
        {
            printf("Student not found.\n");
        }
        else
        {
            menu_showStudent(&db->students[index]);
        }
    }

    // search by name
    else
    {
        char input[MAX_NAME_LEN];

        // gets search string
        menu_getString("Enter name: ", input, MAX_NAME_LEN);

        int found = 0; // flag to track matches

        // loops through all students
        for (int i = 0; i < db->count; i++)
        {
            char stored[MAX_NAME_LEN], search[MAX_NAME_LEN];
            int k;

            // converts stored name to lowercase
            for (k = 0; db->students[i].name[k]; k++)
            {
                stored[k] = (char)tolower(db->students[i].name[k]);
            }
            stored[k] = '\0';

            // convert input to lowercase
            for (k = 0; input[k]; k++)
            {
            search[k] = (char)tolower(input[k]);
            }
            search[k] = '\0';

            // checks if substring exists
            if (strstr(stored, search))
            {
                menu_showStudent(&db->students[i]); // displays match
                found = 1;
            }
        }

        // if no match found
        if (!found)
        {
            printf("No match found.\n");
        }
    }
}

// record a grade
void menu_recordGrade(StudentDB* db)
{
    // gets student ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // finds student index
    int index = db_findById(db, id);

    // if not found
    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    // gets grade input
    float grade = menu_getFloat("Enter grade: ", 0, 100);

    // records grade in database
    db_recordGrade(db, id, grade);

    // displays updated average
    printf("Grade recorded. New average: %.2f\n", db->students[index].average);
}

// update student name
void menu_updateStudent(StudentDB* db)
{
    char name[MAX_NAME_LEN]; // buffer for new name

    // gets ID
    int id = menu_getInt("Enter ID: ", 1, 999999);

    // finds student
    int index = db_findById(db, id);

    // if not found
    if (index == INVALID_VALUE)
    {
        printf("Student not found.\n");
        return;
    }

    // gets new name
    menu_getString("Enter new name: ", name, MAX_NAME_LEN);

    // updates name in database
    db_updateName(db, id, name);

    // confirmation message
    printf("Student updated.\n");
}