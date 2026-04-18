/*=========================================================================
 *					STUDENT DATABASE MANAGEMENT SYSTEM
 *=========================================================================*/

#include <stdio.h>
#include <string.h>
#include "main.h"

// Function to initialize the student database by setting the count to 0.
void db_init(StudentDB* db)
{
    db->count = 0;
}

// Function to check if a student with the given ID exists in the database.
int db_idExists(const StudentDB* db, int id)
{
	for (int i = 0; i < db->count; i++)                                             // Iterates through the students in the database to check for a matching ID.
    {
		if (db->students[i].id == id)                                               // Compares the ID of each student with the given ID.
        {
			return 1;                                                               // Returns 1 if a student with the given ID exists.
        }
    }
	return 0;                                                                       // Returns 0 if no student with the given ID exists.
}

// Function to add a new student to the database with the given ID and name.
int db_addStudent(StudentDB* db, int id, const char* name)
{
	if (db->count >= MAX_STUDENTS)                                                  // Checks if the database has reached its maximum capacity for students.
    {
		return INVALID_VALUE;
    }
    if (id <= 0)                                                                    // Checks if the given ID is valid (greater than 0).
    {
        return INVALID_VALUE;                             
    }
	if (name == NULL || name[0] == '\0')                                            // Checks if the given name is valid (not NULL and not an empty string).
    {
        return INVALID_VALUE;
    }
	if (db_idExists(db, id))                                                        // Checks if a student with the given ID already exists in the database.
    {
        return INVALID_VALUE;
    }
	Student* s = &db->students[db->count];                                          // Gets a pointer to the next available slot in the students array.
	s->id = id;                                                                     // Sets the ID of the new student.
    s->gradeCount = 0;                                                              // Initializes the grade count to 0.                                    
	s->average = 0;                                                                 // Initializes the average grade to 0.
	strncpy_s(s->name, MAX_NAME_LEN, name, MAX_NAME_LEN - 1);                       // Copies the given name to the student's name field, ensuring it does not exceed the maximum length.
    s->name[MAX_NAME_LEN - 1] = '\0';                                               // Ensures the name is null-terminated.
	db->count++;                                                                    // Increments the count of students in the database.
	return 1;                                                                       // Returns 1 to indicate that the student was successfully added to the database.
}

// Function to remove a student from the database based on the given ID.
int db_removeStudent(StudentDB* db, int id)
{
	int index = db_findById(db, id);                                                // Finds the index of the student with the given ID in the database.
	if (index == INVALID_VALUE)                                                     // Checks if the student with the given ID was not found in the database.
    {
        return INVALID_VALUE;
    }
    for (int i = index; i < db->count - 1; i++)                                     // Shifts the students after the removed student to fill the gap.
    {
		db->students[i] = db->students[i + 1];                                      // Copies the next student to the current index, effectively removing the student at the specified index.
    }
    db->count--;                                                                    // Decrements the count of students in the database.
    return 1;                                                                       // Returns 1 to indicate that the student was successfully removed.
}

// Function to record a grade for a student with the given ID in the database.
int db_recordGrade(StudentDB* db, int id, float grade)
{
    if (grade < 0 || grade > 100)                                                   // Checks if the given grade is valid (between 0 and 100).
    {
        return INVALID_VALUE;
    }
    int index = db_findById(db, id);                                                // Finds the index of the student with the given ID in the database.
    if (index == INVALID_VALUE)                                                     // Checks if the student with the given ID was not found in the database.
    {
        return INVALID_VALUE;
    }
    Student* s = &db->students[index];                                              // Gets a pointer to the student with the given ID.     
    if (s->gradeCount >= MAX_GRADES)                                                // Checks if the student has already reached the maximum number of grades.   
    {
        return INVALID_VALUE;
    }
    s->grades[s->gradeCount++] = grade;                                             // Records the grade for the student and increments the grade count. 
    s->average = db_Average(s->grades, s->gradeCount);                              // Updates the average grade for the student by calculating the average of all recorded grades.
    return 1;                                                                       // Returns 1 to indicate that the grade was successfully recorded for the student.
}

// Function to calculate the average of the given grades.
float db_Average(const float grades[], int count)
{
	if (count <= 0)                                                                 // Checks if the count of grades is valid (greater than 0).
    {
        return 0.0f;
    }
	float sum = 0;                                                                  // Initializes the sum of grades to 0.
	for (int i = 0; i < count; i++)                                                 // Iterates through the grades to calculate the sum.
    {
        sum += grades[i];                                                           // Adds the current grade to the sum.
    }
    return sum / count;                                                             // Returns the average of the grades.
}

// Function to find the index of a student in the database based on the given ID.
int db_findById(const StudentDB* db, int id)
{
    for (int i = 0; i < db->count; i++)                                             // Iterates through the students in the database.
    {
        if (db->students[i].id == id)                                               // Checks if the current student's ID matches the given ID.
        {
            return i;                                                               // Returns the index of the student with the given ID.
        }
    }
	return INVALID_VALUE;                    
}

// Function to find the index of a student in the database based on the given name.
int db_findByName(const StudentDB* db, const char* name)
{
    if (name == NULL)
    {
		return INVALID_VALUE;                                                       // Checks if the given name is NULL, which is invalid for searching.
    }
	for (int i = 0; i < db->count; i++)                                             // Iterates through the students in the database.
    {
		if (strstr(db->students[i].name, name))                                     // Checks if the current student's name contains the given name as a substring.
        {
            return i;                                                               // Returns the index of the student with the given name.
        }
    }
    return INVALID_VALUE;
}

// Function to update the name of a student in the database based on the given ID and new name.
int db_updateName(StudentDB* db, int id, const char* newName)
{
	if (newName == NULL || newName[0] == '\0')                                      // Checks if the given new name is valid (not NULL and not an empty string).
    {
        return INVALID_VALUE;
    }
	int index = db_findById(db, id);                                                // Finds the index of the student with the given ID in the database.
	if (index == INVALID_VALUE)                                                     // Checks if the student with the given ID was not found in the database.
    { 
        return INVALID_VALUE;
    }
	strncpy_s(db->students[index].name, MAX_NAME_LEN, newName, MAX_NAME_LEN - 1);   // Copies the new name to the student's name field, ensuring it does not exceed the maximum length.
	db->students[index].name[MAX_NAME_LEN - 1] = '\0';                              // Ensures the new name is null-terminated.
	return 1;                                                                       // Returns 1 to indicate that the student's name was successfully updated.
}