#pragma once
#include "stdafx.h"

//���� ������ Ÿ�� 
//�� Ÿ���� ������� 60 (60 X 60)
#define TILESIZE 60

//Ÿ�� ������ ���� 20 / ���� 20
#define TILEX 45
#define TILEY 36

//Ÿ�� �� ������� 1200 X 1200
#define TILESIZEX TILESIZE * TILEX   // 60 X 15 = 900
#define TILESIZEY TILESIZE * TILEY   // 60 X 12 = 720

//������ ����Ÿ�� 
#define PALETTESIZE 40

#define PALETTEX 7
#define PALETTEY 7

#define PALETTETILESIZEX  PALETTEX * PALETTESIZE
#define PALETTETILESIZEY  PALETTEY * PALETTESIZE

// LANDOBJECT
#define LANDOBJECTX 5
#define LANDOBJECTY 5

// OBJECT
#define OBJECTX 7
#define OBJECTY 4

// TREE
#define TREETILEX 7
#define TREETILEY 2
#define TREEHEIGHT 120

//����
enum class TERRAIN
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	NONE,
};

enum class LAND
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	WATER,		// �ٴ�Ÿ�� 
	NONE,
};

enum class LANDOBJECT
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	NONE,
};

enum class OBJECT
{
	ROCK, COAL, GOLD, IRON, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		// �ܵ����� 
	COTTON, BEET, WHEAT, BUSH , FLOWER_1, FLOWER_2, FLOWER_3,
	HOT_PEPPER, PUMPKIN, LAVENDER, CINDERBLOOM, NIGHTSHADE,
	NONE,
};

enum class TREE
{
	BASIC,
	RED,
	SNOW,
	CACTUS,
	NONE,
};
enum class CHARACTER
{
	PLAYER,	  // PLAYER
	ENEMY,	  // ENEMY
	BOSS,	  // BOSS
	NONE,
};

enum class TYPE
{
	TERRAIN,		// ���� 
	LAND,			// ��
	LANDOBJECT,     // ���� ������Ʈ 
	OBJECT,			// �Ĺ� 
	TREE, 
	CHARACTER,		// PLAYER
	NONE,			// NONE
};

// ���� �׷����� Ÿ�� 
struct tagTile
{
	TYPE type;
	TERRAIN terrain;		//����
	LAND land;				//�� 
	LANDOBJECT landObject;  //���� ���ڷ��̼� 
	TREE tree;				//���� 
	OBJECT object;			//��� 
	CHARACTER character;	//PLAYER
	RECT rc;				//��Ʈ
	int terrainFrameX;		//���� ��ȣ
	int terrainFrameY;		//���� ��ȣ
	int landFrameX;			//�� ��ȣ
	int landFrameY;			//�� ��ȣ 
	int landObjectFrameX;	//���� ���� ��ȣ  
	int landObjectFrameY;	//���� ���� ��ȣ 
	int treeFrameX;			//���� ��ȣ 
	int treeFrameY;			//���� ��ȣ 
	int objectFrameX;		//�ٴ� ���� 
	int objectFrameY;		//�ٴ� ���� 
	int characterFrameX;	//�ɸ��� ��ȣ 
	int characterFrameY;	//�ɸ��� ��ȣ 
	int idx, idy;
	bool isClick;
	bool isObject;			// �Ĺ��� �ִ��� ������ 
};

// ������ �ȷ�Ʈ Ÿ�ϼ� 
struct tagPalette
{
	TYPE type;
	TERRAIN  terrain;
	RECT rc;
	int frameX;
	int frameY;
};

struct tagButton
{
	RECT rc;
	bool isClick;
};


