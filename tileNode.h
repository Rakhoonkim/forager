#pragma once
#include "stdafx.h"

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

//character

#define CHARACTERX 6

//지형
enum class TERRAIN
{
	GRASS,		// 잔디형식 
	DESERT,
	SNOW,
	GRAVE,
	VOLCANO,
	FIRETEMPLE,
	NONE,
};

enum class LAND
{
	GRASS,		// 잔디형식 
	DESERT,
	SNOW,
	WATER,		// 바다타입 
	GRAVE,
	VOLCANO,
	NONE,
};

enum class LANDOBJECT
{
	GRASS,		// 잔디형식 
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
	TERRAIN,		// 지형 
	LAND,			// 땅
	LANDOBJECT,     // 땅위 오브젝트 
	OBJECT,			// 식물 
	TREE,			// 나무
	CHARACTER,		// PLAYER
	BUILDING,		// 건물 
	TEMPLEOBJECT,	// 건물 및 던전 오브젝트 
	NONE			// NONE
};


// 왼쪽 그려지는 타일 
struct tagTile
{
	TYPE	    		 type;			//타입 
	TERRAIN			  terrain;			//지형
	LAND				 land;			//땅 
	LANDOBJECT	   landObject;			//땅 위 오브젝트 
	OBJECT			   object;			//식물 
	TREE				 tree;			//나무 
	CHARACTER		character;			//케릭터 및 몬스터
	TEMPLEOBJECT templeObject;			//던전 오브젝트
	BUILDING		 building;			//건축물
	RECT				   rc;		    //RECT
	int terrainFrameX;		//지형 번호
	int terrainFrameY;		//지형 번호
	int landFrameX;			//땅 번호
	int landFrameY;			//땅 번호 
	int landObjectFrameX;	//땅 위 오브젝트 번호  
	int landObjectFrameY;	//땅 위 오브젝트 번호 
	int objectFrameX;		//식물 
	int objectFrameY;		//식물 
	int treeFrameX;			//나무 번호 
	int treeFrameY;			//나무 번호 
	int characterFrameX;	//케릭터 번호 
	int characterFrameY;	//케릭터 번호 
	int templeObjectFrameX; // 건물 오브젝트
	int templeObjectFrameY; // 건물 오브젝트
	int idx, idy;			//(idx,idy)
	bool isClick;			// 미니맵에 타일을 보이기 위한 값
	bool isObject;			// 타일 위에 오브젝트가 있는지 없는지
	bool isRender;			// 랜더링 Bool값
};

// 오른쪽 팔레트 타일셋 
struct tagPalette
{
	TYPE type;				//타입
	TERRAIN  terrain;		//지형
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
	int alpha;				//alpha값
	bool isClick;			//선택중인지
	bool isEffect;			//흐림효과중인지
};


