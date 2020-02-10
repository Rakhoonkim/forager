#pragma once
#include "stdafx.h"

//왼쪽 보여질 타일 
//한 타일의 사이즈는 60 (60 X 60)
#define TILESIZE 60

//타일 갯수는 가로 20 / 세로 20
#define TILEX 45
#define TILEY 36

//타일 총 사이즈는 1200 X 1200
#define TILESIZEX TILESIZE * TILEX   // 60 X 15 = 900
#define TILESIZEY TILESIZE * TILEY   // 60 X 12 = 720

//오른쪽 샘플타일 
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

//지형
enum class TERRAIN
{
	GRASS,		// 잔디형식 
	DESERT,
	SNOW,
	NONE,
};

enum class LAND
{
	GRASS,		// 잔디형식 
	DESERT,
	SNOW,
	WATER,		// 바다타입 
	NONE,
};

enum class LANDOBJECT
{
	GRASS,		// 잔디형식 
	DESERT,
	SNOW,
	NONE,
};

enum class OBJECT
{
	ROCK, COAL, GOLD, IRON, VOLCANIC_COAL, VOLCANIC_IRON, VOLCANIC_GOLD,  		// 잔디형식 
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
	TERRAIN,		// 지형 
	LAND,			// 땅
	LANDOBJECT,     // 땅위 오브젝트 
	OBJECT,			// 식물 
	TREE, 
	CHARACTER,		// PLAYER
	NONE,			// NONE
};

// 왼쪽 그려지는 타일 
struct tagTile
{
	TYPE type;
	TERRAIN terrain;		//지형
	LAND land;				//땅 
	LANDOBJECT landObject;  //땅위 데코레이션 
	TREE tree;				//나무 
	OBJECT object;			//배경 
	CHARACTER character;	//PLAYER
	RECT rc;				//렉트
	int terrainFrameX;		//지형 번호
	int terrainFrameY;		//지형 번호
	int landFrameX;			//흙 번호
	int landFrameY;			//흙 번호 
	int landObjectFrameX;	//땅위 데코 번호  
	int landObjectFrameY;	//땅위 데코 번호 
	int treeFrameX;			//나무 번호 
	int treeFrameY;			//나무 번호 
	int objectFrameX;		//바닥 데코 
	int objectFrameY;		//바닥 데코 
	int characterFrameX;	//케릭터 번호 
	int characterFrameY;	//케릭터 번호 
	int idx, idy;
	bool isClick;
	bool isObject;			// 식물이 있는지 없는지 
};

// 오른쪽 팔레트 타일셋 
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


