#pragma once
#include "gameNode.h"

#define SAVESLOT 4
#define MAXSTYLE 6

class mapToolScene : public gameNode
{
	tagTile			   _tiles[TILEX * TILEY];					// 그려지는 타일 
	
	tagPalette _terrainPalette[PALETTEX * PALETTEY];			// 지형     7 X 7
	tagPalette _landPalette[PALETTEX * PALETTEY];				// 땅       7 X 7
	tagPalette _landObjectPalette[LANDOBJECTX * LANDOBJECTY];	// 오브젝트  5 X 5
	tagPalette _objectPalette[OBJECTX * OBJECTY];				// 작물 타일 7 X 4
	tagPalette _treePalette[TREETILEX * TREETILEY];				// 나무 타일 7 X 2
	tagPalette _characterPalette[CHARACTERX];
	tagPalette _templeObjectPalette[PALETTEX * PALETTEY];



	tagButton _mapButton[9];				//MAP 위치를 나타내는 RECT 
	int _mapButtonSize;


	//추후 수정 예정 
	tagButton _miniMap[TILEX * TILEY];  // MINIMAP
	int		 _miniMapSizeWidth;			    // 가로 
	float	_miniMapSizeHeight;				// 세로


	tagButton	   _saveSlot[SAVESLOT];			// SLOT
	int _saveSlotDirection;
	const char* _saveName;

	int		 _saveSlotSizeWidth;			// 가로 
	int		_saveSlotSizeHeight;			// 세로 

	tagButton _style[MAXSTYLE];	// 0,1,2	
	tagButton _type[7];     // 0,1,2,3,4
	tagButton _saveButton;	// SAVE 
	tagButton _loadButton;	// LOAD  
	tagButton _exitButton;	// 나가기 

	tagPalette _currentTile;	// 현재 타일

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void save();
	void load();
	void SaveAndLoad();

	void MapToolImage();		// 맵툴이미지
	void MapToolSetup();		// 맵툴초기화

	void MapToolCollision();	// 맵툴충돌		 : 선택할 때
	void MapToolUpdate();		// 맵툴업데이트   : 선택하고 나서  
	void MapToolEraser();		// 맵툴 삭제

	void MapToolRender();		// 맵툴렌더

	//타일 속성 
	TERRAIN MapToolTerrainSelect(int frameX, int frameY);
	LAND MapToolLandSelect(int frameX, int frameY);
	LANDOBJECT MapToolLandObjectSelect(int frameX, int frameY);
	OBJECT MapToolObjectSelect(int frameX, int frameY);
	TREE MapToolTreeSelect(int frameX, int frameY);
	CHARACTER MapToolCharacterSelect(int frameX, int frameY);
	TEMPLEOBJECT MapToolTempleObjectSelect(int frameX, int frameY);
};
