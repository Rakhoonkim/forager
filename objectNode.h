#pragma once
#include "stdafx.h"


struct tagPlayer
{
	animation* playerAni;
	animation* weaponAni;
	image* playerImage;
	image* weaponImage;
	float x, y;
	float weaponX, weaponY;
	int idx, idy;
	int hp, maxHp;
	int speed;
	int damage;
	int health;
	int direction;
};


// 작물 , 몬스터, 건물
struct tagObject
{
	OBJECT object;
	RECT rc;
	const char* imageName;
	float centerX, centerY;
	float x, y;
	float time;
	int idx, idy;
	int frameX, frameY;
	int speed;
	int hp, maxHp;
	int damage;
};
