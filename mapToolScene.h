#pragma once
#include "gameNode.h"

#define SAVESLOT 4
#define MAXSTYLE 6

class mapToolScene : public gameNode
{
	tagTile					     	_tiles[TILEX * TILEY];			//(45 X 36) 타일
	
	tagPalette				 _terrainPalette[PALETTEX * PALETTEY];	//(7 X 7)	지형
	tagPalette					_landPalette[PALETTEX * PALETTEY];	//(7 X 7)	땅
	tagPalette		_landObjectPalette[LANDOBJECTX * LANDOBJECTY];	//(5 X 5)   땅 위의 오브젝트
	tagPalette					_objectPalette[OBJECTX * OBJECTY];	//(7 X 4)   식물 오프젝트
	tagPalette				  _treePalette[TREETILEX * TREETILEY];	//(7 X 2)   나무 
	tagPalette						_characterPalette[CHARACTERX];  //6         플레이어 및 몬스터
	tagPalette			_templeObjectPalette[PALETTEX * PALETTEY];	//(7 X 7)   던전 오브젝트

	tagButton	  _mapButton[9];	// MINIMAP 
	int			 _mapButtonSize;    // MAP버튼 사이즈

	tagButton  _miniMap[TILEX * TILEY];		// (45 X 36) MINIMAP
	int				 _miniMapSizeWidth;		// 가로 
	float			_miniMapSizeHeight;		// 세로


	tagButton	   _saveSlot[SAVESLOT];		// SAVE SLOT
	const char*				 _saveName;		// 선택중인 파일 이름 
	int				_saveSlotDirection;		// 선택중인 
	int					_saveSlotWidth;		// 가로 
	int				   _saveSlotHeight;		// 세로 

	tagButton	_style[MAXSTYLE];	// 6  스타일버튼	
	tagButton			_type[7];   // 7  타입버튼
	tagButton		 _saveButton;	//	  SAVE버튼
	tagButton		 _loadButton;	//	  LOAD버튼
	tagButton		 _exitButton;	//	  나가기버튼

	tagPalette		_currentTile;	// 현재 선택한 타일

public:
	mapToolScene();
	~mapToolScene();

	HRESULT init();
	void release();
	void update();
	void render();
	
	void save();				//세이브
	void load();				//로드
	void saveLoadClick();		//세이브로드나가기 버튼 클릭

	void MapToolImage();		// 맵툴이미지
	void MapToolSetup();		// 맵툴초기화

	void MapToolCollision();	// 맵툴충돌		 : 선택할 때
	void MapToolUpdate();		// 맵툴업데이트   : 선택하고 나서  
	void MapToolEraser();		// 맵툴삭제

	void MapToolRender();		// 맵툴렌더

	//타일 속성을 반환해 주는 함수
	TERRAIN			MapToolTerrainSelect(int frameX, int frameY);
	LAND			MapToolLandSelect(int frameX, int frameY);
	LANDOBJECT	    MapToolLandObjectSelect(int frameX, int frameY);
	OBJECT			MapToolObjectSelect(int frameX, int frameY);
	TREE			MapToolTreeSelect(int frameX, int frameY);
	CHARACTER		MapToolCharacterSelect(int frameX, int frameY);
	TEMPLEOBJECT	MapToolTempleObjectSelect(int frameX, int frameY);
};
