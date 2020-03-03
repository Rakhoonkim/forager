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
	TYPE type;					//타입
	OBJECT object;			    //식물
	TREE tree;					//나무
	BUILDING building;			//건물
	DIRECTION imageDirection;   //몬스터의 이미지 방향
	ENEMY enemy;				//몬스터
	RECT rc;					//RECT
	animation* ani;				//몬스터 ANI
	const char* imageName;		//이미지
	float x, y;					//(x,y)
	float width, height;		//가로, 세로
	float centerX, centerY;		//(x + width/2, y + height/2)  중점
	float time;					//시간
	float angle;				//각도
	float sourX, sourY;			//시작값
	float dstX, dstY;			//도착값
	float acel;					//가속도
	float hitTime;				//피격타임
	float hpBar;				//체력바
	int idx, idy;				//(idx,idy)
	int frameX, frameY;			//(frameX,frameY)
	int speed;					//속도
	int hp, maxHp;				// HP / MAXHP
	int damage;					//공격력
	int exp;				    //경험치
	int alpha;					//블렌더값
	int hitCount;				//피격 타임
	bool isClick;				//선택중이냐
	bool isJump;				//점프중이냐
	bool isAttack;				//공격중이냐
	bool isEffect;				//식물 이펙트	
	bool isHit;					//피격중이냐
	bool AttackTerm;			//공격텀
	bool isPlayerAttack;		// 매니저에서 사용함
};


// item
struct tagItem
{
	const char* imageName;
	animation* ani;
	RECT rc;
	OBJECT object;
	TREE tree;
	float x, y;				  //(x,y)
	float angle;			  //아이템이 떨어지는 각도
	float time;				  //아이템 시간
	int speed;				  //속도
	int alpha;				  //알파값
	int stemina, heart;		  //스테미나 생명력
	int frameX, frameY;		  //인벤토리 사진출력 
	float jumpPower;		  //아이템 점프력
	float jumpGravity;		  //아이템 떨어지는 중력 
	bool isClick;			  //선택할 수 있는지
	bool move;				  //아이템이 이동중인지
	bool drop;				  //아이템이 떨어졌는지
	bool isUse;				  //사용할수있는지없는지
};

// Inven

struct tagInven                                    
{
	const char* imageName;
	RECT rc;                                  
	int count;					// 인벤토리 개수     
	int frameX, frameY;			// 인벤토리 사진	
	int centerX, centerY;		// 인벤토리 위치		
	int stemina, heart;         // 스테미나, 생명력
	int num;				    // 번호                      
	float x, y;                 //(x,y) 
	bool isClick;				//선택          
	bool isItem;				//아이템 유무
	bool isUse;					//사용중 유뮤(오른쪽 아이템 창)      
};

// SKILL
struct tagSkill
{
	RECT rc;					//RECT
	int frameX, frameY;			// 스킬 프레임 위치 
	int alpha;					//알파값
	int skillPoint;				//스킬포인트
	float x, y;                 //(x,y)
	bool isClick;               //클릭
	bool isUse;                 //스킬적용 여부
};

// bullet

struct tagBullet
{
	animation* ani;
	RECT rc;
	float startX, startY;		//총알 충발지
	float x, y;					//(x,y)
	float distance;				//총알 나가는 거리
	float startAngle;			//총알 출발 각도
	float angle;				//총알 각도
	float speed;				//속도
	float time;					//시간
	int idx, idy;				//(idx,idy)
	int count;					//각도를 바꾸기 위한 인터벌값
	bool isFire;				//발사 했는지
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
	TEMPLEOBJECT temple;		//배경 오브젝트
	PUZZLE puzzle;				//타입
	const char* imageName;		//이미지 이름
	RECT rc;					//RECT
	float x, y;					//(x,y)
	float centerX, centerY;		//(centerX,centerY)
	int idx, idy;				//(idx,idy)
	int width;					//가로
	int height;					//세로
	int alpha;					//알파값
	bool remove;				//보물상자 제거하기 위한
	bool isClick;				//선택중을 판단
	bool isRender;				//렌더링 할건지 (LAND에서 토지 구매시 true)
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
	float idx, idy;				//(idx,idy)
	float x, y;					//(x,y)
	float anlge;				//각도
	int frameX;					//이미지 번호
	float time;					// 캐논에서 사용할 시간 값
};