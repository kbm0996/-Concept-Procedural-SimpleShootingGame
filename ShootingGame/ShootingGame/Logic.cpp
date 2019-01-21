#include "Logic.h"

#include <stdlib.h>
#include <time.h>
#include "Queue.h"
#include "Console.h"
#include "KeyProcess.h"
#include "Draw.h"

int g_iState = dfSCENE_TITLE;	// 현재 State
int g_iState_Return = 0;		// Pause() 종료 시 복귀할 State


//---------------------------------------------------------------
//	MENU
//---------------------------------------------------------------

void Title()
{
	if (!KeyProcess()) return;

	TitleScene_Logic();
	Buffer_Clear();
	Draw_Scene();
}

void Normal_Stage()
{
	if (!KeyProcess()) return;

	PlayerLogic();
	EnemyLogic();
	BulletAction();
	CollisionCheck();

	Buffer_Clear();

	Draw_Player();
	Draw_Enemy();
	Draw_Bullet();
}

void Boss_Stage()
{
	if (!KeyProcess()) return;

	PlayerLogic();
	BossLogic();
	SpecialBulletAction();
	BulletAction();
	CollisionCheck();

	Buffer_Clear();

	Draw_Player();
	Draw_Boss();
	Draw_Bullet();
	Draw_SpecialBullet();
}

void Pause()
{
	if (!KeyProcess()) return;

	PauseScene_Logic();
	Buffer_Clear();
	Draw_Scene();
}

void Result()
{
	if (!KeyProcess()) return;

	ResultScene_Logic();
	Buffer_Clear();
	Draw_Scene();
}



//---------------------------------------------------------------
//	SCENE
//---------------------------------------------------------------

int g_iScene_Twinkle = 1; // 화면 깜빡임

void TitleScene_Logic()
{
	int iAction;

	g_iScene_Twinkle *= -1;

	if (Dequeue(&iAction))
	{
		if (iAction == dfENTER)
		{
			InitPlayer();
			InitEnemy();
			InitBoss();
			InitBullet();
			InitSpecialBullet();
			g_iState = dfSCENE_STAGE1;
		}
	}
}

void PauseScene_Logic()
{
	int iAction;

	g_iScene_Twinkle *= -1;

	if (Dequeue(&iAction))
	{
		if (iAction == dfESCAPE)
		{
			g_iState = g_iState_Return;
		}
	}
}

void ResultScene_Logic()
{
	int iAction;

	g_iScene_Twinkle *= -1;

	if (Dequeue(&iAction))
	{
		if (iAction == dfENTER)
		{
			g_iState = dfSCENE_TITLE;
		}
	}
}

//---------------------------------------------------------------
//	GAME
//---------------------------------------------------------------

stPlayer Player;
stEnemy Enemy[dfMAX_ENEMY];
stEnemy Boss;
stEnemy SpecialBullet[dfMAX_ENEMY];
stBullet Bullet[dfMAX_BULLET];

void InitPlayer()
{
	Player.bFlag = true;
	Player.iHP = 5;
	Player.iX = dfSCREEN_WIDTH / 2;
	Player.iY = dfSCREEN_HEIGHT;
}

void InitEnemy()
{
	int iNo = 0;

	for (int iCnt = 0; iCnt < 3; ++iCnt)
	{
		for (int iCnt2 = 0; iCnt2 < 20; ++iCnt2)
		{
			if (iNo > dfMAX_ENEMY) break;

			Enemy[iNo].iRoamingX = 8;
			Enemy[iNo].iSpawnX = Enemy[iNo].iRoamingX + (iCnt2 + 1) * 3; // X이동반경 + X간격 
			Enemy[iNo].iSpawnY = 5 + iCnt * 3;	// Y위치 + Y간격
			Enemy[iNo].iCycleX = 1;

			Enemy[iNo].bFlag = true;
			Enemy[iNo].iHP = 1;
			Enemy[iNo].iX = Enemy[iNo].iSpawnX;
			Enemy[iNo].iY = Enemy[iNo].iSpawnY;
			++iNo;
		}
	}
}

