#ifndef __LOGIC_H__
#define __LOGIC_H__
#include "_config.h"

//---------------------------------------------------------------
//	MENU
//---------------------------------------------------------------

void Title();
void Normal_Stage();
void Boss_Stage();
void Pause();
void Result();

//---------------------------------------------------------------
//	SCENE
//---------------------------------------------------------------

void TitleScene_Logic();
void PauseScene_Logic();
void ResultScene_Logic();

extern int g_iScene_Twinkle;

//---------------------------------------------------------------
//	GAME
//---------------------------------------------------------------

struct stPlayer
{
	bool bFlag;
	int iX;
	int iY;
	int iHP;
};

struct stEnemy
{
	bool bFlag;

	int iSpawnX;	// 생성됐던 위치
	int iSpawnY;
	int iRoamingX;	// 이동 반경
	int iRoamingY;
	int iCycleX;	// X축 끝 부분에 도달했는가
	int iCycleY;	// Y축 끝 부분에 도달했는가

	int iX;
	int iY;
	int iHP;
};

struct stBullet
{
	bool bFlag;
	int iX;
	int iY;
	int iOriginX; // Special Bullet Only
	int iType;
};

void InitPlayer();
void InitEnemy();
void InitBoss();
void InitBullet();
void InitSpecialBullet();

void CreateBullet(int iPosX, int iPosY, int Type, int iOriginX = 0);
void CreateSpecialBullet(int iPosX, int iPosY);

void PlayerLogic();
void EnemyLogic();
void BossLogic();
void BulletAction();
void SpecialBulletAction();

void CollisionCheck();


extern stPlayer Player;
extern stEnemy Enemy[dfMAX_ENEMY];
extern stBullet Bullet[dfMAX_BULLET];
extern stEnemy Boss;
extern stEnemy SpecialBullet[dfMAX_ENEMY];

extern int g_iState;
#endif