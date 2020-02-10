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
	TREE tree;
	RECT rc;
	animation* ani;
	const char* imageName;
	float centerX, centerY;
	float x, y;
	float time;
	int idx, idy;
	int frameX, frameY;
	int speed;
	int hp, maxHp;
	int damage;
	bool isClick;
};


// item

struct tagItem
{
	const char* imageName;
	animation* ani;
	RECT rc;
	OBJECT object;
	TREE tree;
	float x, y;
	float angle;
	float time;
	int speed;
	int alpha;
	bool isClick;
	bool move;
	bool drop;
};