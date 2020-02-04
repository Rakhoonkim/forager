#pragma once
#include "stdafx.h"

//���� ������ Ÿ�� 
//�� Ÿ���� ������� 60 (60 X 60)
#define TILESIZE 60

//Ÿ�� ������ ���� 20 / ���� 20
#define TILEX 15
#define TILEY 12

//Ÿ�� �� ������� 1200 X 1200
#define TILESIZEX TILESIZE * TILEX   // 60 X 15 = 900
#define TILESIZEY TILESIZE * TILEY   // 60 X 12 = 720

//������ ����Ÿ�� 
#define PALETTESIZE 40

#define PALETTEX 7
#define PALETTEY 7

#define PALETTETILESIZEX  PALETTEX * PALETTESIZE
#define PALETTETILESIZEY  PALETTEY * PALETTESIZE


// OBJECT
#define OBJECTX 5
#define OBJECTY 5

//����
enum class TERRAIN
{
	GRASS,		// �ܵ����� 
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
	GRASS,		// ��� 
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
	TERRAIN,		// ���� 
	LAND,
	OBJECT,		// �������ڷ��̼�
	CHARACTER,		// PLAYER
	NONE,			// NONE
};

// ���� �׷����� Ÿ�� 
struct tagTile
{
	TYPE type;
	TERRAIN terrain;		//����
	LAND land;
	OBJECT object;			//��� 
	CHARACTER character;	//PLAYER
	RECT rc;				//��Ʈ
	int terrainFrameX;		//���� ��ȣ
	int terrainFrameY;		//���� ��ȣ
	int landFrameX;			//�� ��ȣ
	int landFrameY;			//�� ��ȣ 
	int objectFrameX;		//�ٴ� ���� 
	int objectFrameY;		//�ٴ� ���� 
	int characterFrameX;	//�ɸ��� ��ȣ 
	int characterFrameY;	//�ɸ��� ��ȣ 
};

// ������ �ȷ�Ʈ Ÿ�ϼ� 
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
