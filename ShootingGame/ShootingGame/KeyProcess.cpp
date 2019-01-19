#include "Windows.h"
#include "Queue.h"
#include "_config.h"

bool KeyProcess()
{
	if (GetAsyncKeyState(VK_UP) & 0x8001)
		Enqueue(dfUP);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
		Enqueue(dfDOWN);

	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
		Enqueue(dfLEFT);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
		Enqueue(dfRIGHT);

	if (GetAsyncKeyState(VK_UP) & 0x8001 && GetAsyncKeyState(VK_LEFT) & 0x8001)
		Enqueue(dfUPLEFT);

	if (GetAsyncKeyState(VK_UP) & 0x8001 && GetAsyncKeyState(VK_RIGHT) & 0x8001)
		Enqueue(dfUPRIGHT);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001 && GetAsyncKeyState(VK_LEFT) & 0x8001)
		Enqueue(dfDOWNLEFT);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001 && GetAsyncKeyState(VK_RIGHT) & 0x8001)
		Enqueue(dfDOWNRIGHT);

	if (GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfATTACK);

	if (GetAsyncKeyState(VK_UP) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfUP_ATTACK);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfDOWN_ATTACK);

	if (GetAsyncKeyState(VK_LEFT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfLEFT_ATTACK);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfRIGHT_ATTACK);

	if (GetAsyncKeyState(VK_UP) & 0x8001 && GetAsyncKeyState(VK_LEFT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfUPLEFT_ATTACK);

	if (GetAsyncKeyState(VK_UP) & 0x8001 && GetAsyncKeyState(VK_RIGHT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfUPRIGHT_ATTACK);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001 && GetAsyncKeyState(VK_LEFT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfDOWNLEFT_ATTACK);

	if (GetAsyncKeyState(VK_DOWN) & 0x8001 && GetAsyncKeyState(VK_RIGHT) & 0x8001 && GetAsyncKeyState(VK_SPACE) & 0x8001)
		Enqueue(dfDOWNRIGHT_ATTACK);

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		Enqueue(dfESCAPE);

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		Enqueue(dfENTER);

	return true;
}