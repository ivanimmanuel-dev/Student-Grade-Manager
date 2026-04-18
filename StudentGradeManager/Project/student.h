/*=========================================================================
 *							HEADER FILE: student.h
 *=========================================================================*/

#pragma once
#if defined(__cplusplus)
extern "C" {
#endif

// Constants for the student database, including an invalid value indicator, maximum limits for students, name length, and grades.
#define INVALID_VALUE  -1										// A constant to represent an invalid value, used for error handling in the database functions.
#define MAX_STUDENTS  100										// A constant to define the maximum number of students that can be stored in the database.
#define MAX_NAME_LEN   64										// A constant to define the maximum length of a student's name, including the null terminator.
#define MAX_GRADES     10										// A constant to define the maximum number of grades that can be recorded for each student.

// Structure that represents a student, containing an ID, name, array of grades, count of grades, and average grade.
typedef struct
{
		int    id;
		char   name[MAX_NAME_LEN];
		float  grades[MAX_GRADES];
		int    gradeCount;
		float  average;
} Student;

// Structure that represents the student database, containing an array of students and a count of how many students are currently stored.
typedef struct													
{
		Student students[MAX_STUDENTS];
		int     count;
} StudentDB;

// Functions for the student database operations, including initialization, adding/removing students, recording grades, calculating averages, finding students by ID or name, and updating student names.
void  db_init(StudentDB* db);
int   db_idExists(const StudentDB* db, int id);
int   db_addStudent(StudentDB* db, int id, const char* name);
int   db_removeStudent(StudentDB* db, int id);
int   db_recordGrade(StudentDB* db, int id, float grade);
float db_Average(const float grades[], int count);
int   db_findById(const StudentDB* db, int id);
int   db_findByName(const StudentDB* db, const char* name);
int   db_updateName(StudentDB* db, int id, const char* newName);

#if defined(__cplusplus)
}
#endif