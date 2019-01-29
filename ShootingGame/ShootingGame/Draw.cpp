#include <stdio.h>
#include "Console.h"
#include "Windows.h"
#include "Logic.h"
#include "_config.h"

char szScreenBuffer[dfSCREEN_HEIGHT][dfSCREEN_WIDTH];

extern int g_iState;

void Buffer_Clear()
{
	memset(szScreenBuffer, 0x20, sizeof(szScreenBuffer));
	for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; ++iCnt)
		szScreenBuffer[iCnt][dfSCREEN_WIDTH - 1] = NULL;
}

void Draw_Sprite(int iPosX, int iPosY, char ch)
{
	if (iPosX < 0) iPosX = 0;
	if (iPosY < 0) iPosY = 0;
	if (iPosX > dfSCREEN_WIDTH - 2) iPosX = dfSCREEN_WIDTH - 2;
	if (iPosY > dfSCREEN_HEIGHT - 1) iPosY = dfSCREEN_HEIGHT - 1;

	szScreenBuffer[iPosY][iPosX] = ch;
}

void Buffer_Flip()
{
	for (int iCnt = 0; iCnt < dfSCREEN_HEIGHT; ++iCnt)
	{
		cs_SetCursor(0, iCnt);
		printf(szScreenBuffer[iCnt]);
	}
}


//---------------------------------------------------------------
//	SCENE
//---------------------------------------------------------------

void Draw_Scene()
{
	//	TITLE
	if (g_iState == dfSCENE_TITLE)
	{
		Draw_Sprite(10, 20, 'M');
		Draw_Sprite(11, 20, 'o');
		Draw_Sprite(12, 20, 'v');
		Draw_Sprite(13, 20, 'e');
		Draw_Sprite(15, 20, '-');
		Draw_Sprite(17, 20, 'A');
		Draw_Sprite(18, 20, 'r');
		Draw_Sprite(19, 20, 'r');
		Draw_Sprite(20, 20, 'o');
		Draw_Sprite(21, 20, 'w');
		Draw_Sprite(22, 20, 'K');
		Draw_Sprite(23, 20, 'e');
		Draw_Sprite(24, 20, 'y');

		Draw_Sprite(10, 21, 'S');
		Draw_Sprite(11, 21, 'h');
		Draw_Sprite(12, 21, 'o');
		Draw_Sprite(13, 21, 't');
		Draw_Sprite(15, 21, '-');
		Draw_Sprite(17, 21, 'S');
		Draw_Sprite(18, 21, 'p');
		Draw_Sprite(19, 21, 'a');
		Draw_Sprite(20, 21, 'c');
		Draw_Sprite(21, 21, 'e');
		Draw_Sprite(22, 21, 'b');
		Draw_Sprite(23, 21, 'a');
		Draw_Sprite(24, 21, 'r');

		Draw_Sprite(10, 22, 'P');
		Draw_Sprite(11, 22, 'a');
		Draw_Sprite(12, 22, 'u');
		Draw_Sprite(13, 22, 's');
		Draw_Sprite(14, 22, 'e');
		Draw_Sprite(16, 22, '-');
		Draw_Sprite(18, 22, 'E');
		Draw_Sprite(19, 22, 'S');
		Draw_Sprite(20, 22, 'C');

		Draw_Sprite(31, 10, 'I');
		Draw_Sprite(34, 10, 'N');
		Draw_Sprite(37, 10, 'V');
		Draw_Sprite(40, 10, 'A');
		Draw_Sprite(43, 10, 'D');
		Draw_Sprite(46, 10, 'E');
		Draw_Sprite(49, 10, 'R');

		if (g_iScene_Twinkle == 1)
		{
			Draw_Sprite(63, 23, 'P');
			Draw_Sprite(64, 23, 'r');
			Draw_Sprite(65, 23, 'e');
			Draw_Sprite(66, 23, 's');
			Draw_Sprite(67, 23, 's');
			Draw_Sprite(69, 23, 'E');
			Draw_Sprite(70, 23, 'n');
			Draw_Sprite(71, 23, 't');
			Draw_Sprite(72, 23, 'e');
			Draw_Sprite(73, 23, 'r');
			Draw_Sprite(75, 23, 'K');
			Draw_Sprite(76, 23, 'e');
			Draw_Sprite(77, 23, 'y');
		}
	}

	//	PAUSE
	if (g_iState == dfSCENE_PAUSE)
	{
		if (g_iScene_Twinkle == 1)
		{
			Draw_Sprite(31, 10, 'P');
			Draw_Sprite(34, 10, 'A');
			Draw_Sprite(37, 10, 'U');
			Draw_Sprite(40, 10, 'S');
			Draw_Sprite(43, 10, 'E');
		}
	}

	//	GAME OVER
	if (g_iState == dfSCENE_GAMEOVER)
	{
		if (Player.bFlag == false)
		{
			Draw_Sprite(36, 10, 'G');
			Draw_Sprite(37, 10, 'A');
			Draw_Sprite(38, 10, 'M');
			Draw_Sprite(39, 10, 'E');
			Draw_Sprite(41, 10, 'O');
			Draw_Sprite(42, 10, 'V');
			Draw_Sprite(43, 10, 'E');
			Draw_Sprite(44, 10, 'R');
		}
		else
		{
			Draw_Sprite(38, 10, 'C');
			Draw_Sprite(39, 10, 'L');
			Draw_Sprite(40, 10, 'E');
			Draw_Sprite(41, 10, 'A');
			Draw_Sprite(42, 10, 'R');
		}


		if (g_iScene_Twinkle == 1)
		{
			Draw_Sprite(63, 23, 'P');
			Draw_Sprite(64, 23, 'r');
			Draw_Sprite(65, 23, 'e');
			Draw_Sprite(66, 23, 's');
			Draw_Sprite(67, 23, 's');
			Draw_Sprite(69, 23, 'E');
			Draw_Sprite(70, 23, 'n');
			Draw_Sprite(71, 23, 't');
			Draw_Sprite(72, 23, 'e');
			Draw_Sprite(73, 23, 'r');
			Draw_Sprite(75, 23, 'K');
			Draw_Sprite(76, 23, 'e');
			Draw_Sprite(77, 23, 'y');
		}
	}
}