void InitBoss()
{
	Boss.iCycleX = 1;
	Boss.iCycleY = 1;

	Boss.bFlag = true;
	Boss.iHP = 2;
	Boss.iX = 1;
	Boss.iY = 1;
}

void InitSpecialBullet()
{

	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
	{
		SpecialBullet[iCnt].bFlag = false;
		SpecialBullet[iCnt].iHP = 1;
	}
}


void InitBullet()
{
	for (int iCnt = 0; iCnt < dfMAX_BULLET; ++iCnt)
	{
		Bullet[iCnt].bFlag = false;
	}
}


void CreateBullet(int iPosX, int iPosY, int Type, int iOriginX)
{
	for (int iCnt = 0; iCnt < dfMAX_BULLET; ++iCnt)
	{
		if (Bullet[iCnt].bFlag == false)
		{
			Bullet[iCnt].bFlag = true;
			Bullet[iCnt].iX = iPosX;
			Bullet[iCnt].iY = iPosY;
			Bullet[iCnt].iType = Type;
			Bullet[iCnt].iOriginX = iOriginX;
			return;
		}
	}
}

void CreateSpecialBullet(int iPosX, int iPosY)//int Type)
{
	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
	{
		if (SpecialBullet[iCnt].bFlag == false)
		{
			SpecialBullet[iCnt].iHP = 1;
			SpecialBullet[iCnt].bFlag = true;
			SpecialBullet[iCnt].iX = iPosX;
			SpecialBullet[iCnt].iY = iPosY;
			//SpecialBullet[iCnt].bType = Type;
			return;
		}
	}
}

void PlayerLogic()
{
	int iAction;

	while (Dequeue(&iAction))
	{
		if (iAction == dfUP)
		{
			--Player.iY;
		}

		if (iAction == dfDOWN)
		{
			++Player.iY;
		}

		if (iAction == dfLEFT)
		{
			--Player.iX;
		}

		if (iAction == dfRIGHT)
		{
			++Player.iX;
		}

		if (iAction == dfUPLEFT)
		{
			--Player.iY;
			--Player.iX;
		}

		if (iAction == dfUPRIGHT)
		{
			--Player.iY;
			++Player.iX;
		}

		if (iAction == dfDOWNLEFT)
		{
			++Player.iY;
			--Player.iX;
		}

		if (iAction == dfDOWNRIGHT)
		{
			++Player.iY;
			++Player.iX;
		}

		if (iAction == dfATTACK)
		{
			CreateBullet(Player.iX, Player.iY, 0);
		}

		//if (iAction == dfUP_ATTACK)
		//{
		//	--Player.iY;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfDOWN_ATTACK)
		//{
		//	++Player.iY;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfLEFT_ATTACK)
		//{
		//	--Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfRIGHT_ATTACK)
		//{
		//	++Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfUPLEFT_ATTACK)
		//{
		//	--Player.iY;
		//	--Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfUPRIGHT_ATTACK)
		//{
		//	--Player.iY;
		//	++Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfDOWNLEFT_ATTACK)
		//{
		//	++Player.iY;
		//	--Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		//if (iAction == dfDOWNRIGHT_ATTACK)
		//{
		//	++Player.iY;
		//	++Player.iX;
		//	CreateBullet(Player.iX, Player.iY, 0);
		//}

		if (iAction == dfESCAPE)	// Pause
		{
			g_iState_Return = g_iState;
			g_iState = dfSCENE_PAUSE;
		}
	}

	if (Player.iX < 0) Player.iX = 0;
	if (Player.iY < 0) Player.iY = 0;
	if (Player.iX > dfSCREEN_WIDTH - 2)	Player.iX = dfSCREEN_WIDTH - 2;
	if (Player.iY > dfSCREEN_HEIGHT - 1) Player.iY = dfSCREEN_HEIGHT - 1;

	// 사망
	if (Player.iHP <= 0)
	{
		Player.bFlag = false;
		g_iState = dfSCENE_GAMEOVER;
	}

}


