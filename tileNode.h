#pragma once
#include "stdafx.h"

//왼쪽 보여질 타일 
//한 타일의 사이즈는 60 (60 X 60)
#define TILESIZE 60

//타일 갯수는 가로 20 / 세로 20
#define TILEX 15
#define TILEY 12

//타일 총 사이즈는 1200 X 1200
#define TILESIZEX TILESIZE * TILEX   // 60 X 15 = 900
#define TILESIZEY TILESIZE * TILEY   // 60 X 12 = 720

//오른쪽 샘플타일 
#define PALETTESIZE 40

#define PALETTEX 7
#define PALETTEY 7

#define PALETTETILESIZEX  PALETTEX * PALETTESIZE
#define PALETTETILESIZEY  PALETTEY * PALETTESIZE


// OBJECT
#define OBJECTX 5
#define OBJECTY 5

//지형
enum class TERRAIN
{
	GRASS,		// 잔디형식 
	WATER, 
	NONE
};

enum class LAND
{
	GRASS,
	NONE
};

enum class OBJECT
{
	GRASS,		// 배경 
	NONE
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
	LAND,
	OBJECT,		// 지형데코레이션
	CHARACTER,		// PLAYER
	NONE,			// NONE
};

// 왼쪽 그려지는 타일 
struct tagTile
{
	TYPE type;
	TERRAIN terrain;		//지형
	LAND land;
	OBJECT object;			//배경 
	CHARACTER character;	//PLAYER
	RECT rc;				//렉트
	int terrainFrameX;		//지형 번호
	int terrainFrameY;		//지형 번호
	int landFrameX;			//흙 번호
	int landFrameY;			//흙 번호 
	int objectFrameX;		//바닥 데코 
	int objectFrameY;		//바닥 데코 
	int characterFrameX;	//케릭터 번호 
	int characterFrameY;	//케릭터 번호 
};

// 오른쪽 팔레트 타일셋 
struct tagPalette
{
	TYPE type;
	RECT rc;
	int frameX;
	int frameY;
};

struct tagButton
{
	RECT rc;
	bool isClick;
};
