#pragma once
#include "stdafx.h"


//�÷��̾��� ���� 

enum class DIRECTION
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct tagPlayer
{
	animation* playerAni;
	animation* weaponAni;
	image* playerImage;
	image* weaponImage;
	RECT rc;
	DIRECTION direc;
	float x, y;
	float weaponX, weaponY;
	float acel;
	int idx, idy;
	int hp, maxHp;
	int level;			// LEVEL
	int expMax, exp;	// ����ġ�ִ�ġ, ����ġ 
	int speed;
	int damage;
	int health;
	int imageDirection;
};


// �۹� , ����, �ǹ�
struct tagObject
{
	TYPE type;
	OBJECT object;
	TREE tree;
	BUILDING building;
	DIRECTION imageDirection;
	ENEMY enemy;
	RECT rc;
	animation* ani;
	const char* imageName;
	float x, y;					// (x,y)
	float width, height;
	float centerX, centerY;		// (x + width/2, y + height/2)  ����
	float time;
	float angle;
	float sourX, sourY;
	float dstX, dstY;
	float acel;
	int idx, idy;
	int frameX, frameY;
	int speed;
	int hp, maxHp;
	int damage;
	int exp;
	bool isClick;
	bool isJump;
	bool isAttack;
	bool isEffect;			// ����Ʈ 
	bool AttackTerm;
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
	float jumpPower;
	float jumpGravity;
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


struct tagBullet
{
	animation* ani;
	RECT rc;
	float startX, startY;
	float x, y;
	bool isFire;
	float startAngle;
	float angle;
	float speed;
	float time;
	int count;
};

// recipe 
enum class FURNACERECIPE
{
	COAL,
	BRICK,
	IRON,
	GOLD,
	STEEL,
	GLASS,
	BREAD,
	FISH,
	MEAT,
	NONE,
};

enum class FORGERECIPE
{
	COIN,
	SHOVEL,
	SWORD,
	PICKAXE,
	BOTTLE,
	NONE,
};

enum class SEWINGRECIPE
{
	THREAD,
	SMALL_BACKPACK,
	MEDIUM_BACKPACK,
	SMALL_WALLET,
	SLIME_WALLET,
	NONE,
};

