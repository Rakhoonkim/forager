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
	animation* playerAni;		//PLAYER ANI
	animation* weaponAni;		//WEAPON ANI
	image* playerImage;			//PLAYER IMAGE
	image* weaponImage;			//WEAPON IMAGE
	RECT rc;					//RECT
	DIRECTION direc;			//����
	float x, y;					//(X,Y)	PLAYER
	float weaponX, weaponY;	    //(X,Y)	WEAPON
	float accel;				//���ӵ�
	float angle;				//�̵� ����
	int idx, idy;				//(idx,idy)
	int hp, maxHp;				//MAXHP / HP
	int level;					//LEVEL
	int expMax, exp;			//MAX����ġ / ����ġ 
	int speed;					//���ǵ�
	int damage;					//������
	int health;					//ü��
	int imageDirection;			//�̹��� ����
	int skillPount;				//��ų ����Ʈ
	int hitCount;				//�ǰ�ī��Ʈ
	int alpha;					//Alpha��
	bool isAttack;				//�����ϴ��� �Ǵ��ϴ� BOOL��
	bool isHit;					//�ǰ�
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
	float hitTime;
	float hpBar;
	int idx, idy;
	int frameX, frameY;
	int speed;
	int hp, maxHp;
	int damage;
	int exp;
	int alpha;
	int hitCount;
	bool isClick;
	bool isJump;
	bool isAttack;
	bool isEffect;			// ����Ʈ 
	bool isHit;
	bool AttackTerm;
	bool isPlayerAttack;
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
	int stemina, heart;
	int frameX, frameY;		// �κ��丮 ������� 
	float jumpPower;
	float jumpGravity;
	bool isClick;
	bool move;
	bool drop;
	bool isUse;
};

// Inven

struct tagInven                                    
{
	const char* imageName;
	RECT rc;                                  
	int count;					// �κ��丮 ����     
	int frameX, frameY;			// �κ��丮 ����	
	int centerX, centerY;		// �κ��丮 ��ġ		
	int stemina, heart;                
	int num;			// ��ȣ                      
	float x, y;                                    
	bool isClick;                                
	bool isItem;
	bool isUse;                                   
};

// SKILL
struct tagSkill
{
	RECT rc;
	int frameX, frameY;			// �κ��丮 ����		// ��ų ������ ��ġ 
	int alpha;
	int skillPoint;
	float x, y;                                     //  x,y
	bool isClick;                                   // Ŭ��
	bool isUse;                                     // ��ų���� ����
};

// bullet

struct tagBullet
{
	animation* ani;
	RECT rc;
	float startX, startY;
	float x, y;
	float distance;
	bool isFire;
	float startAngle;
	float angle;
	float speed;
	float time;
	int idx, idy;
	int count;
};

enum class PUZZLE
{
	RAINBOW,
	DRUIDTREE,
	TREASURECHEST,
	NONE,
};

struct tagPuzzle
{
	TEMPLEOBJECT temple;
	PUZZLE puzzle;
	const char* imageName;
	RECT rc;
	float x, y;
	float centerX, centerY;
	int idx, idy;
	int width;
	int height;
	int alpha;
	bool remove;
	bool isClick;
	bool isRender;
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
	KEY,
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


struct tagTempleObject
{
	RECT rc;
	animation* ani;
	const char* imageName;
	float idx, idy;
	float x, y;
	float anlge;
	int frameX;
	float time;
};