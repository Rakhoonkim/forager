#pragma once
#include "stdafx.h"

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

//character

#define CHARACTERX 6

//����
enum class TERRAIN
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	GRAVE,
	VOLCANO,
	FIRETEMPLE,
	NONE,
};

enum class LAND
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	WATER,		// �ٴ�Ÿ�� 
	GRAVE,
	VOLCANO,
	NONE,
};

enum class LANDOBJECT
{
	GRASS,		// �ܵ����� 
	DESERT,
	SNOW,
	GRAVE,
	VOLCANO,
	NONE,
};

enum class OBJECT
{
	ROCK, COAL, GOLD, IRON, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		
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
	SLIME,
	BOAR,
	DEMON,
	SKULL,
	DEMON_BOSS,
	NONE,
};

enum class BUILDING
{
	FURNACE,
	FORGE,
	SEWING_STATION,
	BRIDGE,
	FISHTRAP,
	NONE,
};

enum class ENEMY
{
	SLIME,
	BOAR,
	DEMON,
	SKULL,
	DEMON_BOSS,
	NONE,
};

enum class TEMPLEOBJECT
{
	FURNACE,
	FORGE,
	SEWING_STATION,
	BRIDGE,
	FISHTRAP,
	RAINBOW,
	DRUIDTREE,
	TREASURECHEST,
	TEMPLE_ENTRANCE,
	TEMPLE_LANTERN,
	TEMPLE_CANNON,
	TEMPLE_DOOR,
	TEMPLE_DOOR_RED,
	TEMPLE_DOOR_BLUE,
	TEMPLE_DOOR_GREEN,
	TEMPLE_DOOR_BOSS,
	NONE,
};


enum class TYPE
{
	TERRAIN,		// ���� 
	LAND,			// ��
	LANDOBJECT,     // ���� ������Ʈ 
	OBJECT,			// �Ĺ� 
	TREE,			// ����
	CHARACTER,		// PLAYER
	BUILDING,		// �ǹ� 
	TEMPLEOBJECT,	// �ǹ� �� ���� ������Ʈ 
	NONE			// NONE
};


// ���� �׷����� Ÿ�� 
struct tagTile
{
	TYPE	    		 type;			//Ÿ�� 
	TERRAIN			  terrain;			//����
	LAND				 land;			//�� 
	LANDOBJECT	   landObject;			//�� �� ������Ʈ 
	OBJECT			   object;			//�Ĺ� 
	TREE				 tree;			//���� 
	CHARACTER		character;			//�ɸ��� �� ����
	TEMPLEOBJECT templeObject;			//���� ������Ʈ
	BUILDING		 building;			//���๰
	RECT				   rc;		    //RECT
	int terrainFrameX;		//���� ��ȣ
	int terrainFrameY;		//���� ��ȣ
	int landFrameX;			//�� ��ȣ
	int landFrameY;			//�� ��ȣ 
	int landObjectFrameX;	//�� �� ������Ʈ ��ȣ  
	int landObjectFrameY;	//�� �� ������Ʈ ��ȣ 
	int objectFrameX;		//�Ĺ� 
	int objectFrameY;		//�Ĺ� 
	int treeFrameX;			//���� ��ȣ 
	int treeFrameY;			//���� ��ȣ 
	int characterFrameX;	//�ɸ��� ��ȣ 
	int characterFrameY;	//�ɸ��� ��ȣ 
	int templeObjectFrameX; // �ǹ� ������Ʈ
	int templeObjectFrameY; // �ǹ� ������Ʈ
	int idx, idy;			//(idx,idy)
	bool isClick;			// �̴ϸʿ� Ÿ���� ���̱� ���� ��
	bool isObject;			// Ÿ�� ���� ������Ʈ�� �ִ��� ������
	bool isRender;			// ������ Bool��
};

// ������ �ȷ�Ʈ Ÿ�ϼ� 
struct tagPalette
{
	TYPE type;				//Ÿ��
	TERRAIN  terrain;		//����
	RECT rc;				//RECT
	int frameX;				//FRAME X
	int frameY;				//FRAME Y
};

struct tagButton
{
	RECT rc;
	const char* imageName;
	float x, y;				//(x,y)
	float centerX, centerY; //(centerX,centerY)
	int frameX;				//frameX
	int alpha;				//alpha��
	bool isClick;			//����������
	bool isEffect;			//�帲ȿ��������
};