void EnemyLogic()
{
	int iDeadCnt = 0;

	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
	{
		// 이동
		if (Enemy[iCnt].bFlag == true)
		{
			if (Enemy[iCnt].iX == Enemy[iCnt].iSpawnX + Enemy[iCnt].iRoamingX || Enemy[iCnt].iX == Enemy[iCnt].iSpawnX - Enemy[iCnt].iRoamingX)
				Enemy[iCnt].iCycleX *= -1;

			if (Enemy[iCnt].iCycleX == 1)
				++Enemy[iCnt].iX;
			else
				--Enemy[iCnt].iX;
		}

		// 공격
		if (iCnt == rand() % dfMAX_ENEMY)
		{
			if (Enemy[iCnt].bFlag == true)
				CreateBullet(Enemy[iCnt].iX, Enemy[iCnt].iY, 1);
		}

		// 사망
		if (Enemy[iCnt].iHP <= 0)
		{
			Enemy[iCnt].bFlag = false;
			Enemy[iCnt].iX = 0;
			Enemy[iCnt].iY = 0;
		}

		if (Enemy[iCnt].bFlag == false)
			++iDeadCnt;
	}

	if (iDeadCnt == dfMAX_ENEMY)
	{
		InitBoss();
		InitSpecialBullet();
		g_iState = dfSCENE_STAGE2;
	}
}

void BossLogic()
{
	// 이동
	if (Boss.bFlag == true)
	{
		if (Boss.iX == 1 || Boss.iX == dfSCREEN_WIDTH - 2)
			Boss.iCycleX *= -1;

		if (Boss.iCycleX == -1)
			++Boss.iX;
		else
			--Boss.iX;


		if (Boss.iY == 1 || Boss.iY == dfSCREEN_HEIGHT / 2 - 1)
			Boss.iCycleY *= -1;

		if (Boss.iCycleY == -1)
			++Boss.iY;
		else
			--Boss.iY;
	}

	// 공격
	if (Boss.bFlag == true)
	{
		if (Boss.iY == 1)
			CreateSpecialBullet(Boss.iX, Boss.iY);

		if (Boss.iY == dfSCREEN_HEIGHT / 2 - 1)
			CreateBullet(Boss.iX, Boss.iY, 1);
	}


	// 사망
	if (Boss.iHP <= 0)
	{
		Boss.bFlag = false;
		g_iState = dfSCENE_GAMEOVER;
	}
}

void BulletAction()
{
	for (int iCnt = 0; iCnt < dfMAX_BULLET; ++iCnt)
	{
		if (Bullet[iCnt].bFlag == true)
		{
			if (Bullet[iCnt].iType == 0) // Player Bullet
			{
				--Bullet[iCnt].iY;
			}

			if (Bullet[iCnt].iType == 1) // Enemy Bullet
			{
				++Bullet[iCnt].iY;
			}

			if (Bullet[iCnt].iType == 3) // Boss Special Bullet's Bullet1
			{
				++Bullet[iCnt].iX;
				if (Bullet[iCnt].iX > Bullet[iCnt].iOriginX + 12)
					Bullet[iCnt].bFlag = false;
			}

			if (Bullet[iCnt].iType == 4) // Boss Speical Bullet's Bullet2
			{
				--Bullet[iCnt].iX;
				if (Bullet[iCnt].iX < Bullet[iCnt].iOriginX - 12)
					Bullet[iCnt].bFlag = false;
			}
		}

		if (Bullet[iCnt].iX < 0) Bullet[iCnt].bFlag = false;
		if (Bullet[iCnt].iY < 0) Bullet[iCnt].bFlag = false;
		if (Bullet[iCnt].iX > dfSCREEN_WIDTH - 2)	Bullet[iCnt].bFlag = false;
		if (Bullet[iCnt].iY > dfSCREEN_HEIGHT - 1)	Bullet[iCnt].bFlag = false;
	}
}