//---------------------------------------------------------------
//	GAME
//---------------------------------------------------------------

void Draw_Player()
{
	if (Player.bFlag == 1)
		Draw_Sprite(Player.iX, Player.iY, 'A');
}

void Draw_Enemy()
{
	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
		if (Enemy[iCnt].bFlag)
			Draw_Sprite(Enemy[iCnt].iX, Enemy[iCnt].iY, '@');
}

void Draw_Boss()
{
	if (Boss.bFlag)
		Draw_Sprite(Boss.iX, Boss.iY, '#');
}

void Draw_Bullet()
{
	for (int iCnt = 0; iCnt < dfMAX_BULLET; ++iCnt)
		if (Bullet[iCnt].bFlag == true)
		{
			if (Bullet[iCnt].iType == 0)
				Draw_Sprite(Bullet[iCnt].iX, Bullet[iCnt].iY, '^');
			if (Bullet[iCnt].iType == 1)
				Draw_Sprite(Bullet[iCnt].iX, Bullet[iCnt].iY, 'v');
			if (Bullet[iCnt].iType == 3)
				Draw_Sprite(Bullet[iCnt].iX, Bullet[iCnt].iY, '>');
			if (Bullet[iCnt].iType == 4)
				Draw_Sprite(Bullet[iCnt].iX, Bullet[iCnt].iY, '<');
		}
}

void Draw_SpecialBullet()
{
	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
		if (SpecialBullet[iCnt].bFlag)
			Draw_Sprite(SpecialBullet[iCnt].iX, SpecialBullet[iCnt].iY, '@');
}


