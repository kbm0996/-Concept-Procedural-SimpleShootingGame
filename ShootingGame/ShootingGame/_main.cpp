#include "Console.h"
#include "Draw.h"
#include "Logic.h"
#include <Windows.h>
#include <time.h>
#include "_config.h"

void main()
{
	srand((unsigned int)time(NULL));

	cs_Initial();
	Buffer_Clear();

	// 1 Loop = 1 Frame
	while (1)
	{
		switch (g_iState)
		{
		case dfSCENE_TITLE:
			Title();
			break;
		case dfSCENE_STAGE1:
			Normal_Stage();
			break;
		case dfSCENE_STAGE2:
			Boss_Stage();
			break;
		case dfSCENE_PAUSE:
			Pause();
			break;
		case dfSCENE_GAMEOVER:
			Result();
			break;
		}

		// Print ScreenBuffer
		Buffer_Flip();

		// Frame Control
		Sleep(100);
	}
}
