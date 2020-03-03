#pragma once
#include "stdafx.h"


//플레이어의 방향 

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
	DIRECTION direc;			//방향
	float x, y;					//(X,Y)	PLAYER
	float weaponX, weaponY;	    //(X,Y)	WEAPON
	float accel;				//가속도
	float angle;				//이동 각도
	int idx, idy;				//(idx,idy)
	int hp, maxHp;				//MAXHP / HP
	int level;					//LEVEL
	int expMax, exp;			//MAX경험치 / 경험치 
	int speed;					//스피드
	int damage;					//데미지
	int health;					//체력
	int imageDirection;			//이미지 방향
	int skillPount;				//스킬 포인트
	int hitCount;				//피격카운트
	int alpha;					//Alpha값
	bool isAttack;				//공격하는지 판단하는 BOOL값
	bool isHit;					//피격
};


// 작물 , 몬스터, 건물
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
	float centerX, centerY;		// (x + width/2, y + height/2)  중점
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
	bool isEffect;			// 이펙트 
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
	int frameX, frameY;		// 인벤토리 사진출력 
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
	int count;					// 인벤토리 개수     
	int frameX, frameY;			// 인벤토리 사진	
	int centerX, centerY;		// 인벤토리 위치		
	int stemina, heart;                
	int num;			// 번호                      
	float x, y;                                    
	bool isClick;                                
	bool isItem;
	bool isUse;                                   
};

// SKILL
struct tagSkill
{
	RECT rc;
	int frameX, frameY;			// 인벤토리 사진		// 스킬 프레임 위치 
	int alpha;
	int skillPoint;
	float x, y;                                     //  x,y
	bool isClick;                                   // 클릭
	bool isUse;                                     // 스킬적용 여부
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