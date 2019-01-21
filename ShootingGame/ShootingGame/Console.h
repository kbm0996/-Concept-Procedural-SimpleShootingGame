//////////////////////////////////////////////////////////////
// Windows Console Cursor Control
//
//////////////////////////////////////////////////////////////
//-------------------------------------------------------------
// How to use?
//
// #incude <stdio.h>
// #include <windows.h>
// #incude "Console.h"
//
// void main(void)
// {
//		cs_Initial();
//
//		cs_MoveCursor(0, 0);	// Set cursor pos 0,0
//		printf("abcde");		// Output text at 0,0
//		cs_MoveCursor(20, 10);	// Set cursor pos 20,10
//		printf("abcde");		// Output text at 20,10
//
//		// Clear Screen
//		cs_ClearScreen();
// }
//-------------------------------------------------------------

#ifndef __CONSOLE__
#define __CONSOLE__

//-------------------------------------------------------------
// Initialize Console
//
//-------------------------------------------------------------
void cs_Initial(void);

//-------------------------------------------------------------
// Move Console Cursor
//
//-------------------------------------------------------------
void cs_MoveCursor(int iPosX, int iPosY);

//-------------------------------------------------------------
// Clear Console
//
//-------------------------------------------------------------
void cs_ClearScreen(void);


#endif

