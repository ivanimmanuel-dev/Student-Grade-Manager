/*==========================================================================================
 *									HEADER FILE: menu.h
 *								Author: Keshav Kumar Markan
 *==========================================================================================*/

#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include "student.h"

	/* Basic display helpers */
	void menu_printSeparator(void);
	void menu_printHeader(void);

	/* Display */
	void menu_showStudent(const Student* s);
	void menu_showAllStudents(const StudentDB* db);

	/* Input helpers */
	void  menu_flushInput(void);
	int   menu_getInt(const char* prompt, int min, int max);
	float menu_getFloat(const char* prompt, float min, float max);
	void  menu_getString(const char* prompt, char* buf, int size);

	/* Main menu */
	int menu_showMain(void);

	/* Menu actions */
	void menu_addStudent(StudentDB* db);
	void menu_removeStudent(StudentDB* db);
	void menu_displayAll(StudentDB* db);

	/* Search / grade / update */
	void menu_searchStudent(StudentDB* db);
	void menu_recordGrade(StudentDB* db);
	void menu_updateStudent(StudentDB* db);

#if defined(__cplusplus)
}
#endif