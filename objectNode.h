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
	TYPE type;					//Ÿ��
	OBJECT object;			    //�Ĺ�
	TREE tree;					//����
	BUILDING building;			//�ǹ�
	DIRECTION imageDirection;   //������ �̹��� ����
	ENEMY enemy;				//����
	RECT rc;					//RECT
	animation* ani;				//���� ANI
	const char* imageName;		//�̹���
	float x, y;					//(x,y)
	float width, height;		//����, ����
	float centerX, centerY;		//(x + width/2, y + height/2)  ����
	float time;					//�ð�
	float angle;				//����
	float sourX, sourY;			//���۰�
	float dstX, dstY;			//������
	float acel;					//���ӵ�
	float hitTime;				//�ǰ�Ÿ��
	float hpBar;				//ü�¹�
	int idx, idy;				//(idx,idy)
	int frameX, frameY;			//(frameX,frameY)
	int speed;					//�ӵ�
	int hp, maxHp;				// HP / MAXHP
	int damage;					//���ݷ�
	int exp;				    //����ġ
	int alpha;					//������
	int hitCount;				//�ǰ� Ÿ��
	bool isClick;				//�������̳�
	bool isJump;				//�������̳�
	bool isAttack;				//�������̳�
	bool isEffect;				//�Ĺ� ����Ʈ	
	bool isHit;					//�ǰ����̳�
	bool AttackTerm;			//������
	bool isPlayerAttack;		// �Ŵ������� �����
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
	float angle;			  //�������� �������� ����
	float time;				  //������ �ð�
	int speed;				  //�ӵ�
	int alpha;				  //���İ�
	int stemina, heart;		  //���׹̳� �����
	int frameX, frameY;		  //�κ��丮 ������� 
	float jumpPower;		  //������ ������
	float jumpGravity;		  //������ �������� �߷� 
	bool isClick;			  //������ �� �ִ���
	bool move;				  //�������� �̵�������
	bool drop;				  //�������� ����������
	bool isUse;				  //����Ҽ��ִ���������
};

// Inven

struct tagInven                                    
{
	const char* imageName;
	RECT rc;                                  
	int count;					// �κ��丮 ����     
	int frameX, frameY;			// �κ��丮 ����	
	int centerX, centerY;		// �κ��丮 ��ġ		
	int stemina, heart;         // ���׹̳�, �����
	int num;				    // ��ȣ                      
	float x, y;                 //(x,y) 
	bool isClick;				//����          
	bool isItem;				//������ ����
	bool isUse;					//����� ����(������ ������ â)      
};

// SKILL
struct tagSkill
{
	RECT rc;					//RECT
	int frameX, frameY;			// ��ų ������ ��ġ 
	int alpha;					//���İ�
	int skillPoint;				//��ų����Ʈ
	float x, y;                 //(x,y)
	bool isClick;               //Ŭ��
	bool isUse;                 //��ų���� ����
};

// bullet

struct tagBullet
{
	animation* ani;
	RECT rc;
	float startX, startY;		//�Ѿ� �����
	float x, y;					//(x,y)
	float distance;				//�Ѿ� ������ �Ÿ�
	float startAngle;			//�Ѿ� ��� ����
	float angle;				//�Ѿ� ����
	float speed;				//�ӵ�
	float time;					//�ð�
	int idx, idy;				//(idx,idy)
	int count;					//������ �ٲٱ� ���� ���͹���
	bool isFire;				//�߻� �ߴ���
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
	TEMPLEOBJECT temple;		//��� ������Ʈ
	PUZZLE puzzle;				//Ÿ��
	const char* imageName;		//�̹��� �̸�
	RECT rc;					//RECT
	float x, y;					//(x,y)
	float centerX, centerY;		//(centerX,centerY)
	int idx, idy;				//(idx,idy)
	int width;					//����
	int height;					//����
	int alpha;					//���İ�
	bool remove;				//�������� �����ϱ� ����
	bool isClick;				//�������� �Ǵ�
	bool isRender;				//������ �Ұ��� (LAND���� ���� ���Ž� true)
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
	float anlge;				//����
	int frameX;					//�̹��� ��ȣ
	float time;					// ĳ���� ����� �ð� ��
};