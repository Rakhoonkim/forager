#pragma once
#include "stdafx.h"


struct tagPlayer
{
	animation* playerAni;
	animation* weaponAni;
	image* playerImage;
	image* weaponImage;
	RECT rc;
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
	BUILDING building;
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
	int frameX, frameY;		// 인벤토리 사진출력 
	bool isClick;
	bool move;
	bool drop;
};

// Inven

struct tagInven
{
	RECT rc;
	int count;			// 인벤토리 개수 
	int frameX, frameY; // 인벤토리 사진 
	int centerX, centerY;		// 인벤토리 위치
	int num;			// 번호
};