void SpecialBulletAction()
{
	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
	{
		// 이동
		++SpecialBullet[iCnt].iY;

		// 공격
		if (SpecialBullet[iCnt].bFlag == true)
		{
			CreateBullet(SpecialBullet[iCnt].iX, SpecialBullet[iCnt].iY, 3, SpecialBullet[iCnt].iX);
			CreateBullet(SpecialBullet[iCnt].iX, SpecialBullet[iCnt].iY, 4, SpecialBullet[iCnt].iX);
		}

		// 사망
		if (SpecialBullet[iCnt].iHP <= 0)
		{
			SpecialBullet[iCnt].bFlag = false;
			SpecialBullet[iCnt].iX = 0;
			SpecialBullet[iCnt].iY = 0;
		}

		if (SpecialBullet[iCnt].iX < 0) SpecialBullet[iCnt].bFlag = false;
		if (SpecialBullet[iCnt].iY < 0) SpecialBullet[iCnt].bFlag = false;
		if (SpecialBullet[iCnt].iX > dfSCREEN_WIDTH - 2)	SpecialBullet[iCnt].bFlag = false;
		if (SpecialBullet[iCnt].iY > dfSCREEN_HEIGHT - 1)	SpecialBullet[iCnt].bFlag = false;
	}


}

void CollisionCheck()
{
	for (int iCnt = 0; iCnt < dfMAX_BULLET; ++iCnt)
	{
		if (Bullet[iCnt].bFlag == 1)
		{
			if (Bullet[iCnt].iType == 0)	// 주인공 탄환
			{
				for (int iCnt2 = 0; iCnt2 < dfMAX_ENEMY; ++iCnt2)		// vs 적
					if (Bullet[iCnt].iX == Enemy[iCnt2].iX && Bullet[iCnt].iY == Enemy[iCnt2].iY)
					{
						--Enemy[iCnt2].iHP;
						Bullet[iCnt].bFlag = false;
					}

				if (Bullet[iCnt].iX == Boss.iX && Bullet[iCnt].iY == Boss.iY)	// vs 보스
				{
					--Boss.iHP;
					Bullet[iCnt].bFlag = false;
				}

				for (int iCnt2 = 0; iCnt2 < dfMAX_ENEMY; ++iCnt2)		// vs 특수 탄환
					if (Bullet[iCnt].iX == SpecialBullet[iCnt2].iX && Bullet[iCnt].iY == SpecialBullet[iCnt2].iY)
					{
						SpecialBullet[iCnt2].iHP--;
						Bullet[iCnt].bFlag = false;
					}

			}

			if (Bullet[iCnt].iType == 1 || Bullet[iCnt].iType == 3 || Bullet[iCnt].iType == 4)	// 적 탄환
			{
				if (Bullet[iCnt].iX == Player.iX && Bullet[iCnt].iY == Player.iY) // vs 주인공
				{
					--Player.iHP;
					Bullet[iCnt].bFlag = false;
				}
			}

		}
	}

	for (int iCnt = 0; iCnt < dfMAX_ENEMY; ++iCnt)
	{
		if (Enemy[iCnt].bFlag)	// 적
		{
			if (Enemy[iCnt].iX == Player.iX && Enemy[iCnt].iY == Player.iY)	// vs 주인공
			{
				--Player.iHP;
				Enemy[iCnt].iHP--;
			}
		}

		if (SpecialBullet[iCnt].bFlag)	// 특수 탄환 
		{
			if (SpecialBullet[iCnt].iX == Player.iX && SpecialBullet[iCnt].iY == Player.iY) // vs 주인공
			{
				--Player.iHP;
				SpecialBullet[iCnt].iHP--;
			}
		}
	}
}