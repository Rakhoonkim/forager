#pragma once
#include "gameNode.h"

class mapToolScene : public gameNode
{
	tagTile			   _tiles[TILEX * TILEY];			// 그려지는 타일 
	
	tagPalette _terrainPalette[PALETTEX * PALETTEY];			// 지형 타일  7 X 7
	tagPalette _landPalette[PALETTEX * PALETTEY];				// 땅 타일  7 X 7
	tagPalette _landObjectPalette[LANDOBJECTX * LANDOBJECTY];	// 타일 오브젝트 5 X 5
	tagPalette _objectPalette[OBJECTX * OBJECTY];				// 오브젝트 타일
	tagPalette _treePalette[TREETILEX * TREETILEY];				// 나무 타일


	//버튼 RECT
	//X는 920 기준으로
	tagButton _mapButton[9];	//MAP 위치 
	int _mapButtonSize;

	tagButton _miniMap[TILEX * TILEY * 9];  // MINIMAP
	int		 _miniMapSizeWidth;			    // 가로 
	float	_miniMapSizeHeight;				// 세로

	tagButton	   _saveSlot[5];			// SLOT
	const char* _saveName;

	int		 _saveSlotSizeWidth;			// 가로 
	int		_saveSlotSizeHeight;			// 세로 

	tagButton _style[3];	// 0,1,2	
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
	//예정
	CHARACTER MapToolCharacterSelect(int frameX, int frameY);
};
