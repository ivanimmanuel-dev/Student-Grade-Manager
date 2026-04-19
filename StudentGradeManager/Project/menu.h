#pragma once

#if defined(__cplusplus)
extern "C" {
#endif

#include "student.h"

	/* Basic display helpers */
	void menu_printSeparator(void);
	void menu_printHeader(void);

	/* Main menu */
	int menu_showMain(void);

#if defined(__cplusplus)
}
#endif