#include <stdio.h>
#include"student.h"
#include "menu.h"

int main(void) 
{
	StudentDB db;                      // structure to store data of the students
	db_init(&db);
	menu_printHeader();                // function call to dispaly the header
	printf(" Welcome to Student grade manager! Use the menu below To manage the students"); // message to be printed after haeader
	int running = 1;                   // variable set to continue the loop until the user wants to quit
	while (running) 
	{
		int choice = menu_showMain(); // show the functions this code can perform and takes entry from the user
		switch (choice)
		{
		case 1:
			menu_addStudent(&db);    //adds new student
			break;
		case 2:
			menu_removeStudent(&db); //removes a student
			break;
		case 3:
			menu_searchStudent(&db); //search for the student in the stored data
			break;
		case 4:
			menu_recordGrade(&db);   //records grades of the students
			break;
		case 5:
			menu_displayAll(&db);    //display all the students
			break;
		case 6:
			menu_updateStudent(&db); // update student's name
			break;
		case 0:                      // when the user wants to exit 
			printf("\n Thank you\n");
			running = 0;
			break;
		default:                      // default case if the input is wrong
			printf("invalid choice");
			break;
		}
}


	return 0;
}