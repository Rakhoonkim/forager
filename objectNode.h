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


// �۹� , ����, �ǹ�
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
	int frameX, frameY;		// �κ��丮 ������� 
	bool isClick;
	bool move;
	bool drop;
};

// Inven

struct tagInven
{
	RECT rc;
	int count;			// �κ��丮 ���� 
	int frameX, frameY; // �κ��丮 ���� 
	int centerX, centerY;		// �κ��丮 ��ġ
	int num;			// ��ȣ
};