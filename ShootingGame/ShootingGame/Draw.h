#ifndef __DRAW_H__
#define __DRAW_H__

void Buffer_Clear();
void Draw_Sprite(int iPosX, int iPosY, char ch);
void Buffer_Flip();

void Draw_Scene();

void Draw_Player();
void Draw_Enemy();
void Draw_Boss();
void Draw_Bullet();
void Draw_SpecialBullet();

#endif