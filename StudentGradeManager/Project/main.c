#include <stdio.h>
#include"student.h"
#include "menu.h"

int main(void) 
{
	StudentDB db;
	db_init(&db);
	menu_printHeader();
	printf(" Welcome to Student grade manager! Use the menu below To manage the students");
	int running = 1;
	while (running) {
		int choice = menu_showMain();
		switch (choice)
		{
		case 1:
			menu_addStudent(&db);
			break;
		case 2:
			menu_removeStudent(&db);
			break;
		case 3:
			menu_searchStudent(&db);
			break;
		case 4:
			menu_recordGrade(&db);
			break;
		case 5:
			menu_displayAll(&db);
			break;
		case 6:
			menu_updateStudent(&db);
			break;
		case 0:
			printf("\n Thank you\n");
			running = 0;
			break;
		default:
			printf("invalid choice");
			break;
		}
}


	return 0;
}